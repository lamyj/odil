/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "NCreateResponse.h"

#include "odil/Exception.h"
#include "odil/registry.h"
#include "odil/message/Response.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

NCreateResponse
::NCreateResponse(const Value::Integer &message_id_being_responded_to, const Value::Integer &status,
    Value::String const & affected_sop_class_uid)
: Response(message_id_being_responded_to, status)
{
    this->set_command_field(Command::N_CREATE_RSP);
    this->set_affected_sop_class_uid(affected_sop_class_uid);
}

NCreateResponse
::NCreateResponse(Message const & message)
: Response(message)
{
    if(message.get_command_field() != Command::N_CREATE_RSP)
    {
        throw Exception("Message is not a N-CREATE-RSP");
    }
    this->set_command_field(message.get_command_field());
    
    this->set_affected_sop_class_uid(
        message.get_command_set().as_string(registry::AffectedSOPClassUID, 0));
}

NCreateResponse
::~NCreateResponse()
{
    // Nothing to do.
}

}

}
