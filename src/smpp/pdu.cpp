#include <smpp.hpp>

namespace smpp {

	PDU::PDU() {
		sequence = 0;
		status = 0;
	}
	
	PDU::~PDU() {}
	
	uint32_t PDU::getSequence() {
		return sequence;
	}
	
	void PDU::setSequence(uint32_t value) {
		this->sequence = value;
	}
	
	uint32_t PDU::getStatus() {
		return status;
	}
	
	void PDU::setStatus(uint32_t value) {
		this->status = value;
	}
}
