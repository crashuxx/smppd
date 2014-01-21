/* 
 * File:   smppserver.hpp
 * Author: c
 *
 * Created on 28 kwiecień 2013, 11:37
 */

#ifndef SMPPSERVER_HPP
#define	SMPPSERVER_HPP

#include "connection.hpp"
#include <boost/asio.hpp>
#include <boost/array.hpp>

class Server {
public:
    Server();
    virtual ~Server();
    
    void run();
	
	boost::asio::io_service& getService();
	
private:   
    void handle_accept(Connection *session, const boost::system::error_code& error);
    
    void accept();

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor *acceptor;
};

#endif	/* SMPPSERVER_HPP */

