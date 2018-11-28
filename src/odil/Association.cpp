/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Association.h"

#include <algorithm>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "odil/AssociationAcceptor.h"
#include "odil/AssociationAborted.h"
#include "odil/AssociationParameters.h"
#include "odil/AssociationReceiver.h"
#include "odil/AssociationRequester.h"
#include "odil/Exception.h"
#include "odil/dul/Connection.h"
#include "odil/message/Message.h"
#include "odil/MessageReceiver.h"
#include "odil/MessageSender.h"
#include "odil/dul/AAbort.h"
#include "odil/dul/AAssociateAC.h"
#include "odil/dul/AAssociateRJ.h"
#include "odil/dul/AAssociateRQ.h"
#include "odil/dul/AReleaseRP.h"
#include "odil/dul/AReleaseRQ.h"

namespace odil
{

Association
::Association()
: _own_service(std::make_shared<boost::asio::io_service>()), _service(*_own_service),
  _socket(_service), _connection(_socket), 
  _peer_host(""), _peer_port(104), _association_parameters(),
  _transfer_syntaxes_by_abstract_syntax(), _transfer_syntaxes_by_id(),
  _next_message_id(0)
{
    // FIXME
    // this->set_tcp_timeout(boost::posix_time::pos_infin);
    // this->set_message_timeout(boost::posix_time::seconds(30));
}

Association
::Association(boost::asio::io_service & service)
: _own_service(nullptr), _service(service),
  _socket(_service), _connection(_socket), 
  _peer_host(""), _peer_port(104), _association_parameters(),
  _transfer_syntaxes_by_abstract_syntax(), _transfer_syntaxes_by_id(),
  _next_message_id(0)
{
    // FIXME
    // this->set_tcp_timeout(boost::posix_time::pos_infin);
    // this->set_message_timeout(boost::posix_time::seconds(30));
}

Association
::~Association()
{
    // Nothing to do, everything is taken care of by the StateMachine
}

boost::asio::io_service &
Association
::get_io_service()
{
    return this->_service;
}

boost::asio::ip::tcp::socket &
Association
::get_socket()
{
    return this->_socket;
}

std::string const &
Association
::get_peer_host() const
{
    return this->_peer_host;
}

void
Association
::set_peer_host(std::string const & host)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_peer_host = host;
}

uint16_t
Association
::get_peer_port() const
{
    return this->_peer_port;
}

void
Association
::set_peer_port(uint16_t port)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_peer_port = port;
}

AssociationParameters const &
Association
::get_parameters() const
{
    return this->_association_parameters;
}

AssociationParameters &
Association
::update_parameters()
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    return this->_association_parameters;
}

void
Association
::set_parameters(AssociationParameters const & value)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_association_parameters = value;
}

AssociationParameters const &
Association
::get_negotiated_parameters() const
{
    return this->_negotiated_parameters;
}

// FIXME
// Association::duration_type
// Association
// ::get_tcp_timeout() const
// {
    
//     return this->_state_machine.get_transport().get_timeout();
// }

// FIXME
// void
// Association
// ::set_tcp_timeout(duration_type const & duration)
// {
//     this->_state_machine.get_transport().set_timeout(duration);
// }

// FIXME
// Association::duration_type
// Association
// ::get_message_timeout() const
// {
//     return this->_state_machine.get_timeout();
// }

// FIXME
// void
// Association
// ::set_message_timeout(duration_type const & duration)
// {
//     this->_state_machine.set_timeout(duration);
// }

bool
Association
::is_associated() const
{
    return (this->_connection.get_status() == dul::Connection::Status::DataTransfer);
}

void
Association
::associate()
{
    bool done = false;
    dul::PDU::Pointer pdu;
    boost::system::error_code error;
    auto success_handler = [&](dul::AAssociateAC::Pointer) { 
        done = true; 
    };
    auto error_handler = [&](dul::PDU::Pointer p, boost::system::error_code e) {
        done = true;
        pdu = p;
        error = e;
    };
    this->associate(success_handler, error_handler);
    
    while(!done)
    {
        this->_connection.socket.get_io_service().run_one();
    }

    if(pdu)
    {
        auto rejection = std::dynamic_pointer_cast<dul::AAssociateRJ>(pdu);
        auto abort_ = std::dynamic_pointer_cast<dul::AAbort>(pdu);
        if(rejection)
        {
            throw Exception("Association rejected");
        }
        else if(abort_)
        {
            throw AssociationAborted(abort_->get_source(), abort_->get_reason());
        }
        else
        {
            throw Exception("Association failed (unknown PDU received)");
        }
    }
    else if(error)
    {
        throw Exception("Association failed: "+error.message());
    }
}

