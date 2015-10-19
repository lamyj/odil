/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/StoreSCP.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CStoreRequest.h"
#include "dcmtkpp/CStoreResponse.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

bool
StoreSCP
::store(Callback callback) const
{
    Message request;
    try
    {
        request = this->_receive();
    }
    catch(Exception const & e)
    {
        if(e.get_source() != Exception::Source::Condition ||
           e.get_condition() != DUL_PEERREQUESTEDRELEASE)
        {
            throw;
        }
        else
        {
            return true;
        }
    }

    if(request.get_command_field() == Message::Command::C_ECHO_RQ)
    {
        this->_send_echo_response(CEchoRequest(request));
    }
    else if(request.get_command_field() == Message::Command::C_STORE_RQ)
    {
        this->store(CStoreRequest(request), callback);
        request.delete_data_set();
    }
    else
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response Command Field: 0x"
                << std::hex << request.get_command_field();
        throw Exception(message.str());
    }

    return false;
}

void
StoreSCP
::store(CStoreRequest const & request, Callback callback) const
{
    // Execute user callback
    Value::Integer status = CStoreResponse::Success;
    if(!request.has_data_set() || request.get_data_set().empty())
    {
        status = CStoreResponse::ErrorCannotUnderstand;
    }
    else
    {
        try
        {
            callback(request.get_data_set());
        }
        catch(...)
        {
            // FIXME: logging
            status = CStoreResponse::ErrorCannotUnderstand;
        }
    }

    // Send store response
    CStoreResponse response(request.get_message_id(), status);
    response.set_affected_sop_class_uid(request.get_affected_sop_class_uid());
    response.set_affected_sop_instance_uid(
        request.get_affected_sop_instance_uid());
    this->_send(response, request.get_affected_sop_class_uid());
}

}
