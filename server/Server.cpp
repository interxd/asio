#include "server.hpp"
#include "connection.hpp"

server::Server(boost::asio::io_service& io_service):
	io_service_(io_service),
	acceptor_(io_service_),
	new_connection_(new Connection(io_service_))
	status_(0)
{

}

server::~Server()
{

}

server::start()
{
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), LISTEN_PORT);

	acceptor_.open(endpoint.protocol());
	acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	acceptor_.set_option(boost::asio::ip::tcp::socket::keep_alive(true));
	acceptor_.set_option(boost::asio::ip::tcp::no_delay(true));
	acceptor_.bind(endpoint);
	acceptor_.listen();

	acceptor_.async_accept(
			new_connection_->socket(),
			std::bind(
				&Server::handle_accept,
				shared_from_this(),
				boost::asio::placeholders::error
			)
	);

	status_ = 1;
}

server::handle_accept(const boost::system::error_code& err)
{
	printf("new client int\n");
	if (err)
	{
		printf("new_connection error\n");
		return;
	}

	new_connection_->start()
	new_connection_.reset(new connection(io_service_));
	//new_connection_->set_buffer_size(64 * 1024);
	
	acceptor_.async_accept(
		new_connection_.socket(),
		std::bind(
			&server::handle_accept,
			shared_from_this(),
			boost::asio::placeholders::error
			)
		);
}

server::stop()
{
	status_ = 2;
}






