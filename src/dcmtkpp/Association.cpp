/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
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

#include "dcmtkpp/AssociationParameters.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/uid.h"
#include "dcmtkpp/dul/StateMachine.h"
#include "dcmtkpp/message/Message.h"
#include "dcmtkpp/pdu/AAbort.h"
#include "dcmtkpp/pdu/AAssociate.h"
#include "dcmtkpp/pdu/AAssociateRJ.h"
#include "dcmtkpp/pdu/AReleaseRP.h"
#include "dcmtkpp/pdu/AReleaseRQ.h"
#include "dcmtkpp/pdu/ImplementationClassUID.h"
#include "dcmtkpp/pdu/ImplementationVersionName.h"
#include "dcmtkpp/pdu/PDataTF.h"
#include "dcmtkpp/pdu/PresentationContextAC.h"
#include "dcmtkpp/pdu/PresentationContextRQ.h"
#include "dcmtkpp/pdu/RoleSelection.h"
#include "dcmtkpp/pdu/UserIdentityRQ.h"
#include "dcmtkpp/pdu/UserInformation.h"
#include "dcmtkpp/Reader.h"
#include "dcmtkpp/Writer.h"

namespace dcmtkpp
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
    return this->_state_machine.get_transport().is_open();
}

void
Association
::associate()
{
    boost::asio::ip::tcp::resolver resolver(
        this->_state_machine.get_transport().get_service());
    boost::asio::ip::tcp::resolver::query const query(this->_peer_host, "");
    auto const endpoint_it = resolver.resolve(query);

    dul::EventData data;
    data.peer_endpoint = *endpoint_it;
    data.peer_endpoint.port(this->_peer_port);

    auto const request =
        std::make_shared<pdu::AAssociateRQ>(
            this->_association_parameters.as_a_associate_rq());

    data.pdu = request;

    this->_state_machine.send_pdu(data);
    this->_state_machine.receive_pdu(data);

    if(data.pdu == nullptr)
    {
        throw Exception("No response received");
    }
    else
    {
        auto const acceptation = std::dynamic_pointer_cast<pdu::AAssociateAC>(data.pdu);
        auto const rejection = std::dynamic_pointer_cast<pdu::AAssociateRJ>(data.pdu);
        if(acceptation != nullptr)
        {
            AssociationParameters negotiated_parameters(
                *acceptation, this->_association_parameters);

            this->_transfer_syntaxes_by_abstract_syntax.clear();
            this->_transfer_syntaxes_by_id.clear();

            for(auto const & pc: negotiated_parameters.get_presentation_contexts())
            {
                if(pc.result != AssociationParameters::PresentationContext::Result::Acceptance)
                {
                    continue;
                }

                this->_transfer_syntaxes_by_id[pc.id] = pc.transfer_syntaxes[0];
                this->_transfer_syntaxes_by_abstract_syntax[pc.abstract_syntax] =
                    {pc.id, pc.transfer_syntaxes[0]};
            }
        }
        else if(rejection != nullptr)
        {
            throw Exception("Association rejected");
        }
        else
        {
            throw Exception("Invalid response");
        }
    }
}

void
Association
::receive_association(
    boost::asio::ip::tcp const & protocol, unsigned short port,
    AssociationAcceptor acceptor)
{
    dul::EventData data;
    data.peer_endpoint = dul::Transport::Socket::endpoint_type(protocol, port);

    this->_state_machine.set_association_acceptor(acceptor);

    this->_state_machine.receive(data);
    this->_state_machine.receive_pdu(data);

    if(data.pdu == NULL)
    {
        // We have rejected the request
        //return false;
    }
    else
    {
        auto const & request = std::dynamic_pointer_cast<pdu::AAssociateRQ>(data.pdu);
        if(request == nullptr)
        {
            throw Exception("Invalid response");
        }

        auto const endpoint =
            this->_state_machine.get_transport().get_socket()->remote_endpoint();
        this->_peer_host = endpoint.address().to_string();
        this->_peer_port = endpoint.port();

        auto const negotiated_parameters = data.association_parameters;

        this->_transfer_syntaxes_by_abstract_syntax.clear();
        this->_transfer_syntaxes_by_id.clear();

        for(auto const & pc: negotiated_parameters.get_presentation_contexts())
        {
            if(pc.result != AssociationParameters::PresentationContext::Result::Acceptance)
            {
                continue;
            }

            this->_transfer_syntaxes_by_id[pc.id] = pc.transfer_syntaxes[0];
            this->_transfer_syntaxes_by_abstract_syntax[pc.abstract_syntax] =
                {pc.id, pc.transfer_syntaxes[0]};
        }

        data.pdu = std::make_shared<pdu::AAssociateAC>(
            negotiated_parameters.as_a_associate_ac());
        this->_state_machine.send_pdu(data);
    }
}

