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

#include "odil/AssociationParameters.h"
#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/uid.h"
#include "odil/dul/Connection.h"
#include "odil/dul/StateMachine.h"
#include "odil/message/Message.h"
#include "odil/dul/AAbort.h"
#include "odil/dul/AAssociate.h"
#include "odil/dul/AAssociateRJ.h"
#include "odil/dul/AReleaseRP.h"
#include "odil/dul/AReleaseRQ.h"
#include "odil/dul/ImplementationClassUID.h"
#include "odil/dul/ImplementationVersionName.h"
#include "odil/dul/PDataTF.h"
#include "odil/dul/PresentationContextAC.h"
#include "odil/dul/PresentationContextRQ.h"
#include "odil/dul/RoleSelection.h"
#include "odil/dul/UserIdentityRQ.h"
#include "odil/dul/UserInformation.h"
#include "odil/Reader.h"
#include "odil/StringStream.h"
#include "odil/Writer.h"

namespace odil
{

Association
::Association()
: _state_machine(), _peer_host(""), _peer_port(104), _association_parameters(),
  _transfer_syntaxes_by_abstract_syntax(), _transfer_syntaxes_by_id(),
  _next_message_id(1)
{
    this->set_tcp_timeout(boost::posix_time::pos_infin);
    this->set_message_timeout(boost::posix_time::seconds(30));
}

Association
::Association(Association const & other)
: _state_machine(), _peer_host(other._peer_host), _peer_port(other._peer_port),
  _association_parameters(other._association_parameters),
  _transfer_syntaxes_by_abstract_syntax(), _transfer_syntaxes_by_id(),
  _next_message_id(other._next_message_id)
{
    this->set_tcp_timeout(other.get_tcp_timeout());
    this->set_message_timeout(other.get_message_timeout());
}

Association
::~Association()
{
    // Nothing to do, everything is taken care of by the StateMachine
}

dul::Transport &
Association
::get_transport()
{
    return this->_state_machine.get_transport();
}

Association &
Association
::operator=(Association const & other)
{
    if(this != &other)
    {
        this->set_peer_host(other.get_peer_host());
        this->set_peer_port(other.get_peer_port());
        this->set_parameters(other.get_parameters());
    }

    return *this;
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

Association::duration_type
Association
::get_tcp_timeout() const
{
    return this->_state_machine.get_transport().get_timeout();
}

void
Association
::set_tcp_timeout(duration_type const & duration)
{
    this->_state_machine.get_transport().set_timeout(duration);
}

Association::duration_type
Association
::get_message_timeout() const
{
    return this->_state_machine.get_timeout();
}

void
Association
::set_message_timeout(duration_type const & duration)
{
    this->_state_machine.set_timeout(duration);
}

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
    auto success_handler = [&](Association & association) { 
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
    std::function<void(Association &)> success_handler, 
    std::function<void(dul::PDU::Pointer, boost::system::error_code)> error_handler)
{
    this->_associate_connections.emplace_back(this->_connection.a_associate.confirmation.connect(
        [&](dul::PDU::Pointer pdu)
        {
            for(auto const & c: this->_associate_connections) 
            { 
                c.disconnect();
            };
            this->_associate_connections.clear();

            auto acceptation = std::dynamic_pointer_cast<dul::AAssociateAC>(pdu);
            auto rejection = std::dynamic_pointer_cast<dul::AAssociateRJ>(pdu);
            if(acceptation)
            {
                this->_negotiated_parameters = AssociationParameters(
                    *acceptation, this->_association_parameters);

                this->_transfer_syntaxes_by_abstract_syntax.clear();
                this->_transfer_syntaxes_by_id.clear();

                for(auto const & pc: this->_negotiated_parameters.get_presentation_contexts())
                {
                    if(pc.result != AssociationParameters::PresentationContext::Result::Acceptance)
                    {
                        continue;
                    }

                    this->_transfer_syntaxes_by_id[pc.id] = pc.transfer_syntaxes[0];
                    this->_transfer_syntaxes_by_abstract_syntax[pc.abstract_syntax] =
                        {pc.id, pc.transfer_syntaxes[0]};
                }
                
                success_handler(*this);
            }
            else if(rejection)
            {
                error_handler(rejection, boost::system::error_code());
            }
        }));
    this->_associate_connections.emplace_back(this->_connection.a_abort.indication.connect(
        [&](dul::PDU::Pointer pdu)
        {
            for(auto const & c: this->_associate_connections) 
            { 
                c.disconnect();
            };
            this->_associate_connections.clear();

            error_handler(pdu, boost::system::error_code());
        }));
    
    this->_associate_connections.emplace_back(this->_connection.transport_error.indication.connect(
        [&](boost::system::error_code error)
        {
            for(auto const & c: this->_associate_connections) 
            { 
                c.disconnect();
            };
            this->_associate_connections.clear();

            error_handler(nullptr, error);
        }));
    this->_associate_connections.emplace_back(this->_connection.transport_closed.indication.connect(
        [&]() 
        {
            for(auto const & c: this->_associate_connections) 
            { 
                c.disconnect();
            };
            this->_associate_connections.clear();

            error_handler(
                nullptr, 
                boost::system::errc::make_error_code(boost::system::errc::connection_reset)); 
        }));
    
    boost::asio::ip::tcp::resolver resolver(
        this->_state_machine.get_transport().get_service());
    boost::asio::ip::tcp::resolver::query const query(
        this->_peer_host, std::to_string(this->_peer_port));
    auto const endpoint_it = resolver.resolve(query);

    auto const request =
        std::make_shared<dul::AAssociateRQ>(
            this->_association_parameters.as_a_associate_rq());

    this->_connection.send(*endpoint_it, request);
}

void
Association
::receive_association(
    boost::asio::ip::tcp const & protocol, unsigned short port,
    AssociationAcceptor acceptor)
{
    bool done = false;
    auto success_handler = [&](Association &) { done = true; };
    auto const error_handler = [&](dul::PDU::Pointer pdu, boost::system::error_code error) {
        done = true;

        auto const reject = std::dynamic_pointer_cast<dul::AAssociateRJ>(pdu);
        auto const abort_ = std::dynamic_pointer_cast<dul::AAbort>(pdu);
        if(reject)
        {
            throw AssociationRejected(
                reject->get_result(), reject->get_source(), reject->get_reason());
        }
        else if(abort_)
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
    std::function<void(Association &)> success_handler,
    std::function<void(dul::PDU::Pointer, boost::system::error_code)> error_handler,
    AssociationAcceptor acceptor)
{
    std::vector<boost::signals2::connection> connections;
    
    this->_receive_association_connections.emplace_back(this->_connection.transport_error.indication.connect(
        [&](boost::system::error_code error)
        {
            for(auto const & c: this->_receive_association_connections) 
            { 
                c.disconnect();
            };
            this->_receive_association_connections.clear();

            error_handler(nullptr, error);
        }));
    this->_receive_association_connections.emplace_back(this->_connection.transport_closed.indication.connect(
        [&]()
        {
            for(auto const & c: this->_receive_association_connections) 
            { 
                c.disconnect();
            };
            this->_receive_association_connections.clear();

            error_handler(
                nullptr, 
                boost::system::errc::make_error_code(boost::system::errc::connection_reset));
        }));

    this->_connection.acceptor = [&](dul::AAssociateRQ::Pointer request) {
        dul::PDU::Pointer result;

        AssociationParameters negotiated_parameters;
        try
        {
            this->_negotiated_parameters = acceptor(AssociationParameters(*request));

            auto const endpoint = this->_connection.socket.remote_endpoint();
            this->_peer_host = endpoint.address().to_string();
            this->_peer_port = endpoint.port();

            this->_transfer_syntaxes_by_abstract_syntax.clear();
            this->_transfer_syntaxes_by_id.clear();

            for(auto const & pc: this->_negotiated_parameters.get_presentation_contexts())
            {
                if(pc.result != AssociationParameters::PresentationContext::Result::Acceptance)
                {
                    continue;
                }

                this->_transfer_syntaxes_by_id[pc.id] = pc.transfer_syntaxes[0];
                this->_transfer_syntaxes_by_abstract_syntax[pc.abstract_syntax] =
                    {pc.id, pc.transfer_syntaxes[0]};
            }

            result = std::make_shared<dul::AAssociateAC>(
                negotiated_parameters.as_a_associate_ac());
            success_handler(*this);
        }
        catch(AssociationRejected const & e)
        {
            result = std::make_shared<dul::AAssociateRJ>(
                e.get_result(), e.get_source(), e.get_reason());
            // TODO: what about transport errors?
            error_handler(result, boost::system::error_code());
        }

        return result;
    };
    
    boost::asio::ip::tcp::endpoint endpoint(protocol, port);
    boost::asio::ip::tcp::acceptor network_acceptor(
        this->_connection.socket.get_io_service(), endpoint);
    network_acceptor.async_accept(
        this->_connection.socket,
        [&](boost::system::error_code error) {
            this->_connection.transport_connection.indication(error);
        }
    );

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
    std::function<void(dul::PDU::Pointer, boost::system::error_code)> error_handler)
{
    
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
    bool done = false;
    int presentation_context_id;
    bool command_set_received=false;
    bool has_data_set=true;
    bool data_set_received=false;

    std::shared_ptr<DataSet> command_set;

    std::string command_buffer;
    std::string data_buffer;

    while(!done)
    {
        dul::EventData data;
        data.pdu = nullptr;
        this->_state_machine.receive_pdu(data);

        auto const a_release_rq = std::dynamic_pointer_cast<dul::AReleaseRQ>(data.pdu);
        if(a_release_rq != nullptr)
        {
            data.pdu = std::make_shared<dul::AReleaseRP>();
            this->_state_machine.send_pdu(data);
            throw AssociationReleased();
        }

        auto const a_abort = std::dynamic_pointer_cast<dul::AAbort>(data.pdu);
        if(a_abort != nullptr)
        {
            throw AssociationAborted(a_abort->get_source(), a_abort->get_reason());
        }

        auto const p_data_tf = std::dynamic_pointer_cast<dul::PDataTF>(data.pdu);

        if(p_data_tf == nullptr)
        {
            throw Exception("Invalid PDU received");
        }

        for(auto const & pdv: p_data_tf->get_pdv_items())
        {
            presentation_context_id = pdv.get_presentation_context_id();

            // Check if this is the last command or data PDV
            auto & received =
                pdv.is_command()?command_set_received:data_set_received;
            received |= pdv.is_last_fragment();

            // Accumulate incoming PDVs in command or data buffer
            auto & buffer = (pdv.is_command()?command_buffer:data_buffer);
            buffer.append(pdv.get_fragment());

            if(command_set_received && !command_set)
            {
                IStringStream istream(&command_buffer[0], command_buffer.size());
                Reader reader(istream, registry::ImplicitVRLittleEndian);
                command_set = reader.read_data_set();
                auto const value =
                    command_set->as_int(registry::CommandDataSetType, 0);

                if(value == message::Message::DataSetType::ABSENT)
                {
                    has_data_set = false;
                }
            }
        }

        done = command_set_received && (!has_data_set || data_set_received);
    }

    std::shared_ptr<DataSet> data_set;
    if(has_data_set)
    {
        auto const transfer_syntax_it =
            this->_transfer_syntaxes_by_id.find(presentation_context_id);
        if(transfer_syntax_it == this->_transfer_syntaxes_by_id.end())
        {
            throw Exception("No such Presentation Context ID");
        }

        IStringStream istream(&data_buffer[0], data_buffer.size());
        Reader reader(istream, transfer_syntax_it->second);
        data_set = reader.read_data_set();
    }
    return std::make_shared<message::Message>(command_set, data_set);
}

void
Association
::send_message(
    std::shared_ptr<message::Message const> message,
    std::string const & abstract_syntax)
{
    if(!this->is_associated())
    {
        throw Exception("Not associated");
    }
    
    auto const transfer_syntax_it =
        this->_transfer_syntaxes_by_abstract_syntax.find(abstract_syntax);
    if(transfer_syntax_it == this->_transfer_syntaxes_by_abstract_syntax.end())
    {
        throw Exception("No transfer syntax for "+abstract_syntax);
    }

    auto const & transfer_syntax = transfer_syntax_it->second.second;
    auto const & id = transfer_syntax_it->second.first;

    std::vector<dul::PDataTF::PresentationDataValueItem> pdv_items;

    std::string command_buffer;
    OStringStream command_stream(command_buffer);
    Writer command_writer(
        command_stream, registry::ImplicitVRLittleEndian, // implicit vr for command
        Writer::ItemEncoding::ExplicitLength, true); // true for Command
    command_writer.write_data_set(message->get_command_set());
    command_stream.flush();
    pdv_items.emplace_back(id, 3, command_buffer);

    if (message->has_data_set())
    {
        std::string data_buffer;
        OStringStream data_stream(data_buffer);
        Writer data_writer(
            data_stream, transfer_syntax,
            Writer::ItemEncoding::ExplicitLength, false);
        data_writer.write_data_set(message->get_data_set());
        data_stream.flush();

        auto const max_length = this->_negotiated_parameters.get_maximum_length();
        auto current_length = command_buffer.size() + 12; // 12 is the size of all that is added on top of the fragment
        if (!max_length 
            || (current_length + data_buffer.size() + 6 < max_length))
        {   // Can send all the buffer in one go
            pdv_items.emplace_back(transfer_syntax_it->second.first, 2, data_buffer);

            dul::EventData data;
            data.pdu = std::make_shared<dul::PDataTF>(pdv_items);
            this->_state_machine.send_pdu(data);
        }
        else // We have to fragment into multiple PDUs
        {
            auto available = max_length - 6 - current_length; // Need at least 6 bytes for the headers
            int64_t remaining = data_buffer.size();
            std::size_t offset = 0;

            if (available > 0) // Send some data with the command set
            {
                remaining -= available;
                pdv_items.emplace_back(transfer_syntax_it->second.first, (remaining > 0 ? 0 : 2), data_buffer.substr(0, available));
                offset += available;
            }

            auto pdu = std::make_shared<dul::PDataTF>(pdv_items);
            dul::EventData data;
            data.pdu = pdu;
            this->_state_machine.send_pdu(data);

            available = max_length - 6; // In case some software do not take into account the size of the header when allocating their buffer
            while (remaining > 0)
            {
                remaining -= available;
                pdv_items.clear();
                pdv_items.emplace_back(transfer_syntax_it->second.first, (remaining > 0 ? 0 : 2), data_buffer.substr(offset, available));
                offset += available;
                pdu->set_pdv_items(pdv_items);
                this->_state_machine.send_pdu(data);
            }
        }
    }
    else
    {
        dul::EventData data;
        data.pdu = std::make_shared<dul::PDataTF>(pdv_items);
        this->_state_machine.send_pdu(data);
    }
}

uint16_t
Association
::next_message_id()
{
    return ++this->_next_message_id;
}

AssociationReleased
::AssociationReleased()
: Exception("Association released")
{
    // Nothing else.
}

AssociationReleased
::~AssociationReleased() noexcept
{
    // Nothing to do.
}

AssociationAborted
::AssociationAborted(unsigned char source, unsigned char reason)
: Exception("Association aborted"), source(source), reason(reason)
{
    // Nothing else.
}

AssociationAborted
::~AssociationAborted() noexcept
{
    // Nothing to do.
}

}
