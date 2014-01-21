#include <smpp.hpp>

namespace smpp {
	
	TLV_InterfaceVersion::TLV_InterfaceVersion() : TLV() {
		tag = SMPP_TLV_INTERFACE_VERSION;
		length = sizeof(uint8_t);
	}
	
	TLV_InterfaceVersion::~TLV_InterfaceVersion() {
		
	}
	
	void TLV_InterfaceVersion::encode( PDUEncoder *pdu ) {
		
		pdu->writeUInt16(tag);
		pdu->writeUInt16(length);
		pdu->writeUInt8(value);
	}
	
	void TLV_InterfaceVersion::setValue(uint8_t value) {
		this->value = value;
	}
}
