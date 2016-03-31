#pragma once

#include <boost/asio.hpp>

using boost::asio;

class Connection
{
public:
	Connection(boost::asio::io_service& io_service);
	~Connection();

public:
	boost::asio::io_service&		io_service_;
	boost::asio::ip::tcp::socket	socket_;
	std::vector<char> 				buffer_;
};

typedef std::shared_ptr<Connection> connection_ptr;
