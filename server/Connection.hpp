#pragma once
#include "common.hpp"

using boost::asio;

class Connection
{
public:
	Connection(boost::asio::io_service& io_service);
	~Connection();

	void start();
	void stop();

	void start_work();


public:
	boost::asio::io_service&		io_service_;
	boost::asio::ip::tcp::socket	socket_;
	std::vector<char> 				buffer_;
	//Strand to ensure connection's handlers are not called concurrently
	shared_ptr         strand_;

	char tmp_buff_[1024];
};

typedef std::shared_ptr<Connection> connection_ptr;
