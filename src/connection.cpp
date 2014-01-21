/* 
 * File:   session.cpp
 * Author: c
 * 
 * Created on 28 kwiecień 2013, 12:50
 */

#include "connection.hpp"
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include <iostream>

Connection::Connection(boost::asio::io_service& io_service) : m_socket(io_service), m_strand(io_service), timer(io_service) {
	
	m_working = 0;
	m_shutdown = false;
	m_shutdown_count = 0;
	m_buffer = new uint8_t[BUFFER_SIZE];
	m_package = NULL;
	client = new Client();
}

Connection::~Connection() {
	
	if( m_buffer != NULL ) {
		delete [] m_buffer;
	}
	
	if( m_package != NULL ) {
		delete m_package;
	}
}

void Connection::run() {
	read();
}

boost::asio::ip::tcp::socket& Connection::getSocket() {
	return m_socket;
}

void Connection::host_shutdown() {
	
	m_lock.lock();
	
	if( m_shutdown_count == 0 ) {
	
		m_shutdown_count++;

		timer.expires_from_now( boost::posix_time::milliseconds( 100 ) );
		timer.async_wait( m_strand.wrap( boost::bind( &Connection::handleShutdown, this, 0 ) ) );
	}
	
	m_lock.unlock();
}

void Connection::remote_shutdown(uint32_t sequence_id) {

	m_lock.lock();
	
	if( m_shutdown_count == 0 ) {
		
		shutdownReceive();
	
		m_shutdown_count++;

		timer.expires_from_now( boost::posix_time::milliseconds( 100 ) );
		timer.async_wait( m_strand.wrap( boost::bind( &Connection::handleShutdown, this, sequence_id ) ) );
	}
	
	m_lock.unlock();
}

void Connection::handleShutdown(uint32_t sequence_id) {

	if( !is_working() ) {
		
		if( sequence_id > 0 ) {
			
			smpp::UnbindResponse* response = new smpp::UnbindResponse();
			smpp::PDUEncoder* encoder = new smpp::PDUEncoder();
			response->setSequence(sequence_id);
			response->encode(encoder);

			try {
				getSocket().send(boost::asio::buffer(encoder->read(), encoder->getLength()));
			} catch( boost::system::system_error& e ) {
				std::cout << e.what() << std::endl;
			}
			
			encoder->dump();

			delete response;
			delete encoder;
		}
		
		try {
			getSocket().shutdown( boost::asio::ip::tcp::socket::shutdown_both );
		} catch( boost::system::system_error& e ) {
			std::cout << e.what() << std::endl;
		}
		
		try {
			getSocket().close();
		} catch( boost::system::system_error& e ) {
			std::cout << e.what() << std::endl;
		}
		
		m_shutdown = true;
		
	} else {
	
		m_shutdown_count++;
		
		std::cout << "is working!" << std::endl;
		
		timer.expires_from_now( boost::posix_time::milliseconds( 100 ) );
		timer.async_wait( m_strand.wrap( boost::bind( &Connection::handleShutdown, this, sequence_id) ) );
	}
}

void Connection::shutdownReceive() {
	
	try {
		getSocket().shutdown( boost::asio::ip::tcp::socket::shutdown_receive );
	} catch( boost::system::system_error& e ) {
		std::cout << e.what() << std::endl;
	}
}

void Connection::read() {
	
	m_socket.async_read_some(
		boost::asio::buffer( m_buffer, BUFFER_SIZE ), 
		m_strand.wrap( boost::bind( &Connection::handleData, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred ) )
	);
}

void Connection::handleRequest(smpp::PDUDecoder *decoder) {
	
	decoder->dump();
	
	smpp::PDUEncoder *encoder = NULL;
	
	if( decoder->getCommandID() == SMPP_CMD_BIND_TRANSMITTER ) {
	
		smpp::BindTransmiter* request = new smpp::BindTransmiter(decoder);

		smpp::PDU* response = bindTransmiter(*request);
		
		encoder = new smpp::PDUEncoder();
		response->encode(encoder);
		
		delete response;
		delete request;
	}
	else if( decoder->getCommandID() == SMPP_CMD_UNBIND ) {
		
		smpp::Unbind* request = new smpp::Unbind(decoder);
		smpp::PDU* response = unbind(*request);
		
		if( response != NULL ) {
		
			encoder = new smpp::PDUEncoder();
			response->encode(encoder);
		
			delete response;
		}
		
		delete request;
	}
	else {
		
		smpp::GenericNack* response = new smpp::GenericNack();
		response->setSequence(decoder->getSequence());
		
		encoder = new smpp::PDUEncoder();
		response->encode(encoder);
		
		delete response;
	}
	
	if( encoder != NULL ) {
		push_working();
		m_strand.post( boost::bind( &Connection::handleResponse, this, encoder ) );
	}
	
	delete decoder;
	pop_working();
}

void Connection::handleResponse(smpp::PDUEncoder *pdu) {
	
	if( pdu == NULL ) {
		pop_working();
		return;
	}
	
	try {
		getSocket().send(boost::asio::buffer(pdu->read(), pdu->getLength()));
	
	} catch( boost::system::system_error& e ) {
		std::cout << e.what() << std::endl;
	}
	
	pdu->dump();
	
	delete pdu;
	pop_working();
}

void Connection::handleData( const boost::system::error_code& error, int32_t actual_bytes ) {
	
	push_working();
	
	if( error /*|| HasError() || m_hive->HasStopped()*/ ) {
		//StartError( error ); 
	} else if( m_shutdown_count > 0 ) {
		// skip
	} else {
		
		uint32_t read = 0;
		while(read < actual_bytes) {
			
			if( m_package == NULL ) {
				m_package = new smpp::PDUDecoder();
			}
			
			read += m_package->write(m_buffer+read, actual_bytes-read);
			
			if( m_package->isTotal() ) {
				push_working();
				getSocket().get_io_service().post( boost::bind( &Connection::handleRequest, this, m_package ) );
				m_package = NULL;
			}
		}
		
		this->read();
	}
	
	pop_working();
}

smpp::PDU* Connection::bindTransmiter(smpp::BindTransmiter& request) {
	
	smpp::BindTransmiterResponse *response = new smpp::BindTransmiterResponse();
			
	response->setSequence( request.getSequence() );
	response->setSystemID( request.getSystemID() );
	response->InterfaceVersion().setValue(0x34);
	
	return response;
}

smpp::PDU* Connection::unbind( smpp::Unbind& request ) {
	
	remote_shutdown( request.getSequence() );
	return NULL;
}

void Connection::push_working() {
	
	m_working_lock.lock();
	m_working++;
	m_working_lock.unlock();
}

void Connection::pop_working() {
	
	m_working_lock.lock();
	m_working--;
	m_working_lock.unlock();
}

bool Connection::is_working() {
	
	m_working_lock.lock();
	bool is_working = (m_working != 0);
	m_working_lock.unlock();
	
	return is_working;
}
