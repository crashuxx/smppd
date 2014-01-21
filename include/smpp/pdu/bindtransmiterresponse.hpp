/* 
 * File:   bindtransmiterresponse.hpp
 * Author: c
 *
 * Created on 1 maj 2013, 12:09
 */

#ifndef __SMPP__BINDTRANSMITERRESPONSE_HPP__
#define	__SMPP__BINDTRANSMITERRESPONSE_HPP__

#include <smpp.hpp>

namespace smpp {
	
	class BindTransmiterResponse : public PDU {
	public:
		static const uint32_t id = SMPP_CMD_BIND_TRANSMITTER_RESP;

		BindTransmiterResponse();
		BindTransmiterResponse( BindTransmiter* pdu );
		~BindTransmiterResponse();

		void decode( PDUDecoder* pdu );
		void encode( PDUEncoder* pdu );

		void setSystemID(std::string value);
		TLV_InterfaceVersion& InterfaceVersion();

	private:
		std::string system_id;
		TLV_InterfaceVersion *tlv;

	};
}

#endif	/* __SMPP__BINDTRANSMITERRESPONSE_HPP__ */

