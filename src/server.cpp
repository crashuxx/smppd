/* 
 * File:   smppserver.cpp
 * Author: c
 * 
 * Created on 28 kwiecień 2013, 11:37
 */

#include <iostream>
#include "server.hpp"
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

Server::Server() : io_service() {
	
	this->acceptor = new boost::asio::ip::tcp::acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
}

Server::~Server() {
	
	if( this->acceptor ) {
		
		this->acceptor->close();
		this->acceptor->shutdown_both;
		delete this->acceptor;
	}
}

boost::asio::io_service& Server::getService() {
	return io_service;
}

void Server::run() {
    
	accept();
	io_service.run();
}

void Server::handle_accept(Connection *session, const boost::system::error_code& error) {
	std::cerr << "new " << session->getSocket().remote_endpoint().address().to_string() << ":" << session->getSocket().remote_endpoint().port() << std::endl;
	
	session->run();
	
	accept();
}

void Server::accept() {
	Connection *session = new Connection(io_service);

	acceptor->async_accept(session->getSocket(),boost::bind(&Server::handle_accept, this, session, boost::asio::placeholders::error));
}