void
Association
::release()
{
    if(!this->is_associated())
    {
        throw Exception("Not associated");
    }

    auto pdu = std::make_shared<pdu::AReleaseRQ>();
    dul::EventData data;
    data.pdu = pdu;
    this->_state_machine.send_pdu(data);
    this->_state_machine.receive_pdu(data);

    auto const reply = std::dynamic_pointer_cast<pdu::AReleaseRP>(data.pdu);
    if(reply == nullptr)
    {
        // Invalid response, accept it nevertheless.
    }
}

void
Association
::abort(int source, int reason)
{
    if(!this->is_associated())
    {
        throw Exception("Not associated");
    }

    auto pdu = std::make_shared<pdu::AAbort>(source, reason);
    dul::EventData data;
    data.pdu = pdu;
    this->_state_machine.send_pdu(data);
}

message::Message
Association
::receive_message()
{
    bool done = false;
    int presentation_context_id;
    bool command_set_received=false;
    bool has_data_set=true;
    bool data_set_received=false;

    DataSet command_set;
    std::stringstream command_stream, data_stream;

    while(!done)
    {
        dul::EventData data;
        data.pdu = nullptr;
        this->_state_machine.receive_pdu(data);

        auto const a_release_rq = std::dynamic_pointer_cast<pdu::AReleaseRQ>(data.pdu);
        if(a_release_rq != nullptr)
        {
            data.pdu = std::make_shared<pdu::AReleaseRP>();
            this->_state_machine.send_pdu(data);
            throw AssociationReleased();
        }

        auto const a_abort = std::dynamic_pointer_cast<pdu::AAbort>(data.pdu);
        if(a_abort != nullptr)
        {
            throw AssociationAborted(a_abort->get_source(), a_abort->get_reason());
        }

        auto const p_data_tf = std::dynamic_pointer_cast<pdu::PDataTF>(data.pdu);

        if(p_data_tf == nullptr)
        {
            throw Exception("Invalid PDU received");
        }

        for(auto const & pdv: p_data_tf->get_pdv_items())
        {
            presentation_context_id = pdv.get_presentation_context_id();
            bool & received =
                pdv.is_command()?command_set_received:data_set_received;
            received |= pdv.is_last_fragment();

            auto const & fragment_data = pdv.get_fragment();

            std::stringstream  & stream =
                pdv.is_command()?command_stream:data_stream;
            stream.write(&fragment_data[0], fragment_data.size());

            if(command_set_received && command_set.empty())
            {
                Reader reader(command_stream, registry::ImplicitVRLittleEndian);
                command_set = reader.read_data_set();
                auto const value =
                    command_set.as_int(registry::CommandDataSetType, 0);

                if(value == message::Message::DataSetType::ABSENT)
                {
                    has_data_set = false;
                }
            }
        }

        done = command_set_received && (!has_data_set || data_set_received);
    }

    if(has_data_set)
    {
        auto const transfer_syntax_it =
            this->_transfer_syntaxes_by_id.find(presentation_context_id);
        if(transfer_syntax_it == this->_transfer_syntaxes_by_id.end())
        {
            throw Exception("No such Presentation Context ID");
        }

        Reader reader(data_stream, transfer_syntax_it->second);
        auto const data_set = reader.read_data_set();

        return message::Message(command_set, data_set);
    }
    else
    {
        return message::Message(command_set);
    }
}

void
Association
::send_message(
    message::Message const & message, std::string const & abstract_syntax)
{
    auto const transfer_syntax_it =
        this->_transfer_syntaxes_by_abstract_syntax.find(abstract_syntax);
    if(transfer_syntax_it == this->_transfer_syntaxes_by_abstract_syntax.end())
    {
        throw Exception("No transfer syntax for "+abstract_syntax);
    }

    auto const & transfer_syntax = transfer_syntax_it->second.second;
    auto const & id = transfer_syntax_it->second.first;

    std::vector<pdu::PDataTF::PresentationDataValueItem> pdv_items;

    std::ostringstream command_stream;
    Writer command_writer(
        command_stream, registry::ImplicitVRLittleEndian, // implicit vr for command
        Writer::ItemEncoding::ExplicitLength, true); // true for Command
    command_writer.write_data_set(message.get_command_set());
    pdv_items.push_back(
        pdu::PDataTF::PresentationDataValueItem(id, 3, command_stream.str()));

    if (message.has_data_set())
    {
        std::ostringstream data_stream;
        Writer data_writer(
            data_stream, transfer_syntax,
            Writer::ItemEncoding::ExplicitLength, false);
        data_writer.write_data_set(message.get_data_set());
        pdv_items.push_back(
            pdu::PDataTF::PresentationDataValueItem(
                transfer_syntax_it->second.first, 2, data_stream.str()));
    }

    auto pdu = std::make_shared<pdu::PDataTF>(pdv_items);

    dul::EventData data;
    data.pdu = pdu;

    this->_state_machine.send_pdu(data);
}

uint16_t
Association
::next_message_id()
{
    return ++this->_next_message_id;
}

}
