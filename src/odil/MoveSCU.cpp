/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/MoveSCU.h"

#include <chrono>
#include <functional>
#include <thread>
#include <vector>

#include "odil/Association.h"
#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/logging.h"
#include "odil/StoreSCP.h"
#include "odil/message/CMoveRequest.h"
#include "odil/message/CMoveResponse.h"
#include "odil/message/Message.h"

namespace odil
{

MoveSCU
::MoveSCU(Association & association)
: SCU(association), _move_destination(""), _incoming_port(0)
{
    // Nothing else.
}

std::string const &
MoveSCU
::get_move_destination() const
{
    return this->_move_destination;
}

void
MoveSCU
::set_move_destination(std::string const & move_destination)
{
    this->_move_destination = move_destination;
}

uint16_t
MoveSCU
::get_incoming_port() const
{
    return this->_incoming_port;
}

void
MoveSCU
::set_incoming_port(uint16_t port)
{
    this->_incoming_port = port;
}

void
MoveSCU
::move(std::shared_ptr<DataSet> query, StoreCallback store_callback) const
{
    this->move(query, store_callback, MoveCallback());
}

void
MoveSCU
::move(std::shared_ptr<DataSet> query, MoveCallback move_callback) const
{
    this->move(query, StoreCallback(), move_callback);
}

void
MoveSCU
::move(
    std::shared_ptr<DataSet> query, StoreCallback store_callback,
    MoveCallback move_callback) const
{
    // Send the request
    auto request = std::make_shared<message::CMoveRequest const>(
        this->_association.next_message_id(),
        this->_affected_sop_class, message::Message::Priority::MEDIUM,
        this->_move_destination, query);
    this->_move(request, store_callback, move_callback);
}

void
MoveSCU
::_move(
    std::shared_ptr<message::CMoveRequest const> request,
    StoreCallback store_callback, MoveCallback move_callback) const
{
    this->_association.send_message(request, this->_affected_sop_class);

    // Receive the responses
    Association store_association;
    bool done = false;
    if(this->_incoming_port != 0)
    {
        while(!done)
        {
            // Use a small timeout to avoid blocking for a long time.
            boost::posix_time::milliseconds const timeout(10);
            store_association.set_tcp_timeout(timeout);
            store_association.set_message_timeout(timeout);

            if(!store_association.is_associated())
            {
                try
                {
                    store_association.receive_association(
                        boost::asio::ip::tcp::v4(), this->_incoming_port);
                    store_association.set_tcp_timeout(
                        this->_association.get_tcp_timeout());
                    store_association.set_message_timeout(
                        this->_association.get_message_timeout());
                }
                catch(Exception const & e)
                {
                    // Ignore
                }

                if(store_association.is_associated())
                {
                    done = true;
                }
            }
        }
    }

    this->_dispatch(store_association, store_callback, move_callback);
}

std::vector<std::shared_ptr<DataSet>>
MoveSCU
::move(std::shared_ptr<DataSet> query) const
{
    std::vector<std::shared_ptr<DataSet>> result;
    auto callback = [&result](std::shared_ptr<DataSet> data_set) {
        result.push_back(data_set);
    };
    this->move(query, callback, MoveCallback());

    return result;
}

void
MoveSCU
::_dispatch(
    Association & store_association, StoreCallback store_callback,
    MoveCallback move_callback) const
{
    // If no store association has been established, store is considered done
    bool store_done = !store_association.is_associated();
    bool main_done = false;
    while(!(store_done && main_done))
    {
        if(!store_done && store_association.get_transport().get_socket()->available() > 0)
        {
            store_done = this->_handle_store_association(
                store_association, store_callback);
        }
        if(!main_done && this->_association.get_transport().get_socket()->available() > 0)
        {
            main_done = this->_handle_main_association(move_callback);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

bool
MoveSCU
::_handle_main_association(MoveCallback callback) const
{
    auto response = std::make_shared<message::CMoveResponse>(
        this->_association.receive_message());
    if(message::Response::is_warning(response->get_status()))
    {
        ODIL_LOG(WARN) << "C-MOVE response status: " << response->get_status();
    }
    else if(message::Response::is_failure(response->get_status()))
    {
        ODIL_LOG(ERROR) << "C-MOVE response status: " << response->get_status();
    }

    // Store status before moving the response.
    auto const done = !response->is_pending();

    if(callback)
    {
        callback(response);
    }
    return done;
}

bool
MoveSCU
::_handle_store_association(
    Association & association, StoreCallback callback) const
{
    bool result = false;
    try
    {
        auto const store_callback = [&callback](std::shared_ptr<message::CStoreRequest> request) {
            if(callback)
            {
                callback(request->get_data_set());
            }
            return message::Response::Success;
        };
        StoreSCP scp(association, store_callback);
        scp.receive_and_process();
    }
    catch(AssociationReleased const &)
    {
        result = true;
    }
    catch(AssociationAborted const & e)
    {
        result = true;
    }

    return result;
}

}
