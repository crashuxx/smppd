#include <smpp.hpp>

namespace smpp {

	BindTransmiterResponse::BindTransmiterResponse() : PDU() {
		tlv = NULL;
	}
	
	BindTransmiterResponse::BindTransmiterResponse( BindTransmiter* pdu ) : PDU() {
		
		tlv = NULL;
		
		if( pdu != NULL ) {
			setSequence( pdu->getSequence() );
		}
	}

	BindTransmiterResponse::~BindTransmiterResponse() {
		
		if( tlv != NULL ) {
			delete tlv;
		}
	}

	void BindTransmiterResponse::decode( PDUDecoder *pdu ) {
		
		pdu->rewind();
		pdu->skipHeader();

		setStatus( pdu->getStatus() );
		setSequence( pdu->getSequence() );
	}

	void BindTransmiterResponse::encode( PDUEncoder *pdu ) {

		pdu->setID(SMPP_CMD_BIND_TRANSMITTER_RESP);
		pdu->setSequence( getSequence() );
		pdu->setStatus( getStatus() );
		
		pdu->writeCString( system_id );
		
		if( tlv != NULL ) {
			tlv->encode(pdu);
		}
	}
	
	void BindTransmiterResponse::setSystemID(std::string value) {
		system_id = value;
	}
	
	TLV_InterfaceVersion& BindTransmiterResponse::InterfaceVersion() {
		if( tlv == NULL ) {
			tlv = new TLV_InterfaceVersion();
		}
		
		return *tlv;
	}

}