/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "MessageReceiver.h"

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include <boost/signals2.hpp>

#include "odil/DataSet.h"
#include "odil/dul/Connection.h"
#include "odil/dul/PDataTF.h"
#include "odil/message/Message.h"
#include "odil/odil.h"
#include "odil/Reader.h"
#include "odil/registry.h"
#include "odil/StringStream.h"

namespace odil
{

MessageReceiver
::MessageReceiver(
    dul::Connection & connection,
    std::map<uint8_t, std::string> const & transfer_syntaxes_by_id,
    std::function<void(std::shared_ptr<message::Message>)> success_handler,
    std::function<void(dul::PDU::Pointer, boost::system::error_code)> error_handler)
: _connection(connection), _transfer_syntaxes_by_id(transfer_syntaxes_by_id), 
    _presentation_context_id(0),
    success_handler(success_handler), error_handler(error_handler)
{
    // Nothing else.
}

void
MessageReceiver
::operator()()
{
    std::lock_guard<std::mutex> lock(this->_mutex);

    if(this->_connections.empty())
    {
        this->_connections.emplace_back(this->_connection.p_data.indication.connect(
            boost::bind(&MessageReceiver::_on_p_data_tf, this, _1)));
        
        this->_connections.emplace_back(this->_connection.a_abort.indication.connect(
            boost::bind(
                &MessageReceiver::_on_error, this, _1, 
                boost::system::error_code())));

        this->_connections.emplace_back(this->_connection.transport_closed.indication.connect(
            boost::bind(
                &MessageReceiver::_on_error, this, nullptr, 
                boost::system::errc::make_error_code(boost::system::errc::connection_reset))));

        this->_connections.emplace_back(this->_connection.transport_error.indication.connect(
            boost::bind(&MessageReceiver::_on_error, this, nullptr, _1)));
    }
}

void
MessageReceiver
::_on_p_data_tf(dul::PDataTF::Pointer pdu)
{
    for(auto const & pdv: pdu->get_pdv_items())
    {
        this->_presentation_context_id = pdv.get_presentation_context_id();

        // Check if this is the last command or data PDV
        auto & received =
            pdv.is_command()?this->_command_received:this->_data_set_received;
        received |= pdv.is_last_fragment();

        // Accumulate incoming PDVs in command or data buffer
        auto & buffer = 
            pdv.is_command()?this->_command_buffer:this->_data_set_buffer;
        buffer.append(pdv.get_fragment());

        if(this->_command_received && !this->_command)
        {
            IStringStream istream(
                &this->_command_buffer[0], this->_command_buffer.size());
            Reader reader(istream, registry::ImplicitVRLittleEndian);
            this->_command = reader.read_data_set();
        }
    }

    bool has_data_set = (
        this->_command 
        && this->_command->as_int(registry::CommandDataSetType, 0) 
            != message::Message::DataSetType::ABSENT);
    if(has_data_set && this->_data_set_received)
    {
        auto const transfer_syntax_it =
            this->_transfer_syntaxes_by_id.find(this->_presentation_context_id);
        if(transfer_syntax_it == this->_transfer_syntaxes_by_id.end())
        {
            throw Exception("No such Presentation Context ID");
        }

        IStringStream istream(
            &this->_data_set_buffer[0], this->_data_set_buffer.size());
        Reader reader(istream, transfer_syntax_it->second);
        this->_data_set = reader.read_data_set();
    }

    if(this->_command && (!has_data_set || this->_data_set_received))
    {
        std::lock_guard<std::mutex> lock(this->_mutex);

        for(auto & c: this->_connections)
        {
            c.disconnect();
        }
        this->_connections.clear();

        auto message = std::make_shared<message::Message>(
            this->_command, this->_data_set);

        this->success_handler(message);
    }
}

void
MessageReceiver
::_on_error(dul::PDU::Pointer pdu, boost::system::error_code error)
{
    std::lock_guard<std::mutex> lock(this->_mutex);

    // NOTE: if _on_pdata_tf and _on_error are called almost simultaneously, the
    // slots will have been disconnected by time we can lock the mutex. In this
    // case, we must not handle the sent error.
    if(this->_connections.empty())
    {
        return;
    }

    for(auto & c: this->_connections)
    {
        c.disconnect();
    }
    this->_connections.clear();

    this->error_handler(pdu, error);
}

}
