#include <smpp.hpp>

namespace smpp {
	
	UnbindResponse::UnbindResponse() : PDU() { }
	
	UnbindResponse::UnbindResponse( PDUDecoder* decoder ) : PDU() { 
		decode(decoder);
	}
	
	UnbindResponse::UnbindResponse( Unbind* pdu ) : PDU() { 
		
		if( pdu != NULL ) {
			setSequence( pdu->getSequence() );
		}
	}
	
	UnbindResponse::~UnbindResponse() { }
	
	void UnbindResponse::decode( PDUDecoder *pdu ) {
		
		pdu->rewind();
		pdu->skipHeader();
		
		setStatus( pdu->getStatus() );
		setSequence( pdu->getSequence() );
	}
	
	void UnbindResponse::encode( PDUEncoder *pdu ) {

		pdu->setID(SMPP_CMD_UNBIND_RESP);
		pdu->setSequence( getSequence() );
		pdu->setStatus( getStatus() );
	}
}
