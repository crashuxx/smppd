/* 
 * File:   result.hpp
 * Author: c
 *
 * Created on 8 maj 2013, 21:52
 */

#ifndef __DB_MYSQL_RESULT_HPP__
#define	__DB_MYSQL_RESULT_HPP__

#include <db.hpp>

#include <winsock.h>
#include <mysql.h>

namespace db {

	class MySQLResult : public Result {
	public:
		MySQLResult( MYSQL_RES* resource );
		virtual ~MySQLResult();
	private:
		MYSQL_RES* m_resource;
	};

}

#endif	/* __DB_MYSQL_RESULT_HPP__ */

