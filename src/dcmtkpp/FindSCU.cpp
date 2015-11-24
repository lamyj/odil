/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/FindSCU.h"

#include <functional>
#include <sstream>
#include <vector>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/message/CFindRequest.h"
#include "dcmtkpp/message/CFindResponse.h"

namespace dcmtkpp
{

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
        this->_association->get_association()->nextMsgID++,
        this->_affected_sop_class, message::Message::Priority::MEDIUM, query);
    this->_send(request, this->_affected_sop_class);

    // Receive the responses
    bool done = false;
    while(!done)
    {
        // FIXME: include progress callback
        auto response = this->_receive<message::CFindResponse>();

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

        done = !response.is_pending();
        if(!done)
        {
            callback(response.get_data_set());
        }
    }
}

std::vector<DataSet>
FindSCU
::find(DataSet const & query) const
{
    std::vector<DataSet> result;
    auto callback = [&result](DataSet const & dataset) {
        result.push_back(dataset);
    };
    this->find(query, callback);

    return result;
}

}
