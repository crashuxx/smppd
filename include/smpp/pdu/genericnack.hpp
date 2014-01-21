/* 
 * File:   unbind.hpp
 * Author: c
 *
 * Created on 1 maj 2013, 12:13
 */

#ifndef __SMPP__GENERICNACK_HPP__
#define	__SMPP__GENERICNACK_HPP__

#include <smpp.hpp>

namespace smpp {
	
	class GenericNack : public PDU {
	public:
		GenericNack();
		GenericNack( PDUDecoder *decoder );
		~GenericNack();
		
		void decode( PDUDecoder *pdu );
		void encode( PDUEncoder *pdu );
	};
}

#endif	/* __SMPP__GENERICNACK_HPP__ */

