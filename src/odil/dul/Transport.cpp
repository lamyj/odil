/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/Transport.h"

#include <memory>
#include <string>

#include <boost/asio.hpp>
#include <boost/date_time.hpp>

#include "odil/Exception.h"

namespace odil
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

Transport::duration_type
Transport
::get_timeout() const
{
    return this->_timeout;
}

void
Transport
::set_timeout(duration_type timeout)
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

    auto source = Source::NONE;
    boost::system::error_code error;
    this->_start_deadline(source, error);

    this->_socket = std::make_shared<Socket>(this->_service);
    this->_socket->async_connect(
        peer_endpoint,
        [&source,&error](boost::system::error_code const & e)
        {
            source = Source::OPERATION;
            error = e;
        }
    );

    this->_run(source, error);
}

void
Transport
::receive(Socket::endpoint_type const & endpoint)
{
    if(this->is_open())
    {
        throw Exception("Already connected");
    }

    auto source = Source::NONE;
    boost::system::error_code error;
    this->_start_deadline(source, error);

    this->_socket = std::make_shared<Socket>(this->_service);
    this->_acceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(
        this->_service, endpoint);
    boost::asio::socket_base::reuse_address option(true);
    this->_acceptor->set_option(option);
    this->_acceptor->async_accept(
        *this->_socket,
        [&source,&error](boost::system::error_code const & e)
        {
            source = Source::OPERATION;
            error = e;
        }
    );

    this->_run(source, error);

    this->_acceptor = nullptr;
}

void
Transport
::close()
{
    if(this->_acceptor && this->_acceptor->is_open())
    {
        this->_acceptor->close();
        this->_acceptor = nullptr;
    }
    if(this->is_open())
    {
        this->_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        this->_socket->close();
        this->_socket = nullptr;
    }
}

std::string
Transport
::read(std::size_t length)
{
    if(!this->is_open())
    {
        throw Exception("Not connected");
    }

    std::string data(length, 'a');

    auto source = Source::NONE;
    boost::system::error_code error;
    this->_start_deadline(source, error);

    boost::asio::async_read(
        *this->_socket,
        boost::asio::buffer(&data[0], data.size()),
        [&source,&error](boost::system::error_code const & e, std::size_t)
        {
            source = Source::OPERATION;
            error = e;
        }
    );

    this->_run(source, error);

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

    auto source = Source::NONE;
    boost::system::error_code error;
    this->_start_deadline(source, error);

    boost::asio::async_write(
        *this->_socket, boost::asio::buffer(data),
        [&source,&error](boost::system::error_code const & e, std::size_t)
        {
            source = Source::OPERATION;
            error = e;
        }
    );

    this->_run(source, error);
}

void
Transport
::_start_deadline(Source & source, boost::system::error_code & error)
{
    auto const canceled = this->_deadline.expires_from_now(this->_timeout);
    if(canceled != 0)
    {
        throw Exception("TCP timer started with pending operations");
    }

    this->_deadline.async_wait(
        [&source,&error](boost::system::error_code const & e)
        {
            source = Source::TIMER;
            error = e;
        }
    );
}

void
Transport
::_stop_deadline()
{
    this->_deadline.expires_at(boost::posix_time::pos_infin);
}

void
Transport
::_run(Source & source, boost::system::error_code & error)
{
    // WARNING: it seems that run_one runs a *simple* operation, not a
    // *composed* operation, as is done by async_read/async_write
    while(source == Source::NONE)
    {
        auto const ran = this->_service.run_one();
        if(ran == 0)
        {
            throw Exception("No operations ran");
        }
        this->_service.reset();
    }

    if(source == Source::OPERATION)
    {
        if(error)
        {
            throw Exception("Operation error: "+error.message());
        }

        source = Source::NONE;
        this->_stop_deadline();

        while(source == Source::NONE)
        {
            auto const polled = this->_service.poll_one();
            if(polled == 0)
            {
                throw Exception("No operations polled");
            }
            this->_service.reset();
        }

        if(source != Source::TIMER)
        {
            throw Exception("Unknown event");
        }
        else if(error != boost::asio::error::operation_aborted)
        {
            throw Exception("TCP timer error: "+error.message());
        }
    }
    else if(source == Source::TIMER)
    {
        throw Exception("TCP time out");
    }
    else
    {
        throw Exception("Unknown source");
    }
}

}

}
