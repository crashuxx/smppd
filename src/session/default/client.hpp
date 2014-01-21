/* 
 * File:   client.hpp
 * Author: c
 *
 * Created on 4 maj 2013, 16:47
 */

#ifndef __SESSION_DEFAULT_CLIENT_HPP__
#define	__SESSION_DEFAULT_CLIENT_HPP__

#include "../iclient.hpp"

class Client : public IClient {
public:
	Client();
	~Client();
	
	uint32_t registerReceiver();
	uint32_t registerTransmiter();
	uint32_t registerTransceiver();
	void unregister();
protected:

	bool m_receiver;
	bool m_transmiter;
	bool m_transceiver;
};

#endif	/* __SESSION_DEFAULT_CLIENT_HPP__ */

