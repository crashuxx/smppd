/* 
 * File:   client.cpp
 * Author: c
 * 
 * Created on 4 maj 2013, 16:47
 */

#include "client.hpp"

Client::Client() {
	
	m_transmiter = false;
	m_receiver = false;
	m_transceiver = false;
}

Client::~Client() {
}

uint32_t Client::registerReceiver() {
	
	if( m_receiver == true ) {
		return SMPP_ESME_RALYBND;
	}
	else {
		m_receiver = true;
		return SMPP_ESME_ROK;
	}
}

uint32_t Client::registerTransmiter() {
	
	if( m_transmiter == true ) {
		return SMPP_ESME_RALYBND;
	}
	else {
		m_transmiter = true;
		return SMPP_ESME_ROK;
	}
}

uint32_t Client::registerTransceiver() {
	
	if( m_transceiver == true ) {
		return SMPP_ESME_RALYBND;
	}
	else {
		m_transceiver = true;
		return SMPP_ESME_ROK;
	}
}

void Client::unregister() {
}

/*
smpp::PDU* Client::bindTransmiter(smpp::BindTransmiter& request) {
	
	smpp::BindTransmiterResponse *response = new smpp::BindTransmiterResponse();
	this->registerPDU(response);
			
	response->setSequence( request.getSequence() );
	response->setSystemID( request.getSystemID() );
	response->InterfaceVersion().setValue(0x34);
	
	return response;
}

smpp::PDU* Client::unbind( smpp::Unbind& request ) {
	
	smpp::UnbindResponse *response = new smpp::UnbindResponse(&request);
	this->registerPDU(response);
	
	return response;
}
*/