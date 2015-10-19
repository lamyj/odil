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

#include "dcmtkpp/CGetRequest.h"
#include "dcmtkpp/CGetResponse.h"
#include "dcmtkpp/CStoreRequest.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

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
    CGetRequest request(this->_association->get_association()->nextMsgID++,
        this->_affected_sop_class, Message::Priority::MEDIUM, query);
    this->_send(request, this->_affected_sop_class);

    // Receive the responses
    bool done = false;
    while(!done)
    {
        Message const message = this->_receive();

        if(message.get_command_field() == Message::Command::C_GET_RSP)
        {
            done = this->_get_response(CGetResponse(message));
        }
        else if(message.get_command_field() == Message::Command::C_STORE_RQ)
        {
            try
            {
                this->_store_request(CStoreRequest(message), callback);
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
    auto callback = [&result](DataSet const & dataset) {
        result.push_back(dataset);
    };
    this->get(query, callback);

    return result;
}

bool
GetSCU
::_get_response(CGetResponse const & response) const
{
    return !response.is_pending();
}

void
GetSCU
::_store_request(CStoreRequest const & request, Callback callback) const
{
    StoreSCP scp;
    scp.set_network(this->get_network());
    scp.set_association(this->get_association());
    scp.store(request, callback);
}

}
