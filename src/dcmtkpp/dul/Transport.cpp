/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/dul/Transport.h"

#include <memory>
#include <string>

#include <boost/asio.hpp>
#include <boost/date_time.hpp>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

namespace dul
{

Transport
::Transport()
: _service(), _socket(nullptr), _timeout(boost::posix_time::pos_infin),
  _deadline(_service)
{
    // Nothing else
}

Transport
::~Transport()
{
    if(this->is_open())
    {
        this->close();
    }
}

boost::asio::io_service const &
Transport
::get_service() const
{
    return this->_service;
}

boost::asio::io_service &
Transport
::get_service()
{
    return this->_service;
}

std::shared_ptr<Transport::Socket const>
Transport
::get_socket() const
{
    return this->_socket;
}

std::shared_ptr<Transport::Socket>
Transport
::get_socket()
{
    return this->_socket;
}

Transport::duration_time
Transport
::get_timeout() const
{
    return this->_timeout;
}

void
Transport
::set_timeout(duration_time timeout)
{
    this->_timeout = timeout;
}

bool
Transport
::is_open() const
{
    return (this->_socket != nullptr && this->_socket->is_open());
}

void
Transport
::connect(Socket::endpoint_type const & peer_endpoint)
{
    if(this->is_open())
    {
        throw Exception("Already connected");
    }

    this->_start_deadline();

    this->_socket = std::make_shared<Socket>(this->_service);
    this->_socket->async_connect(
        peer_endpoint,
        [](boost::system::error_code const & error)
        {
            if(error == boost::asio::error::operation_aborted)
            {
                throw Exception("Connection timed out");
            }
            else if(error)
            {
                throw boost::system::system_error(error);
            }
        }
    );

    this->_service.run_one();
    this->_stop_deadline();
}

void
Transport
::receive(Socket::endpoint_type const & endpoint)
{
    if(this->is_open())
    {
        throw Exception("Already connected");
    }

    this->_start_deadline();

    this->_socket = std::make_shared<Socket>(this->_service);
    boost::asio::ip::tcp::acceptor acceptor(this->_service, endpoint);
    acceptor.async_accept(
        *this->_socket,
        [](boost::system::error_code const & error)
        {
            if(error == boost::asio::error::operation_aborted)
            {
                throw Exception("Connection timed out");
            }
            else if(error)
            {
                throw boost::system::system_error(error);
            }
        }
    );

    this->_service.run_one();
    this->_service.reset();
    this->_stop_deadline();
}

void
Transport
::close()
{
    if(!this->is_open())
    {
        throw Exception("Not connected");
    }

    this->_socket->close();
    this->_socket = nullptr;
}

std::string
Transport
::read(std::size_t length)
{
    if(!this->is_open())
    {
        throw Exception("Not connected");
    }

    std::string data(length, '\0');

    this->_start_deadline();

    boost::asio::async_read(
        *this->_socket,
        boost::asio::buffer(&data[0], data.size()),
        [](boost::system::error_code const & error, std::size_t)
        {
            if(error == boost::asio::error::operation_aborted)
            {
                throw Exception("Connection timed out");
            }
            else if(error)
            {
                throw boost::system::system_error(error);
            }
        }
    );

    this->_service.run_one();
    this->_service.reset();

    this->_stop_deadline();

    return data;
}

void
Transport
::write(std::string const & data)
{
    if(!this->is_open())
    {
        throw Exception("Not connected");
    }

    this->_start_deadline();
    boost::asio::async_write(
        *this->_socket, boost::asio::buffer(data),
        [](boost::system::error_code const & error, std::size_t)
        {
            if(error == boost::asio::error::operation_aborted)
            {
                throw Exception("Connection timed out");
            }
            else if(error)
            {
                throw boost::system::system_error(error);
            }
        });

    this->_service.run_one();
    this->_service.reset();
    this->_stop_deadline();
}

void
Transport
::_start_deadline()
{
    this->_deadline.expires_from_now(this->_timeout);
    this->_deadline.async_wait(
        [this](boost::system::error_code const & error)
        {
            if(!error)
            {
                this->close();
            }
            else if(error == boost::asio::error::operation_aborted)
            {
                // Do nothing.
            }
            else
            {
                throw boost::system::system_error(error);
            }
        }
    );
}

void
Transport
::_stop_deadline()
{
    this->_deadline.cancel();
    this->_deadline.expires_at(boost::posix_time::pos_infin);
}

}

}
