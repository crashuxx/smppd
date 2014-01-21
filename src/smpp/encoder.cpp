#include <smpp.hpp>

//#ifdef WINDOWS
#include <winsock2.h>
//#endif

//for debug only
#include <stdio.h>
#include <boost/thread.hpp>

namespace smpp {
	
	PDUEncoder::PDUEncoder() {
		
		length = 0;
		id = 0;
		status = 0;
		sequence = 0;
		
		writeUInt32(length);
		writeUInt32(id);
		writeUInt32(status);
		writeUInt32(sequence);
	}
	
	PDUEncoder::~PDUEncoder() {
		
	}
	
	std::vector<uint8_t>& PDUEncoder::read() {
		
		uint32_t tmp;
		uint8_t *p;
		
		length = data.size();
		
		tmp = htonl(length);
		p = (uint8_t*)&tmp;
		for(int i = 0; i < 4; i++) {
			data[i+0] = p[i];
		}
		
		tmp = htonl(id);
		p = (uint8_t*)&tmp;
		for(int i = 0; i < 4; i++) {
			data[i+4] = p[i];
		}
		
		tmp = htonl(status);
		p = (uint8_t*)&tmp;
		for(int i = 0; i < 4; i++) {
			data[i+8] = p[i];
		}
		
		tmp = htonl(sequence);
		p = (uint8_t*)&tmp;
		for(int i = 0; i < 4; i++) {
			data[i+12] = p[i];
		}
		
		return data;
	}
	
	void PDUEncoder::dump() {
		length = data.size();
		
		std::cout << "[" << boost::this_thread::get_id() << "]" << "PDU Length: " << length << std::endl;
		std::cout << "[" << boost::this_thread::get_id() << "]" << "PDU ID: " << id << std::endl;
		std::cout << "[" << boost::this_thread::get_id() << "]" << "PDU ID: " << SMPP_CMD_BIND_RECEIVER_RESP << std::endl;
		std::cout << "[" << boost::this_thread::get_id() << "]" << "PDU Status: " << status << std::endl;
		std::cout << "[" << boost::this_thread::get_id() << "]" << "PDU Sequence: " << sequence << std::endl;
		
		printf("Hex dump: \n");
		
		for(uint32_t i = 0; i < length; i++) {
			printf("%02X ", data[i]);
		}
		printf("\n");
		fflush(stdout);
	}
	
	uint32_t PDUEncoder::getLength() {
		return length = data.size();
	}
	
	void PDUEncoder::setID(uint32_t id) {
		this->id = id;
	}
	
	void PDUEncoder::setStatus(uint32_t status) {
		this->status = status;
	}
	
	void PDUEncoder::setSequence(uint32_t sequence) {
		this->sequence = sequence;
	}
	
	void PDUEncoder::writeUInt8(uint8_t value) {
		data.push_back(value);
	}
	
	void PDUEncoder::writeUInt16(uint16_t value) {
		uint16_t tmp = htonl(value);
		uint8_t *p = (uint8_t*)&tmp;
		for(int i = 0; i < sizeof(uint16_t); i++) {
			data.push_back(p[i]);
		}
	}
	
	void PDUEncoder::writeUInt32(uint32_t value) {
		uint32_t tmp = htonl(value);
		uint8_t *p = (uint8_t*)&tmp;
		for(int i = 0; i < 4; i++) {
			data.push_back(p[i]);
		}
	}
	
	void PDUEncoder::writeCString(uint8_t* value) {
		
		if( value != NULL ) {
		
			for(uint32_t i = 0; value[i] != 0x00 ;i++) {
				
				data.push_back(value[i]);
			}
		}
		
		data.push_back(0x00);
	}
	
	void PDUEncoder::writeCString(std::string &value) {
		writeCString( (uint8_t*)value.c_str() );
	}
}
