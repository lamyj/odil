/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "MessageSender.h"

#include <cstdint>
#include <functional>
#include <mutex>
#include <set>
#include <string>
#include <vector>

#include <boost/signals2.hpp>

#include "odil/odil.h"
#include "odil/dul/Connection.h"
#include "odil/dul/PDataTF.h"
#include "odil/dul/PDU.h"
#include "odil/message/Message.h"
#include "odil/StringStream.h"
#include "odil/Writer.h"

namespace odil
{

MessageSender
::MessageSender(
    dul::Connection & connection, std::function<void()> success_handler, 
    std::function<void(dul::PDU::Pointer, boost::system::error_code)> error_handler)
: _connection(connection), success_handler(success_handler), 
    error_handler(error_handler)
{
    // Nothing else
}

void
MessageSender
::operator()(
    std::shared_ptr<message::Message const> message,
    std::string const & transfer_syntax, uint8_t context_id, 
    uint32_t maximum_length)
{
    this->_split_message(message, transfer_syntax, context_id, maximum_length);

    std::lock_guard<std::mutex> lock(this->_mutex);

    if(this->_connections.empty())
    {
        this->_connections.emplace_back(this->_connection.sent.connect(
            [&](dul::PDU::Pointer pdu) { this->_pdu_sent(pdu); }));
        this->_connections.emplace_back(
            this->_connection.a_abort.indication.connect([&](dul::AAbort::Pointer pdu) {
                this->_on_error(pdu, boost::system::error_code());
            }));
        this->_connections.emplace_back(
            this->_connection.transport_closed.indication.connect([&]() {
                this->_on_error(
                    nullptr, 
                    boost::system::errc::make_error_code(
                        boost::system::errc::connection_reset));
            }));
        this->_connections.emplace_back(
            this->_connection.transport_error.indication.connect([&](boost::system::error_code error) {
                this->_on_error(nullptr, error);
            }));
    }

    for(auto const & pdu: this->_to_send)
    {
        this->_connection.send(pdu);
    }
}

void
MessageSender
::_split_message(
    std::shared_ptr<message::Message const> message,
    std::string const & transfer_syntax, uint8_t context_id, 
    uint32_t maximum_length)
{
    std::vector<dul::PDataTF::PresentationDataValueItem> pdv_items;

    std::string command_buffer;
    OStringStream command_stream(command_buffer);
    Writer command_writer(
        command_stream, registry::ImplicitVRLittleEndian, // implicit vr for command
        Writer::ItemEncoding::ExplicitLength, true); // true for Command
    command_writer.write_data_set(message->get_command_set());
    command_stream.flush();
    pdv_items.emplace_back(context_id, 3, command_buffer);
    
    if(message->has_data_set())
    {
        // Serialize data set
        std::string data_buffer;
        OStringStream data_stream(data_buffer);
        Writer data_writer(
            data_stream, transfer_syntax,
            Writer::ItemEncoding::ExplicitLength, false);
        data_writer.write_data_set(message->get_data_set());
        data_stream.flush();
        
        // We need an additional 12 bytes on top of the fragment
        auto current_length = command_buffer.size() + 12;
        if(!maximum_length 
            || (current_length + data_buffer.size() + 6 < maximum_length))
        {
            // The whole data fits in a single PDU.
            pdv_items.emplace_back(context_id, 2, data_buffer);
            this->_to_send.emplace(std::make_shared<dul::PDataTF>(pdv_items));
        }
        else // We have to fragment into multiple PDUs
        {
            // Each PDU requires 6 bytes for the headers
            auto available = maximum_length - 6 - current_length;
            int64_t remaining = data_buffer.size();
            std::size_t offset = 0;

            if(available > 0) // Send some data with the command set
            {
                remaining -= available;
                pdv_items.emplace_back(
                    context_id, (remaining > 0 ? 0 : 2), 
                    data_buffer.substr(0, available));
                offset += available;
            }

            this->_to_send.emplace(std::make_shared<dul::PDataTF>(pdv_items));

            // Add 6 bytes in case some software do not take into account the 
            // size of the header when allocating their buffer
            available = maximum_length - 6;
            while(remaining > 0)
            {
                remaining -= available;
                pdv_items.clear();
                pdv_items.emplace_back(
                    context_id, (remaining > 0 ? 0 : 2), 
                    data_buffer.substr(offset, available));
                offset += available;
                
                this->_to_send.emplace(std::make_shared<dul::PDataTF>(pdv_items));
            }
        }
    }
    else
    {
        this->_to_send.emplace(std::make_shared<dul::PDataTF>(pdv_items));
    }
}

void
MessageSender
::_pdu_sent(dul::PDU::Pointer pdu)
{
    // Check whether the PDU belongs to the current object.
    auto p_data_tf = std::dynamic_pointer_cast<dul::PDataTF>(pdu);
    if(!p_data_tf)
    {
        return;
    }

    std::lock_guard<std::mutex> lock(this->_mutex);

    // NOTE: if _pdu_sent and _on_error are called almost simultaneously, the
    // slots will have been disconnected by time we can lock the mutex. In this
    // case, we must not handle the sent PDU.
    if(this->_connections.empty())
    {
        return;
    }

    auto const it = this->_to_send.find(p_data_tf);
    if(it == this->_to_send.end())
    {
        return;
    }
    
    this->_to_send.erase(it);

    // Check whether all requested PDUs have been sent.
    if(this->_to_send.empty())
    {
        for(auto & connection: this->_connections)
        {
            connection.disconnect();
        }
        this->_connections.clear();

        this->success_handler();
    }
}

void
MessageSender
::_on_error(dul::PDU::Pointer pdu, boost::system::error_code error)
{
    std::lock_guard<std::mutex> lock(this->_mutex);

    // NOTE: if _pdu_sent and _on_error are called almost simultaneously, the
    // slots will have been disconnected by time we can lock the mutex. In this
    // case, we must not handle the error.
    if(this->_connections.empty())
    {
        return;
    }

    for(auto & connection: this->_connections)
    {
        connection.disconnect();
    }
    this->_connections.clear();

    
    this->_to_send.clear();
    
    this->error_handler(pdu, error);
}

}
