/* 
 * File:   manager.cpp
 * Author: c
 * 
 * Created on 5 maj 2013, 16:35
 */

#include "hive.hpp"
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

namespace db {

	Hive::Hive() {
		configuration();
	}

	Hive::~Hive() {
	}
	
	Adapter& Hive::hire() {
		
		Adapter *conn = NULL;
		
		m_lock.lock();
		
		for( uint32_t i = 0; i < m_connections.size() ; i++ ) {
			
			if( !m_connections[i]->in_use() ) {
				conn = m_connections[i];
				break;
			}
		}
		
		if( conn == NULL ) {
			
			if( m_connections.size() < m_max_connections ) {
				
				conn = new Connection(m_settings);
				m_connections.push_back(conn);
			}
		}
		
		if( conn != NULL ) {
			conn->hire();
		}
		
		m_lock.unlock();
		
		return *conn;
	}
	
	void release(Adapter& conn) {
		conn.release();
	}
	
	void Hive::configuration() {
		
		std::string filename = "etc/smppd.conf";

		boost::property_tree::ptree pt;
		boost::property_tree::read_info(filename, pt);
		
		m_max_connections = pt.get("db.max", 1);
		m_settings.host = pt.get<std::string>("db.connection.host", "");
		m_settings.port = pt.get("db.connection.host", 3306);
		m_settings.username = pt.get("db.connection.username", "");
		m_settings.password = pt.get("db.connection.password", "");
		m_settings.db = pt.get("db.connection.db", "");
	}
}