void
Association
::associate(
    std::function<void(dul::AAssociateAC::Pointer)> success_handler, 
    ErrorHandler error_handler)
{
    this->_association_requester = std::make_shared<AssociationRequester>(
        this->get_io_service(), this->_connection, 
        success_handler, error_handler);
    
    boost::asio::ip::tcp::resolver resolver(this->get_io_service());
    boost::asio::ip::tcp::resolver::query const query(
        this->_peer_host, std::to_string(this->_peer_port));
    auto const endpoint_it = resolver.resolve(query);
    if(endpoint_it.empty())
    {
        throw Exception("Cannot resolve peer host: "+this->_peer_host);
    }
    boost::asio::ip::tcp::endpoint endpoint(*endpoint_it);

    auto const request =
        std::make_shared<dul::AAssociateRQ>(
            this->_association_parameters.as_a_associate_rq());
    
    (*this->_association_requester)(endpoint, request);
}

void
Association
::receive_association(
    boost::asio::ip::tcp const & protocol, unsigned short port,
    AssociationAcceptor acceptor)
{
    bool done = false;
    auto success_handler = [&](dul::PDU::Pointer pdu) { 
        done = true;

        auto const reject = std::dynamic_pointer_cast<dul::AAssociateRJ>(pdu);
        if(reject)
        {
            throw AssociationRejected(
                reject->get_result(), reject->get_source(), reject->get_reason());
        }
        else
        {
            throw Exception("Could not receive association (unknown PDU)");
        }
    };
    auto const error_handler = [&](dul::PDU::Pointer pdu, boost::system::error_code error) {
        done = true;

        
        auto const abort_ = std::dynamic_pointer_cast<dul::AAbort>(pdu);
        if(abort_)
        {
            throw AssociationAborted(abort_->get_source(), abort_->get_reason());
        }
        else if(error)
        {
            throw Exception("Could not receive association: "+error.message());
        }
        else
        {
            throw Exception("Could not receive association (unknown reason)");
        }
    };
    this->receive_association(protocol, port, success_handler, error_handler);

    while(!done)
    {
        this->_connection.socket.get_io_service().run_one();
    }
}

void 
Association
::receive_association(
    boost::asio::ip::tcp const & protocol, unsigned short port,
    std::function<void(dul::PDU::Pointer)> success_handler, 
    ErrorHandler error_handler,
    AssociationAcceptor acceptor)
{
    this->_association_receiver = std::make_shared<AssociationReceiver>(
        this->get_io_service(), this->_connection, 
        success_handler, error_handler);
    
    boost::asio::ip::tcp::endpoint endpoint(protocol, port);

    (*this->_association_receiver)(endpoint);
}

void
Association
::release()
{
    bool done = false;
    dul::PDU::Pointer pdu;
    boost::system::error_code error;

    auto success_handler = [&](Association &) { done = true; };
    auto error_handler = [&](dul::PDU::Pointer p, boost::system::error_code e) {
        done = true;
        pdu = p;
        error = e;
    };

    this->release(success_handler, error_handler);

    while(!done && !pdu && !error)
    {
        this->_connection.socket.get_io_service().run_one();
    }

    if(pdu)
    {
        auto abort_ = std::dynamic_pointer_cast<dul::AAbort>(pdu);
        if(abort_)
        {
            throw AssociationAborted(abort_->get_source(), abort_->get_reason());
        }
        else
        {
            throw Exception("Association release failed (unknown PDU received)");
        }
    }
    else if(error)
    {
        throw Exception("Association release failed: "+error.message());
    }
}

void
Association
::release(
    std::function<void(Association &)> success_handler,
    ErrorHandler error_handler)
{
    // FIXME: should also be handled by a specific object
    this->_release_connections.emplace_back(this->_connection.a_release.confirmation.connect(
        [&](dul::AReleaseRP::Pointer) {
            for(auto const & c: this->_release_connections) 
            { 
                c.disconnect();
            };
            this->_release_connections.clear();

            success_handler(*this);
        }));
    this->_release_connections.emplace_back(this->_connection.a_abort.indication.connect(
        [&](dul::AAbort::Pointer pdu) {
            for(auto const & c: this->_release_connections) 
            { 
                c.disconnect();
            };
            this->_release_connections.clear();
            
            error_handler(pdu, boost::system::error_code());
        }));
    this->_release_connections.emplace_back(this->_connection.transport_error.indication.connect(
        [&](boost::system::error_code error) {
            for(auto const & c: this->_release_connections) 
            { 
                c.disconnect();
            };
            this->_release_connections.clear();

            error_handler(nullptr, error);
        }
    ));
    this->_release_connections.emplace_back(this->_connection.transport_closed.indication.connect(
        [&]() {
            for(auto const & c: this->_release_connections) 
            { 
                c.disconnect();
            };
            this->_release_connections.clear();

            error_handler(
                nullptr, 
                boost::system::errc::make_error_code(boost::system::errc::connection_reset));
        }));

    this->_connection.send(std::make_shared<dul::AReleaseRQ>());
}

