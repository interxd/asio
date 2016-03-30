
#include "common.h"

using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

io_service service;
ip::tcp::endpoint ep( ip::tcp::v4(), 2001); // listen on 2001
ip::tcp::acceptor acc(service, ep);

void start_accept(socket_ptr sock);

void handle_accept(socket_ptr sock, const boost::system::error_code &err) 
{
    if ( err) return;
    // 从这里开始, 你可以从socket读取或者写入

    printf("new connect in\n");

    socket_ptr sock(new ip::tcp::socket(service));
    start_accept(sock);
}


void start_accept(socket_ptr sock)
{
	acc.async_accept(*sock, boost::bind( handle_accept, sock, _1) );
}





int main()
{	
	
	socket_ptr sock(new ip::tcp::socket(service));

	start_accept(sock);

	return 0;
}
