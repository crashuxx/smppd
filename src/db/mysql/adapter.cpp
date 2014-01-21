/* 
 * File:   mysql.cpp
 * Author: c
 * 
 * Created on 8 maj 2013, 19:43
 */

#include <db.hpp>

#include "adapter.hpp"
#include "result.hpp"

namespace db {

	MySQLAdapter::MySQLAdapter(Settings& settings) : m_settings(settings) {
		
		m_hired = false;
		m_raised = false
		m_reconnect = true;
				
		m_hdbc = NULL;
	}

	MySQLAdapter::~MySQLAdapter() {
		this->drop();
	}
	
	Result* MySQLAdapter::query(char* sql, uint32_t length) {
		
		int status = mysql_real_query(m_hdbc, sql, length);
		if( status != 0 ) {
			throw exception(mysql_error( m_hdbc ));
		}
		
		MYSQL_RES* resource =  mysql_store_result(m_hdbc);
		if( status != 0 ) {
			throw exception(mysql_error( m_hdbc ));
		}
		
		Result* result = new MySQLResult( resource );
		if( result == NULL ) throw std::bad_alloc();

		return result;
	}
	
	bool MySQLAdapter::hire() {
		
		bool hired = false;
		
		m_lock.lock();
		
		if( m_hired == false ) {
			m_hired = true;
		}

		m_lock.unlock();
		
		return hired;
	}
	
	void MySQLAdapter::release() {
		
		m_lock.lock();
		m_hired = false;
		m_lock.unlock();
	}
	
	void MySQLAdapter::rise() {
		
		m_hdbc = mysql_init(NULL);
						
		MYSQL*h = 
			mysql_real_connect(
				m_hdbc, 
				m_settings.host.c_str(), 
				m_settings.username.c_str(), 
				m_settings.password.c_str(), 
				m_settings.db.c_str(), 
				m_settings.port, 
				NULL, 
				CLIENT_REMEMBER_OPTIONS
			);
		
		if( h == NULL ) {
			throw exception(mysql_error( m_hdbc ));
		}
		
		mysql_options(m_hdbc, MYSQL_OPT_RECONNECT, (void*)&m_reconnect );
	}
	
	void MySQLAdapter::drop() {
		
		if( m_hdbc != NULL ) {
			mysql_close( m_hdbc );
		}
	}
}
