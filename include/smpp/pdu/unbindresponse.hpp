/* 
 * File:   unbindresponse.hpp
 * Author: c
 *
 * Created on 1 maj 2013, 12:13
 */

#ifndef __SMPP__UNBINDRESPONSE_HPP__
#define	__SMPP__UNBINDRESPONSE_HPP__

#include <smpp.hpp>

namespace smpp {
	
	class UnbindResponse : public PDU {
	public:
		UnbindResponse();
		UnbindResponse( Unbind* pdu );
		UnbindResponse( PDUDecoder* decoder );
		~UnbindResponse();
		
		void decode( PDUDecoder* pdu );
		void encode( PDUEncoder* pdu );
	};
}

#endif	/* __SMPP__UNBINDRESPONSE_HPP__ */

