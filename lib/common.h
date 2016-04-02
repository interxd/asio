#pragma once
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <stdio.h>


typedef std::shared_ptr<boost::asio::io_service::strand> strand_ptr;

#define CONNECTION_CALLBACK(CLASS, FUNC, ...) \
	strand_->wrap(std::bind(&CLASS::FUNC, std::static_pointer_cast<CLASS>(enable_shared_from_this()), ##__VA_ARGS__))

#define CONNECTION_POST(CLASS, FUNC, ...) \
	strand_->post(std::bind(&CLASS::FUNC, std::static_pointer_cast<CLASS>(enable_shared_from_this()), ##__VA_ARGS__))