#pragma once

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include "connection.hpp"
#include <stdio.h>

#define LISTEN_PORT (2001)

class Server: 
		public boost::enable_shared_from_this<server>,
		private boost::noncopyable
{
public:
	Server(boost::asio::io_service& io_service);
	~Server();

	void start();
	void stop();

protected:
	boost::asio::io_service&	io_service_;     //global
	boost::asio::ip::tcp::acceptor acceptor_;
	int							status_;
	connection_ptr				new_connection_;

private:
	void handle_accept(const boost::system::error_code& e);
};

typedef std::shared_ptr<friend_server> friend_server_ptr;