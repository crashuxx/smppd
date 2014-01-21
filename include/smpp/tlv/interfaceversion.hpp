/* 
 * File:   tlv_interfaceversion.hpp
 * Author: c
 *
 * Created on 30 kwiecień 2013, 19:41
 */

#ifndef __SMPP__TLV_INTERFACEVERSION_HPP__
#define	__SMPP__TLV_INTERFACEVERSION_HPP__

#include <smpp.hpp>

namespace smpp {
	
	class TLV_InterfaceVersion : public TLV {
	public:
		TLV_InterfaceVersion();
		~TLV_InterfaceVersion();
		
		void setValue(uint8_t value);
		
		void encode( PDUEncoder *pdu );
			
	protected:
		uint8_t value;
	};
}

#endif	/* __SMPP__TLV_INTERFACEVERSION_HPP__ */

