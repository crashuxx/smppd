#include <smpp.hpp>

namespace smpp {
	
	Unbind::Unbind() : PDU() {
	}
	
	Unbind::Unbind( PDUDecoder *pdu ) : PDU() {
		decode(pdu);
	}
	
	Unbind::~Unbind() {
	}
	
	void Unbind::decode( PDUDecoder *pdu ) {
		
		pdu->rewind();
		pdu->skipHeader();
		
		setStatus( pdu->getStatus() );
		setSequence( pdu->getSequence() );
	}
	
	void Unbind::encode( PDUEncoder *pdu ) {

		pdu->setID(SMPP_CMD_UNBIND);
		pdu->setSequence( getSequence() );
		pdu->setStatus( getStatus() );
	}
}
