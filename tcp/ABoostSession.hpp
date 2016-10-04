// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/distributed-filesystem/srcs/utils/asio/ABoostSession.hpp
// Purpose:  boost asio session implementation
// Created:  2016-09-28 17:31:00
// Modified: 2016-10-04 12:28:50

#ifndef BOOST_SESSION_H
#define BOOST_SESSION_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using namespace boost::asio::ip;

namespace utils {
namespace network {
namespace tcp {

// represents a tcp session using boost asio library
// destroys itselfs when an error is encountered or if the connection is closed
class ABoostSession
{
	public:
        ABoostSession(boost::asio::io_service& io_service);
        virtual ~ABoostSession();

        ABoostSession(ABoostSession const& other) = delete;
        ABoostSession&  operator=(ABoostSession const& other) = delete;

    public:
        ::tcp::socket&  socket();
        void            start();
        void            handle_read(const boost::system::error_code& error,
                                    size_t bytes_transferred);
        void            handle_write(const boost::system::error_code& error);

    protected:
        void            async_read();
        void            async_write(char const* data, size_t len);
        void            async_write(std::string const& data);

        virtual void    process_input() = 0;
        virtual void    output_callback() = 0;

	public:
        static const unsigned int BUFFER_LENGTH = 4096;

    protected:
        ::tcp::socket   _socket;
        char            _in_buffer[BUFFER_LENGTH];
};

}
}
}

#endif /* end of include guard: BOOST_SESSION_H */
