/* 
 * File:   client.hpp
 * Author: c
 *
 * Created on 3 maj 2013, 19:22
 */

#ifndef __SESSION_ICLIENT_HPP__
#define	__SESSION_ICLIENT_HPP__

#include <smpp.hpp>
#include <vector>
#include <boost/thread/mutex.hpp>

class IClient {
public:
	virtual ~IClient();
	
	virtual uint32_t registerReceiver() = 0;
	virtual uint32_t registerTransmiter() = 0;
	virtual uint32_t registerTransceiver() = 0;
	virtual void unregister() = 0;
	
	void freePDU(smpp::PDU* pdu);
protected:
	
	void registerPDU(smpp::PDU* pdu);
	void freeAllPDU();
	
	std::vector<smpp::PDU*> pdus;
	boost::mutex lock;
};

#endif	/* __SESSION_ICLIENT_HPP__ */

