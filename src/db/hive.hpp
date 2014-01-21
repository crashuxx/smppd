/* 
 * File:   manager.hpp
 * Author: c
 *
 * Created on 5 maj 2013, 16:35
 */

#ifndef __DB_MANAGER_HPP__
#define	__DB_MANAGER_HPP__

#include <vector>
#include <boost/thread/mutex.hpp>

#include <db.hpp>

namespace db {

	class Hive {
	public:
		Hive();
		virtual ~Hive();
		
		Connection& hire();
		void release(Connection&);
		
	private:
	
		void configuration();
		
		uint32_t m_max_connections;
		Settings m_settings;
		
		std::vector<Connection*> m_connections;
		
		boost::mutex m_lock;
	};
}

#endif	/* __DB_MANAGER_HPP__ */

