/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/GetSCU.h"

#include <functional>
#include <sstream>
#include <vector>

#include "odil/Association.h"
#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/logging.h"
#include "odil/StoreSCP.h"
#include "odil/message/CGetRequest.h"
#include "odil/message/CGetResponse.h"
#include "odil/message/CStoreRequest.h"

namespace odil
{

GetSCU
::GetSCU(Association & association)
: SCU(association)
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
::get(
    DataSet const & query, StoreCallback store_callback,
    GetCallback get_callback) const
{
    // Send the request
    message::CGetRequest request(
        this->_association.next_message_id(),
        this->_affected_sop_class, message::Message::Priority::MEDIUM, query);
    this->_association.send_message(request, this->_affected_sop_class);

    // Receive the responses
    bool done = false;
    while(!done)
    {
        message::Message const message = this->_association.receive_message();

        if(message.get_command_field() == message::Message::Command::C_GET_RSP)
        {
            done = this->_handle_get_response(
                message::CGetResponse(message), get_callback);
        }
        else if(message.get_command_field() == message::Message::Command::C_STORE_RQ)
        {
            try
            {
                this->_handle_store_request(
                    message::CStoreRequest(message), store_callback);
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
::_handle_get_response(
    message::CGetResponse const & response, GetCallback callback) const
{
    if(message::Response::is_warning(response.get_status()))
    {
        ODIL_LOG(WARN) << "C-GET response status: " << response.get_status();
    }
    else if(message::Response::is_failure(response.get_status()))
    {
        ODIL_LOG(ERROR) << "C-GET response status: " << response.get_status();
    }

    if(callback)
    {
        callback(response);
    }
    return !response.is_pending();
}

void
GetSCU
::_handle_store_request(
    message::CStoreRequest const & request, StoreCallback callback) const
{
    auto const store_callback = [&callback](message::CStoreRequest const & request) {
        if(callback)
        {
            callback(request.get_data_set());
        }
        return message::Response::Success;
    };
    StoreSCP scp(this->_association, store_callback);
    scp(request);
}

}
