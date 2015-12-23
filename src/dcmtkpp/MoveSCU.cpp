/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/MoveSCU.h"

#include <functional>
#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/StoreSCP.h"
#include "dcmtkpp/message/CMoveRequest.h"
#include "dcmtkpp/message/CMoveResponse.h"
#include "dcmtkpp/message/Message.h"

namespace dcmtkpp
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
        /*
        if(!store_association.is_associated() &&
           this->_network->is_association_waiting(1))
        {
            store_association.receive(*this->_network, true);
        }
        */

        done = this->_dispatch(store_association, callback);
    }
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

bool
MoveSCU
::_dispatch(Association & association, Callback callback) const
{
    /*
    T_ASC_Association *associations[2];
    int size = 0;

    associations[0] = this->_association->get_association();
    size = 1;
    associations[1] = association.get_association();
    if(association.is_associated())
    {
        ++size;
    }

    // At this point, we should have a readable association.
    if(!ASC_selectReadableAssociation(associations, size, 1))
    {
        throw Exception("No readable association");
    }

    bool move_finished;

    if(associations[0] != NULL)
    {
        move_finished = this->_handle_main_association();
    }
    else if(associations[1] != NULL)
    {
        bool const release =
            this->_handle_store_association(association, callback);
        if(release)
        {
            association.drop();
        }
    }
    else
    {
        throw Exception("No association available");
    }

    return move_finished;
    */
    return true;
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
    catch(Exception const &)
    {
        result = true;
    }

    return result;
}

}
