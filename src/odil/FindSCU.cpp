/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/FindSCU.h"

#include <functional>
#include <sstream>
#include <utility>
#include <vector>

#include "odil/Association.h"
#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/logging.h"
#include "odil/message/CFindRequest.h"
#include "odil/message/CFindResponse.h"

namespace odil
{

FindSCU
::FindSCU(Association & asociation)
: SCU(asociation)
{
    // Nothing else.
}

FindSCU
::~FindSCU()
{
    // Nothing to do
}

void
FindSCU
::find(DataSet const & query, Callback callback) const
{
    message::CFindRequest request(
        this->_association.next_message_id(),
        this->_affected_sop_class, message::Message::Priority::MEDIUM, query);
    this->_find(request, callback);
}

void
FindSCU
::find(DataSet && query, Callback callback) const
{
    message::CFindRequest request(
        this->_association.next_message_id(),
        this->_affected_sop_class, message::Message::Priority::MEDIUM,
        std::move(query));
    this->_find(request, callback);
}

void _accumulate(std::vector<DataSet> & data_sets, DataSet && data_set)
{
    data_sets.push_back(std::move(data_set));
}

std::vector<DataSet>
FindSCU
::find(DataSet const & query) const
{
    std::vector<DataSet> result;
    auto callback = [&result](DataSet && dataset) {
        result.push_back(std::move(dataset));
    };
    this->find(query, callback);

    return result;
}

std::vector<DataSet>
FindSCU
::find(DataSet && query) const
{
    std::vector<DataSet> result;
    auto callback = [&result](DataSet && dataset) {
        result.push_back(std::move(dataset));
    };
    this->find(std::move(query), callback);

    return result;
}

void
FindSCU
::_find(message::CFindRequest & request, Callback callback) const
{
    this->_association.send_message(request, this->_affected_sop_class);

    // Receive the responses
    bool done = false;
    while(!done)
    {
        // FIXME: include progress callback
        message::CFindResponse response =
            this->_association.receive_message();

        if(response.get_message_id_being_responded_to() != request.get_message_id())
        {
            std::ostringstream message;
            message << "DIMSE: Unexpected Response MsgId: "
                    << response.get_message_id_being_responded_to()
                    << "(expected: " << request.get_message_id() << ")";
            throw Exception(message.str());
        }
        if(response.has_affected_sop_class_uid() &&
           response.get_affected_sop_class_uid() != request.get_affected_sop_class_uid())
        {
            std::ostringstream message;
            message << "DIMSE: Unexpected Response Affected SOP Class UID: "
                    << response.get_affected_sop_class_uid()
                    << " (expected: " << request.get_affected_sop_class_uid() << ")";
            throw Exception(message.str());
        }

        if(message::Response::is_warning(response.get_status()))
        {
            ODIL_LOG(WARN) << "C-FIND response status: " << response.get_status();
        }
        else if(message::Response::is_failure(response.get_status()))
        {
            ODIL_LOG(ERROR) << "C-FIND response status: " << response.get_status();
        }

        done = !response.is_pending();
        if(!done)
        {
            callback(std::move(response.get_data_set()));
        }
    }
}

}
