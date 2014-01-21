/* 
 * File:   mysql.hpp
 * Author: c
 *
 * Created on 8 maj 2013, 19:42
 */

#ifndef __DB_MYSQL_HPP__
#define	__DB_MYSQL_HPP__

#include <db.hpp>

#include <winsock.h>
#include <mysql.h>

#include <boost/thread/mutex.hpp>

namespace db {

	class MySQLAdapter : public Adapter {
	public:
		MySQLAdapter(Settings& settings);
		virtual ~MySQLAdapter();
		
		Result* query(char* sql, uint32_t length);
		
		bool hire();
		void release();
		
	private:

		void rise();
		void drop();
		
		bool m_raised;
		bool m_hired;
		bool m_reconnect;
		
		Settings& m_settings;
		
		MYSQL* m_hdbc;
		boost::mutex m_lock;

	};

}

#endif	/* MYSQL_HPP */

