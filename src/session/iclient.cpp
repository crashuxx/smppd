/* 
 * File:   client.cpp
 * Author: c
 * 
 * Created on 3 maj 2013, 19:22
 */

#include "iclient.hpp"

IClient::~IClient() {
	freeAllPDU();
}

void IClient::registerPDU(smpp::PDU* pdu) {
	
	if( pdu == NULL ) {
		return;
	}
	
	lock.lock();
	pdus.push_back(pdu);
	lock.unlock();
}

void IClient::freePDU(smpp::PDU* pdu) {
	
	if( pdu == NULL ) {
		return;
	}
	
	lock.lock();
	
	uint32_t size = pdus.size();
	for(uint32_t i = 0; i < size; i++) {
		
		if( pdus[i] == pdu ) {
			
			pdus.erase( pdus.begin()+i );
			delete pdu;
			break;
		}
	}
	
	lock.unlock();
}

void IClient::freeAllPDU() {
	
	lock.lock();
	
	uint32_t size = pdus.size();
	for(uint32_t i = 0; i < size; i++) {
			
		delete pdus[i];
	}
	
	pdus.empty();
	
	lock.unlock();
}
