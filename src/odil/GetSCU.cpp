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
    this->_get(request, store_callback, get_callback);
}

void
GetSCU
::get(
    DataSet && query, StoreCallback store_callback,
    GetCallback get_callback) const
{
    // Send the request
    message::CGetRequest request(
        this->_association.next_message_id(),
        this->_affected_sop_class, message::Message::Priority::MEDIUM,
        std::move(query));
    this->_get(request, store_callback, get_callback);
}

std::vector<DataSet>
GetSCU
::get(DataSet const & query) const
{
    std::vector<DataSet> result;
    auto callback = [&result](DataSet && data_set) {
        result.push_back(data_set);
    };
    this->get(query, callback);

    return result;
}

std::vector<DataSet>
GetSCU
::get(DataSet && query) const
{
    std::vector<DataSet> result;
    auto callback = [&result](DataSet && data_set) {
        result.push_back(std::move(data_set));
    };
    this->get(std::move(query), callback);

    return result;
}

void
GetSCU
::_get(
    message::CGetRequest const & request,
    StoreCallback store_callback, GetCallback get_callback) const
{
    this->_association.send_message(request, this->_affected_sop_class);

    // Receive the responses
    bool done = false;
    while(!done)
    {
        message::Message message = this->_association.receive_message();

        if(message.get_command_field() == message::Message::Command::C_GET_RSP)
        {
            done = this->_handle_get_response(
                message::CGetResponse(std::move(message)), get_callback);
        }
        else if(message.get_command_field() == message::Message::Command::C_STORE_RQ)
        {
            try
            {
                this->_handle_store_request(
                    message::CStoreRequest(std::move(message)), store_callback);
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

bool
GetSCU
::_handle_get_response(
    message::CGetResponse && response, GetCallback callback) const
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
        callback(std::move(response));
    }
    return !response.is_pending();
}

void
GetSCU
::_handle_store_request(
    message::CStoreRequest && request, StoreCallback callback) const
{
    auto const store_callback = [&callback](message::CStoreRequest && request) {
        if(callback)
        {
            callback(std::move(request.get_data_set()));
        }
        return message::Response::Success;
    };
    StoreSCP scp(this->_association, store_callback);
    scp(std::move(request));
}

}
