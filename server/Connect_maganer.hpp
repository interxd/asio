#pragma once
#include <boost/noncopyable.hpp>
#include <boost/smart_ptr/detail/spinlock.hpp>
#include "connection.hpp"


class connection_manager
	: private boost:noncopyable
{
public:
	static connection_manager& instance ()
	{
		return *s_inst_;
	}

	static void init()
	{
		s_inst_ = new connect_manager();
	}

	static finit()
	{
		delete s_inst_;
	}

	void register_connection(connection_ptr conn);
	
	void unregister_connection(connection_ptr conn);

	void stop_all();

	std::size_t get_connection_count const 
	{
		return connections_.size();
	}

	bool has_connection(connection_ptr conn);

private:
	static connection_manager *s_inst_;

	connect_manager();
	virtual ~connection_manager();

	std::set<connection_ptr> connections_;
	std::size_t histoty_connection_num_;
	mutable spinlock sp_;
}