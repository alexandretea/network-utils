// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/distributed-filesystem/srcs/utils/asio/BoostSession.hpp
// Purpose:  boost asio session implementation
// Created:  2016-09-28 17:31:00
// Modified: 2016-09-29 22:47:42

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

// represents a tcp session using boost asio library
// destroys itselfs when an error is encountered or if the connection is closed
class BoostSession
{
	public:
        BoostSession(boost::asio::io_service& io_service);
        virtual ~BoostSession();

        BoostSession(BoostSession const& other) = delete;
        BoostSession&   operator=(BoostSession const& other) = delete;

    public:
        tcp::socket&    socket();
        void            start();
        void            handle_read(const boost::system::error_code& error,
                                    size_t bytes_transferred);
        void            handle_write(const boost::system::error_code& error);

    private:
        void            async_read();
        void            async_write(char const* data, size_t len);
        void            async_write(std::string const& data);

	public:
        static const unsigned int BUFFER_LENGTH = 4096;

    private:
        tcp::socket _socket;
        char        _in_buffer[BUFFER_LENGTH];
};

}
}

#endif /* end of include guard: BOOST_SESSION_H */
