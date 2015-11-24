/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/GetSCU.h"

#include <functional>
#include <sstream>
#include <vector>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/message/CGetRequest.h"
#include "dcmtkpp/message/CGetResponse.h"
#include "dcmtkpp/message/CStoreRequest.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Network.h"
#include "dcmtkpp/StoreSCP.h"

namespace dcmtkpp
{

GetSCU
::GetSCU()
: SCU()
{
    // Nothing else
}

GetSCU
::GetSCU(Network * network, Association * association)
: SCU(network, association)
{
    // Nothing else
}

GetSCU
::~GetSCU()
{
    // Nothing to do
}

void
GetSCU
::get(DataSet const & query, Callback callback) const
{
    // Send the request
    message::CGetRequest request(
        this->_association->get_association()->nextMsgID++,
        this->_affected_sop_class, message::Message::Priority::MEDIUM, query);
    this->_send(request, this->_affected_sop_class);

    // Receive the responses
    bool done = false;
    while(!done)
    {
        message::Message const message = this->_receive();

        if(message.get_command_field() == message::Message::Command::C_GET_RSP)
        {
            done = this->_get_response(message::CGetResponse(message));
        }
        else if(message.get_command_field() == message::Message::Command::C_STORE_RQ)
        {
            try
            {
                this->_store_request(message::CStoreRequest(message), callback);
            }
            catch(...)
            {
                // FIXME: logging
                done = true;
            }
        }
        else
        {
            std::ostringstream exception_message;
            exception_message << "DIMSE: Unexpected Response Command Field: 0x"
                              << std::hex << message.get_command_field();
            throw Exception(exception_message.str());
        }
    }
}

std::vector<DataSet>
GetSCU
::get(DataSet const & query) const
{
    std::vector<DataSet> result;
    auto callback = [&result](DataSet const & data_set) {
        result.push_back(data_set);
    };
    this->get(query, callback);

    return result;
}

bool
GetSCU
::_get_response(message::CGetResponse const & response) const
{
    return !response.is_pending();
}

void
GetSCU
::_store_request(message::CStoreRequest const & request, Callback callback) const
{
    auto const store_callback = [&callback](message::CStoreRequest const & request) {
        callback(request.get_data_set());
        return message::Response::Success;
    };
    StoreSCP scp(this->_network, this->_association, store_callback);
    scp(request);
}

}
