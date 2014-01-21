/* 
 * File:   bindtransmiter.hpp
 * Author: c
 *
 * Created on 30 kwiecień 2013, 19:35
 */

#ifndef __SMPP__BINDTRANSMITER_HPP__
#define	__SMPP__BINDTRANSMITER_HPP__

#include <smpp.hpp>

namespace smpp {
	
	class BindTransmiter : public PDU {
	public:
		static const uint32_t id = SMPP_CMD_BIND_TRANSMITTER;

		BindTransmiter();
		BindTransmiter( PDUDecoder *pdu );
		~BindTransmiter();

		void decode( PDUDecoder *pdu );
		void encode( PDUEncoder *pdu );

		std::string getSystemID();
		std::string getPassword();
		std::string getSystemType();
		uint8_t getInterfaceVersion();
		uint8_t getAddrTon();
		uint8_t getAddrNpi();
		std::string getAddressRange();

		void setSystemID(std::string value);
		void setPassword(std::string value);
		void setSystemType(std::string value);
		void setInterfaceVersion(uint8_t value);
		void setAddrTon(uint8_t value);
		void setAddrNpi(uint8_t value);
		void setAddressRange(std::string value);

	private:

		/**
		 * max 16
		 */
		std::string system_id;
		/**
		 * max 9
		 */
		std::string password;
		/**
		 * max 13
		 */
		std::string system_type;
		uint8_t interface_version;
		uint8_t addr_ton;
		uint8_t addr_npi;
		std::string address_range;
	};
}

#endif	/* __SMPP__BINDTRANSMITER_HPP__ */

