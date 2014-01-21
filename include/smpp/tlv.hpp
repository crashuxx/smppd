/* 
 * File:   tlv.hpp
 * Author: c
 *
 * Created on 30 kwiecień 2013, 19:44
 */

#ifndef __SMPP__TLV_HPP__
#define	__SMPP__TLV_HPP__

#include <smpp.hpp>

namespace smpp {
	
	class TLV {
	public:
		virtual ~TLV();
	protected:
		TLV();

		uint16_t tag;
		uint16_t length;
	};
}

#endif	/* __SMPP__TLV_HPP__ */

