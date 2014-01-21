
#include "db/adapter.hpp"

//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

#include "server.hpp"

#include "db/hive.hpp"

using boost::asio::ip::tcp;

boost::mutex global_stream_lock;

void WorkerThread( Server *server )
{
	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] Thread Start" << std::endl;
	global_stream_lock.unlock();

	server->getService().run();

	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] Thread Finish" << std::endl;
	global_stream_lock.unlock();
}

int main()
{
/*	Server *server = new Server();

	boost::thread_group worker_threads;
	for( int x = 0; x < 1; ++x )
	{
	//	worker_threads.create_thread( boost::bind( &WorkerThread, server) );
	}
	
	server->run();
	std::cin.get();*/
	

	db::Hive* manager = new db::Hive();
	
	db::Adapter* ad = manager->hire();
	std::string q = "SELECT * FROM clients WHERE id = 1705";
	ad->query(q.c_str(), q.length());
	
/*  try
  {
    boost::asio::io_service io_service;

    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
//tcp::socket socket(io_service);
tcp::socket *socket = new tcp::socket(io_service);
      acceptor.accept(*socket);
   //   acceptor.
    for (;;)
    {
      

      std::string message = make_daytime_string();
	  
	 const std::string string;
	 std::vector<char> d2(8);

	  
	  boost::system::error_code ignored_error;
	  boost::array<char, 1> buf;
	  unsigned int size = boost::asio::read(*socket, boost::asio::buffer(d2), ignored_error);
	  for(int i = 0; i < size; i++) {
		  putchar(d2[i]);
	  }
   //   
   
	  boost::asio::write(*socket, boost::asio::buffer("\r"), ignored_error);
      boost::asio::write(*socket, boost::asio::buffer(buf), ignored_error);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }*/

  return 0;
}