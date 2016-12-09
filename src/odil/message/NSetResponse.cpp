/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "NSetResponse.h"

#include "odil/Exception.h"
#include "odil/registry.h"
#include "odil/message/Response.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

NSetResponse
::NSetResponse(const Value::Integer &message_id_being_responded_to
               , const Value::Integer & status
        , Value::String const & requested_sop_class_uid
        , Value::String const & requested_sop_instance_uid)
: Response(message_id_being_responded_to, status)
{
    this->set_command_field(Command::N_SET_RSP);
    this->set_requested_sop_class_uid(requested_sop_class_uid);
    this->set_requested_sop_instance_uid(requested_sop_instance_uid );

}

NSetResponse
::NSetResponse(Message const & message)
: Response(message )
{
    if(message.get_command_field() != Command::N_SET_RSP)
    {
        throw Exception("Message is not a N-SET-RSP");
    }

    this->set_command_field(message.get_command_field());

    this->set_requested_sop_class_uid(
        message.get_command_set().as_string(registry::RequestedSOPClassUID, 0));

    this->set_requested_sop_instance_uid(
                message.get_command_set().as_string(registry::RequestedSOPInstanceUID, 0));
}

NSetResponse
::~NSetResponse()
{
    // Nothing to do.
}

}

}
