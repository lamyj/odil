/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/MoveSCU.h"

#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CMoveRequest.h"
#include "dcmtkpp/CMoveResponse.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Message.h"
#include "dcmtkpp/StoreSCP.h"

namespace dcmtkpp
{

MoveSCU
::MoveSCU()
: SCU(), _move_destination("")
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
    CMoveRequest const request(this->_association->get_association()->nextMsgID++,
        this->_affected_sop_class, Message::Priority::MEDIUM,
        this->_move_destination, query);
    this->_send(request, this->_affected_sop_class);

    // Receive the responses
    Association store_association;
    bool done = false;
    while(!done)
    {
        // Use a small timeout to avoid blocking for a long time.
        if(!store_association.is_associated() &&
           this->_network->is_association_waiting(1))
        {
            store_association.receive(*this->_network, true);
        }

        done = this->_dispatch(store_association, callback);
    }
}

std::vector<DataSet>
MoveSCU
::move(DataSet const & query) const
{
    std::vector<DataSet> result;
    auto callback = [&result](DataSet const & dataset) {
        result.push_back(dataset);
    };
    this->move(query, callback);

    return result;
}

bool
MoveSCU
::_dispatch(Association & association, Callback callback) const
{
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

    return move_finished;
}

bool
MoveSCU
::_handle_main_association() const
{
    Message const message = this->_receive();

    if(message.get_command_field() != Message::Command::C_MOVE_RSP)
    {
        std::ostringstream exception_message;
        exception_message << "DIMSE: Unexpected Response Command Field: 0x"
                << std::hex << message.get_command_field();
        throw Exception(exception_message.str());
    }

    CMoveResponse const response(message);
    return !response.is_pending();
}

bool
MoveSCU
::_handle_store_association(Association & association, Callback callback) const
{
    StoreSCP scp;
    scp.set_network(this->_network);
    scp.set_association(&association);
    return scp.store(callback);
}

}
