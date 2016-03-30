#include "common.h"

using namespace boost::asio;


void connect_handler(const boost::system::error_code & ec) 
{
	printf("connect succ!!\n");    // 如果ec返回成功我们就可以知道连接成功了
}

int main()
{
	io_service service;
	ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 2001);
	ip::tcp::socket sock(service);

	sock.async_connect(ep, connect_handler);
	service.run();

	return 0;
}

