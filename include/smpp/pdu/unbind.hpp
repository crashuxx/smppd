/* 
 * File:   unbind.hpp
 * Author: c
 *
 * Created on 1 maj 2013, 12:13
 */

#ifndef __SMPP__UNBIND_HPP__
#define	__SMPP__UNBIND_HPP__

#include <smpp.hpp>

namespace smpp {
	
	class Unbind : public PDU {
	public:
		Unbind();
		Unbind( PDUDecoder *pdu );
		~Unbind();
		
		void decode( PDUDecoder *pdu );
		void encode( PDUEncoder *pdu );
	};
}

#endif	/* __SMPP__UNBIND_HPP__ */

