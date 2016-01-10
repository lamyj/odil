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
#include "odil/StoreSCP.h"
#include "odil/message/CMoveRequest.h"
#include "odil/message/CMoveResponse.h"
#include "odil/message/Message.h"

namespace odil
{

MoveSCU
::MoveSCU(Association & association)
: SCU(association), _move_destination("")
{
    // Nothing else.
}

MoveSCU
::~MoveSCU()
{
    // Nothing to do
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

void
MoveSCU
::move(DataSet const & query, Callback callback) const
{
    // Send the request
    message::CMoveRequest const request(
        this->_association.next_message_id(),
        this->_affected_sop_class, message::Message::Priority::MEDIUM,
        this->_move_destination, query);
    this->_association.send_message(request, this->_affected_sop_class);

    // Receive the responses
    Association store_association;
    bool done = false;
    while(!done)
    {
        // Use a small timeout to avoid blocking for a long time.
        boost::posix_time::milliseconds const timeout(1000);
        store_association.set_tcp_timeout(timeout);
        store_association.set_message_timeout(timeout);

        if(!store_association.is_associated())
        {
            try
            {
                store_association.receive_association(boost::asio::ip::tcp::v4(), 11113);
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

    this->_dispatch(store_association, callback);
}

std::vector<DataSet>
MoveSCU
::move(DataSet const & query) const
{
    std::vector<DataSet> result;
    auto callback = [&result](DataSet const & data_set) {
        result.push_back(data_set);
    };
    this->move(query, callback);

    return result;
}

void
MoveSCU
::_dispatch(Association & store_association, Callback callback) const
{
    bool store_done = false;
    bool main_done = false;
    while(!(store_done && main_done))
    {
        if(store_association.get_transport().get_socket()->available() > 0)
        {
            store_done =
                this->_handle_store_association(store_association, callback);
        }
        if(this->_association.get_transport().get_socket()->available() > 0)
        {
            main_done = this->_handle_main_association();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

bool
MoveSCU
::_handle_main_association() const
{
    message::CMoveResponse const response = this->_association.receive_message();
    return !response.is_pending();
}

bool
MoveSCU
::_handle_store_association(Association & association, Callback callback) const
{
    bool result = false;
    try
    {
        auto const store_callback = [&callback](message::CStoreRequest const & request) {
            callback(request.get_data_set());
            return message::Response::Success;
        };
        StoreSCP scp(association, store_callback);
        scp.receive_and_process();
    }
    catch(odil::AssociationReleased const &)
    {
        result = true;
    }
    catch(odil::AssociationAborted const & e)
    {
        result = true;
    }

    return result;
}

}
