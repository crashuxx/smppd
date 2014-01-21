#include <smpp.hpp>

namespace smpp {
	
	GenericNack::GenericNack() : PDU() { }
	
	GenericNack::GenericNack( PDUDecoder *decoder ) : PDU() {
		decode(decoder);
	}
	
	GenericNack::~GenericNack() { }
		
	void GenericNack::decode( PDUDecoder *pdu ) {
		
		pdu->rewind();
		pdu->skipHeader();
		
		setStatus( pdu->getStatus() );
		setSequence( pdu->getSequence() );
	}
	
	void GenericNack::encode( PDUEncoder *pdu ) {
		
		pdu->setID(SMPP_CMD_GENERIC_NACK);
		pdu->setSequence( getSequence() );
		pdu->setStatus( getStatus() );
	}
}
