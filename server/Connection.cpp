#include "Connection.hpp"

connection::connection(boost::asio::io_service& io_service)
	io_service_(io_service),
	strand_(new boost::asio::io_service::strand(io_service))
{

}


connection::~connection()
{

}

void connection::start()
{
	connection_manager::instance().register_connection(shared_from_this());
	this->strart_work();
}

void connection::stop()
{
	connection_manager::instance().unregister_connection(shared_from_this());
	this->close_socket();
}

void connection::strart_work()
{
	socket_.async_read_some(
			boost::asio::buffer(buffer_),
			CONNECTION_CALLBACL(connection, handle_connected_read, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
		);
}

void connection::handle_connected_read(const boost::system::error_code& e, std::size_t bytes)
{
	if (!e)
	{
		memcpy(buffer_.data(), tmp_buffer_, bytes);
		tmp_buffer_[bytes] = '\0';

		printf("receive data: %s", tmp_buffer_);

		std::string s(tmp_buffer_);
		boost::asio::async_wrtie(socket_, boost::asio::buffer(s),
				CONNECTION_CALLBACL(connection, handle_write, 
					boost::asio::placeholders::error));
	}
	else
	{
		this->unreg();
	}
}

void connnection::handle_write(const boost::system::error_code& e)
{
	if (!e)
	{
		//boost::system::error_code ignored_ec;
		//socket_.shutdown(boost::asio::socket::shutdown_both, ignored_ec);
	}
	else:
	{
		this->unreg();
	}
}

void connection::close_socket()
{
	CONNECTION_POST(connection, handle_close_socket);
}

void connection::handle_close_socket()
{
	if (socket_.lowest_layer().is_open())
	{
		socket_.lowest_layer().close();
	}
}

void connection::unreg()
{
	connection_manager::instance().unregister_connection(shared_from_this());
}







