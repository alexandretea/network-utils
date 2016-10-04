// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/distributed-filesystem/srcs/utils/asio/ABoostSession.cpp
// Purpose:  boost asio session implementation
// Created:  2016-09-29 21:20:48
// Modified: 2016-10-04 12:35:14

#include "ABoostSession.hpp"

namespace utils {
namespace network {
namespace tcp {

// constructors/destructor
ABoostSession::ABoostSession(boost::asio::io_service& io_service) :
    _socket(io_service)
{
}

ABoostSession::~ABoostSession()
{
}


// public member functions
::tcp::socket&
ABoostSession::socket()
{
    return _socket;
}

void
ABoostSession::start()
{
    async_read();
}

void
ABoostSession::handle_read(const boost::system::error_code& error,
            size_t bytes_transferred)
{
    if (!error)
    {
        process_input();
        async_read();
    }
    else
    {
        delete this;
    }
}

void
ABoostSession::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
        output_callback();
    }
    else
    {
        delete this;
    }
}

// private member functions
void
ABoostSession::async_read()
{
    std::memset(_in_buffer, 0, BUFFER_LENGTH);
    _socket.async_read_some(
        boost::asio::buffer(_in_buffer, BUFFER_LENGTH),
        boost::bind(&ABoostSession::handle_read,
                    this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred
        )
    );
}

void
ABoostSession::async_write(char const* data, size_t len)
{
    boost::asio::async_write(
        _socket,
        boost::asio::buffer(data, len),
        boost::bind(&ABoostSession::handle_write,
                    this,
                    boost::asio::placeholders::error)
    );
}

void
ABoostSession::async_write(std::string const& data)
{
    async_write(data.c_str(), data.size());
}

}
}
}
