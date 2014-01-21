#include <smpp.hpp>

//#ifdef WINDOWS
#include <winsock2.h>
//#endif

//for debug only
#include <stdio.h>
#include <boost/thread.hpp>

namespace smpp {
	
	PDUDecoder::PDUDecoder() {
		position = 0;
		body = NULL;
	}

	PDUDecoder::~PDUDecoder() {
		if( body != NULL ) {
			delete [] body;
		}
	}
	
	bool PDUDecoder::isTotal() {
		return (position >= 16 && position == length);
	}
	
	uint32_t PDUDecoder::getLength() {
		return length;
	}
	
	uint32_t PDUDecoder::getCommandID() {
		return id;
	}
	
	uint32_t PDUDecoder::getStatus() {
		return status;
	}
	
	uint32_t PDUDecoder::getSequence() {
		return sequence;
	}
	
	
	uint32_t PDUDecoder::write(uint8_t* buffer, uint32_t size) {
		
		uint32_t i = 0;
		
		for(; i < size && position < 16; i++, position++) {
			
			uint8_t *p;
			
			if( position < 4 ) p = (uint8_t *)&length;
			else if( position < 8 ) p = (uint8_t *)&id;
			else if( position < 12 ) p = (uint8_t *)&status;
			else p = (uint8_t *)&sequence;

			p[position%4] = buffer[i];
			
			if( (position%4) == 3 ) {
				*(uint32_t*)p = ntohl(*(uint32_t*)p);
			}
		}
		
		if( position >= 16 && length > 16 ) {
			
			if( body == NULL ) {
				body = new uint8_t[length-16];
			}
			
			for(; i < size && !isTotal(); i++, position++ ) {
				body[ position-16 ] = buffer[i];
			}
		}
		
		return i;
	}
	
	void PDUDecoder::rewind() {
		position = 0;
	}
	
	void PDUDecoder::skipHeader() {
		position += 4*sizeof(uint32_t);
	}
	
	uint8_t PDUDecoder::readUInt8() {
		
		if( position < length && (position+sizeof(uint8_t)) < length ) {
			uint8_t *p = (uint8_t *)(body + position - 4*sizeof(uint32_t));
			position += sizeof(uint8_t);
			return *p;
		}
		
		return 0;
	}
	
	uint16_t PDUDecoder::readUInt16() {
		if( position < length && (position+sizeof(uint16_t)) < length ) {
			uint16_t *p = (uint16_t *)(body + position - 4*sizeof(uint32_t));
			position += sizeof(uint16_t);
			return ntohl(*p);
		}
		
		return 0;
	}
	
	uint32_t PDUDecoder::readUInt32() {
		if( position < length && (position+sizeof(uint32_t)) < length ) {
			uint32_t *p = (uint32_t *)(body + position - 4*sizeof(uint32_t));
			position += sizeof(uint32_t);
			return ntohl(*p);
		}
		
		return 0;
	}
	
	uint8_t* PDUDecoder::readCString(uint32_t max_length) {
		
		if( position < length && (position+sizeof(uint8_t)) < length ) {
			uint8_t *p = (uint8_t *)(body + position - 4*sizeof(uint32_t));
			
			bool endFound = false;

			for(uint32_t i = 0; position < length; i++) {
				position++;
				
				if( i > max_length ) {
					// error
				}
				
				if( p[i] == 0x00 ) {
					endFound = true;
					break;
				}
			}

			if( endFound ) {
				return p;
			}
		}
		return NULL;
	}

	void PDUDecoder::dump() {
		
		std::cout << "[" <<  boost::this_thread::get_id() << "]" << "PDU Length: " << length << std::endl;
		std::cout << "[" <<  boost::this_thread::get_id() << "]" << "PDU ID: " << id << std::endl;
		std::cout << "[" <<  boost::this_thread::get_id() << "]" << "PDU Status: " << status << std::endl;
		std::cout << "[" <<  boost::this_thread::get_id() << "]" << "PDU Sequence: " << sequence << std::endl;
		
		printf("Hex dump: \n");
		
		uint32_t header[4];
		header[0] = htonl(length);
		header[1] = htonl(id);
		header[2] = htonl(status);
		header[3] = htonl(sequence);
		
		uint8_t *tmp = (uint8_t *)&header;
		
		for(uint32_t i = 0; i < 16; i++) {
			printf("%02X ", tmp[i]);
		}
		
		for(uint32_t i = 0; i < (length-16); i++) {
			printf("%02X ", body[i]);
		}
		printf("\n");
		fflush(stdout);
	}
}
