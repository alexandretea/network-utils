// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/distributed-filesystem/srcs/utils/asio/BoostSession.cpp
// Purpose:  boost asio session implementation
// Created:  2016-09-29 21:20:48
// Modified: 2016-09-29 23:15:36

#include "BoostSession.hpp"

namespace utils {
namespace network {
namespace tcp {

// constructors/destructor
BoostSession::BoostSession(boost::asio::io_service& io_service) :
    _socket(io_service)
{
}

BoostSession::~BoostSession()
{
}


// public member functions
::tcp::socket&
BoostSession::socket()
{
    return _socket;
}

void
BoostSession::start()
{
    async_read();
}

void
BoostSession::handle_read(const boost::system::error_code& error,
            size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << std::string(_in_buffer) << std::endl;
        async_read();
    }
    else
    {
        delete this;
    }
}

void
BoostSession::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
    }
    else
    {
        delete this;
    }
}

// private member functions
void
BoostSession::async_read()
{
    std::memset(_in_buffer, 0, BUFFER_LENGTH);
    _socket.async_read_some(
        boost::asio::buffer(_in_buffer, BUFFER_LENGTH),
        boost::bind(&BoostSession::handle_read,
                    this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred
        )
    );
}

void
BoostSession::async_write(char const* data, size_t len)
{
    boost::asio::async_write(
            _socket,
            boost::asio::buffer(data, len),
            boost::bind(&BoostSession::handle_write,
                        this,
                        boost::asio::placeholders::error)
    );
}

void
BoostSession::async_write(std::string const& data)
{
    async_write(data.c_str(), data.size());
}

}
}
}
