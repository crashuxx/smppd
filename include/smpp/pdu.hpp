/* 
 * File:   pdu.hpp
 * Author: c
 *
 * Created on 30 kwiecień 2013, 19:43
 */

#ifndef __SMPP__PDU_HPP__
#define	__SMPP__PDU_HPP__

#include <smpp.hpp>

namespace smpp {
	
	class PDU {
	public:
		virtual ~PDU();
		virtual void decode( PDUDecoder *pdu ) = 0;
		virtual void encode( PDUEncoder *pdu ) = 0;
		
		virtual uint32_t getSequence();
		virtual void setSequence(uint32_t value);
		
		virtual uint32_t getStatus();
		virtual void setStatus(uint32_t value);
		
	protected: 
		PDU();

		uint32_t sequence;
		uint32_t status;
	};
}

#endif	/* __SMPP__PDU_HPP__ */