void
Association
::abort(int source, int reason)
{
    bool done = false;
    auto close_handler = [&]() { done = true; };
    this->abort(source, reason, close_handler);
    while(!done)
    {
        this->_connection.socket.get_io_service().run_one();
    }
}

void 
Association
::abort(int source, int reason, std::function<void()> close_handler)
{
    // FIXME: should also be handled by a specific object
    this->_abort_connections.emplace_back(this->_connection.transport_closed.indication.connect(
        [&](){
            for(auto const & c: this->_abort_connections) 
            { 
                c.disconnect();
            };
            this->_abort_connections.clear();

            close_handler();
        }));

    auto pdu = std::make_shared<dul::AAbort>(source, reason);
    this->_connection.send(pdu);
}

std::shared_ptr<message::Message>
Association
::receive_message()
{
    std::shared_ptr<message::Message> message;
    dul::PDU::Pointer pdu;
    boost::system::error_code error;

    auto message_handler = [&](std::shared_ptr<message::Message> m) {
        message = m;
    };
    auto error_handler = [&](dul::PDU::Pointer p, boost::system::error_code e) {
        pdu = p;
        error = e;
    };

    this->receive_message(message_handler, error_handler);

    while(!message && !pdu && !error)
    {
        this->_connection.socket.get_io_service().run_one();
    }

    if(pdu)
    {
        auto abort_ = std::dynamic_pointer_cast<dul::AAbort>(pdu);
        if(abort_)
        {
            throw AssociationAborted(abort_->get_source(), abort_->get_reason());
        }
        else
        {
            throw Exception(
                "Could not receive message, received PDU of type "
                +std::to_string(pdu->get_pdu_type()));
        }
    }
    else if(error)
    {
        throw Exception("Could not receive message: "+error.message());
    }

    return message;
}

void
Association
::receive_message(
    std::function<void(std::shared_ptr<message::Message>)> message_handler,
    ErrorHandler error_handler)
{
    this->_message_receiver = std::make_shared<MessageReceiver>(
        this->_connection, this->_transfer_syntaxes_by_id,
        message_handler, error_handler);
    (*this->_message_receiver)();
}

void
Association
::send_message(
    std::shared_ptr<message::Message const> message,
    std::string const & abstract_syntax)
{
    bool sent = false;
    dul::PDU::Pointer pdu;
    boost::system::error_code error;

    auto success_handler = [&]() { sent = true; };
    auto error_handler = [&](dul::PDU::Pointer p, boost::system::error_code e) {
        pdu = p;
        error = e;
    };

    this->send_message(message, abstract_syntax, success_handler, error_handler);

    while(!sent && !pdu && !error)
    {
        this->_connection.socket.get_io_service().run_one();
    }

    if(!sent)
    {
        if(pdu)
        {
            auto abort_ = std::dynamic_pointer_cast<dul::AAbort>(pdu);
            if(abort_)
            {
                throw AssociationAborted(
                    abort_->get_source(), abort_->get_reason());
            }
            else
            {
                throw Exception(
                    "Could not send message, received PDU of type "
                    + std::to_string(abort_->get_pdu_type()));
            }
        }
        else if(error)
        {
            throw Exception("Could not send message: "+error.message());
        }
        else
        {
            throw Exception("Could not send message (unknown reason)");
        }
    }
    // Otherwise, the message was sent sucessfully
}

void 
Association
::send_message(
    std::shared_ptr<message::Message const> message,
    std::string const & abstract_syntax,
    std::function<void()> success_handler, ErrorHandler error_handler)
{
    // WARNING: since this is asynchronous, we need a set of MessageSender
    // or we could handle this in MessageSender.
    this->_message_sender = std::make_shared<MessageSender>(
        this->_connection, success_handler, error_handler);
    auto const it = this->_transfer_syntaxes_by_abstract_syntax.find(abstract_syntax);
    if(it == this->_transfer_syntaxes_by_abstract_syntax.end())
    {
        throw Exception("No presentation context for "+abstract_syntax);
    }
    (*this->_message_sender)(
        message, it->second.second, it->second.first,
        this->_negotiated_parameters.get_maximum_length());
}

uint16_t
Association
::next_message_id()
{
    return ++this->_next_message_id;
}

}
