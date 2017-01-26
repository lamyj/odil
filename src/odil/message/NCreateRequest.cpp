/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "NCreateRequest.h"

#include "odil/message/Request.h"
#include "odil/registry.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

NCreateRequest
::NCreateRequest(Value::Integer message_id, const Value::String &affected_sop_class_uid)
: Request(message_id)
{
    this->set_command_field(Command::N_CREATE_RQ);
    this->set_affected_sop_class_uid( affected_sop_class_uid ) ;
}

NCreateRequest
::NCreateRequest(Message const & message)
: Request(message)
{
    if(message.get_command_field() != Command::N_CREATE_RQ)
    {
        throw Exception("Message is not a N-CREATE-RQ");
    }
    this->set_command_field(message.get_command_field());

    this->set_affected_sop_class_uid(
        message.get_command_set().as_string( registry::AffectedSOPClassUID, 0));
}

NCreateRequest
::~NCreateRequest()
{
    // Nothing to do.
}

}

}
