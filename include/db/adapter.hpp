/* 
 * File:   connection.hpp
 * Author: c
 *
 * Created on 5 maj 2013, 16:27
 */

#ifndef __DB_ICONNECTION_HPP__
#define	__DB_ICONNECTION_HPP__

#include <stdint.h>
#include <iostream>

#include "exception.hpp"

namespace db {
	
	struct Settings {
		std::string host;
		uint16_t port;
		std::string username;
		std::string password;
		std::string db;
	};

	class Adapter {
	public:
		virtual ~Adapter();
		
		virtual bool hire() = 0;
		virtual void release() = 0;
		
		Result* query(char* sql, uint32_t length);
		
	private:
		Adapter();
	};

}

#endif	/* __DB_CONNECTION_HPP__ */

