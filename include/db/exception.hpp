/* 
 * File:   exceptions.hpp
 * Author: c
 *
 * Created on 8 maj 2013, 20:10
 */

#ifndef __DB_EXCEPTIONS_HPP__
#define	__DB_EXCEPTIONS_HPP__

#include <exception>
#include <iostream>

namespace db{

	class exception : public std::exception {
	public:
		exception() : std::exception(), m_mesage("unknown exception\n") {}
		exception(const char *string) : std::exception(), m_mesage(string) {}
		
		~exception() _GLIBCXX_USE_NOEXCEPT {}
		
		const char* what() const _GLIBCXX_USE_NOEXCEPT {return m_mesage.c_str();}
	private:
		std::string m_mesage;
	};
}

#endif	/* __DB_EXCEPTIONS_HPP__ */

