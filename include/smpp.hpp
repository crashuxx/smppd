/* 
 * File:   smpp.hpp
 * Author: c
 *
 * Created on 28 kwiecień 2013, 16:51
 */

#ifndef __SMPP_HPP__
#define	__SMPP_HPP__

#include <basetyps.h>
#include <iostream>
#include <vector>

#include <smpp/status.hpp>

#define SMPP_CMD_GENERIC_NACK			0x80000000
#define SMPP_CMD_BIND_RECEIVER			0x00000001
#define SMPP_CMD_BIND_RECEIVER_RESP		0x80000001
#define SMPP_CMD_BIND_TRANSMITTER		0x00000002
#define SMPP_CMD_BIND_TRANSMITTER_RESP	0x80000002
#define SMPP_CMD_QUERY_SM				0x00000003
#define SMPP_CMD_QUERY_SM_RESP			0x80000003
#define SMPP_CMD_SUBMIT_SM				0x00000004
#define SMPP_CMD_SUBMIT_SM_RESP			0x80000004
#define SMPP_CMD_DELIVER_SM				0x00000005
#define SMPP_CMD_DELIVER_SM_RESP		0x80000005
#define SMPP_CMD_UNBIND					0x00000006
#define SMPP_CMD_UNBIND_RESP			0x80000006
#define SMPP_CMD_REPLACE_SM				0x00000007
#define SMPP_CMD_REPLACE_SM_RESP		0x80000007
#define SMPP_CMD_CANCEL_SM				0x00000008
#define SMPP_CMD_CANCEL_SM_RESP			0x80000008
#define SMPP_CMD_BIND_TRANSCEIVER		0x00000009
#define SMPP_CMD_BIND_TRANSCEIVER_RESP	0x80000009

#define SMPP_CMD_ENQUIRE_LINK			0x00000015
#define SMPP_CMD_ENQUIRE_LINK_RESP		0x80000015

#define SMPP_CMD_SUBMIT_MULTI			0x00000021
#define SMPP_CMD_SUBMIT_MULTI_RESP		0x80000021

#define SMPP_CMD_ALERT_NOTIFICATION		0x00000102

#define SMPP_CMD_DATA_SM				0x00000103
#define SMPP_CMD_DATA_SM_RESP			0x80000103


#define SMPP_TLV_INTERFACE_VERSION		0x0210


#define SMPP_DATACODING_SMSC	0x00
#define SMPP_DATACODING_LATIN1	0x03
#define SMPP_DATACODING_UCS2	0x08

namespace smpp {
	
	class PDUDecoder {
		
	public:
		PDUDecoder();
		virtual ~PDUDecoder();
		
		uint32_t write(uint8_t* buffer, uint32_t size);
		
		bool isTotal();
		void dump();
		
		uint32_t getLength();
		uint32_t getCommandID();
		uint32_t getStatus();
		uint32_t getSequence();
		
		uint8_t readUInt8();
		uint16_t readUInt16();
		uint32_t readUInt32();
		uint8_t* readCString(uint32_t max_length);
		
		void rewind();
		void skipHeader();
		
	private:
		uint32_t position;
		
		uint32_t length;
		uint32_t id;
		uint32_t status;
		uint32_t sequence;
		
		uint8_t *body;
	};
	
	class PDUEncoder {
	public:
		PDUEncoder();
		virtual ~PDUEncoder();
		
		std::vector<uint8_t>& read();
		void dump();
		
		uint32_t getLength();
		
		void setID(uint32_t id);
		void setStatus(uint32_t status);
		void setSequence(uint32_t sequence);
		
		void writeUInt8(uint8_t value);
		void writeUInt16(uint16_t value);
		void writeUInt32(uint32_t value);
		void writeCString(uint8_t* value);
		void writeCString(std::string &value);
	private:
		uint32_t length;
		uint32_t id;
		uint32_t status;
		uint32_t sequence;
		
		std::vector<uint8_t> data;
	};
}

#include <smpp/tlv.hpp>
#include <smpp/tlv/interfaceversion.hpp>

#include <smpp/pdu.hpp>
#include <smpp/pdu/genericnack.hpp>
#include <smpp/pdu/unbind.hpp>
#include <smpp/pdu/unbindresponse.hpp>
#include <smpp/pdu/bindtransmiter.hpp>
#include <smpp/pdu/bindtransmiterresponse.hpp>


#endif	/* __SMPP_HPP__ */

