#include <smpp.hpp>

#include <iostream>
#include <stdio.h>

namespace smpp {

	BindTransmiter::BindTransmiter() : PDU() {
		sequence = 0;
		interface_version = 0x34;
		addr_ton = 0;
		addr_npi = 0;
	}
	
	BindTransmiter::BindTransmiter( PDUDecoder *decoder ) : PDU() { 
		decode(decoder);
	}

	BindTransmiter::~BindTransmiter() {	}
	
	void BindTransmiter::decode( PDUDecoder *pdu ) {
		
		pdu->rewind();
		pdu->skipHeader();
		
		setStatus( pdu->getStatus() );
		setSequence( pdu->getSequence() );
		
		char *tmp;
		
		tmp = (char*)pdu->readCString(16);
		if( tmp != NULL ) system_id.append( tmp );
		else system_id.empty();
		
		tmp = (char*)pdu->readCString(9);
		if( tmp != NULL ) password.append( tmp );
		else password.empty();
		
		tmp = (char*)pdu->readCString(13);
		if( tmp != NULL ) system_type.append( tmp );
		else system_type.empty();
		
		interface_version = pdu->readUInt8();
		addr_ton = pdu->readUInt8();
		addr_npi = pdu->readUInt8();
		
		tmp = (char*)pdu->readCString(41);
		if( tmp != NULL ) address_range.append( tmp );
		else address_range.empty();
	}
	
	void BindTransmiter::encode( PDUEncoder *pdu ) {

		pdu->setID(SMPP_CMD_BIND_TRANSMITTER_RESP);
		pdu->setSequence( getSequence() );
		pdu->setStatus( getStatus() );
		
		pdu->writeCString( system_id );
		pdu->writeCString( password );
		pdu->writeCString( system_type );
		pdu->writeUInt32( interface_version );
		pdu->writeUInt32( addr_ton );
		pdu->writeUInt32( addr_npi );
		pdu->writeCString( address_range );
	}
		
	std::string BindTransmiter::getSystemID() {
		return system_id;
	}
	
	std::string BindTransmiter::getPassword() {
		return password;
	}
	
	std::string BindTransmiter::getSystemType() {
		return system_type;
	}
	
	uint8_t BindTransmiter::getInterfaceVersion() {
		return interface_version;
	}
	
	uint8_t BindTransmiter::getAddrTon() {
		return addr_ton;
	}
	
	uint8_t BindTransmiter::getAddrNpi() {
		return addr_npi;
	}
	
	std::string BindTransmiter::getAddressRange() {
		return address_range;
	}
	
	void BindTransmiter::setSystemID(std::string value) {
		this->system_id = value;
	}
	
	void BindTransmiter::setPassword(std::string value) {
		this->password = value;
	}
	
	void BindTransmiter::setSystemType(std::string value) {
		this->system_type = value;
	}
	
	void BindTransmiter::setInterfaceVersion(uint8_t value) {
		this->interface_version = value;
	}
	
	void BindTransmiter::setAddrTon(uint8_t value) {
		this->addr_ton = value;
	}
	
	void BindTransmiter::setAddrNpi(uint8_t value) {
		this->addr_npi = value;
	}
	
	void BindTransmiter::setAddressRange(std::string value) {
		this->address_range = value;
	}
}

