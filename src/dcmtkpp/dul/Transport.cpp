/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/dul/Transport.h"

#include <iterator>
#include <memory>
#include <string>

#include <boost/asio.hpp>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

namespace dul
{

Transport
::Transport()
: _io_service(), _socket(nullptr)
{
    // Nothing else
}

void
Transport
::connect(Socket::endpoint_type const & peer_endpoint)
{
    if(this->_socket != nullptr)
    {
        throw Exception("Already connected");
    }

    this->_socket = std::make_shared<Socket>(this->_io_service);
    this->_socket->connect(peer_endpoint);
}

void
Transport
::receive(Socket::endpoint_type const & endpoint)
{
    if(this->_socket != nullptr)
    {
        throw Exception("Already connected");
    }

    this->_socket = std::make_shared<Socket>(this->_io_service);
    // FIXME: should the acceptor scope be Transport instead of Transport::receive?
    boost::asio::ip::tcp::acceptor acceptor(this->_io_service, endpoint);
    acceptor.accept(*this->_socket);
}

void
Transport
::close()
{
    if(this->_socket == nullptr)
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
    if(this->_socket == nullptr)
    {
        throw Exception("Not connected");
    }

    std::string data;
    bool done=false;
    while(!done)
    {
        // FIXME: chunk size
        std::string bytes(std::min<int>(length, 256), '\0');
        std::size_t read=0;
        try
        {
            read = this->_socket->read_some(
                boost::asio::buffer(&bytes[0], bytes.size()));
        }
        catch(boost::system::system_error const & e)
        {
            if(e.code() == boost::asio::error::eof)
            {
                done = true;
            }
            else
            {
                throw;
            }
        }

        std::copy(
            bytes.begin(), bytes.begin()+read, std::back_inserter(data));

        if(data.size() >= length)
        {
            done = true;
        }
    }

    return data;
}

void
Transport
::write(std::string const & data)
{
    if(this->_socket == nullptr)
    {
        throw Exception("Not connected");
    }

    this->_socket->write_some(boost::asio::buffer(data));
}

}

}
