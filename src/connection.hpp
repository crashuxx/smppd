/* 
 * File:   session.h
 * Author: c
 *
 * Created on 28 kwiecień 2013, 12:50
 */

#ifndef __CONNECTION_HPP__
#define	__CONNECTION_HPP__

#include <vector>
#include <list>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/cstdint.hpp>
#include <boost/thread/mutex.hpp>

#include "session/default/client.hpp"

#include <smpp.hpp>

class Connection : public boost::enable_shared_from_this<Connection> {
public:
	
	static const uint32_t BUFFER_SIZE = 256;
	
	Connection(boost::asio::io_service& io_service);
	virtual ~Connection();
	
	void run();
	
	boost::asio::ip::tcp::socket& getSocket();

	bool HasStopped();
	
	void host_shutdown();
	
private:
	
	void remote_shutdown(uint32_t sequence_id);
	
	void shutdownReceive();
	void handleShutdown(uint32_t sequence_id);
	
	void handleRequest(smpp::PDUDecoder* decoder);
	void handleResponse(smpp::PDUEncoder* encoder);
	
	void read();
	void handleData( const boost::system::error_code& error, int32_t actual_bytes );
	
	smpp::PDU* bindTransmiter(smpp::BindTransmiter& request);
	smpp::PDU* unbind( smpp::Unbind& request );
	
	void push_working();
	void pop_working();
	bool is_working();
	
	bool m_shutdown;
	uint32_t m_shutdown_count;
	uint32_t m_working;
	boost::mutex m_working_lock;
	
	uint8_t* m_buffer;
	
	smpp::PDUDecoder* m_package;
	
	boost::asio::strand m_strand;
	boost::asio::deadline_timer timer;
	
	boost::asio::ip::tcp::socket m_socket;
	
	boost::mutex m_lock;
	
	Client *client;
};

#endif	/* __CONNECTION_HPP__ */

