/* 
 * File:   result.cpp
 * Author: c
 * 
 * Created on 8 maj 2013, 21:52
 */

#include "result.hpp"

namespace db {

	MySQLResult::MySQLResult( MYSQL_RES* resource ) {
		m_resource = resource;
	}

	MySQLResult::~MySQLResult() {
		if( m_resource ) {
			mysql_free_result(m_resource);
		}
	}

}
