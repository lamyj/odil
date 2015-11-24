/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "CEchoResponse.h"

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/message/Response.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

namespace message
{

CEchoResponse
::CEchoResponse(
    Value::Integer message_id_being_responded_to, Value::Integer status,
    Value::String const & affected_sop_class_uid)
: Response(message_id_being_responded_to, status)
{
    this->set_command_field(Command::C_ECHO_RSP);
    this->set_affected_sop_class_uid(affected_sop_class_uid);
}

CEchoResponse
::CEchoResponse(Message const & message)
: Response(message)
{
    if(message.get_command_field() != Command::C_ECHO_RSP)
    {
        throw Exception("Message is not a C-ECHO-RSP");
    }
    this->set_command_field(message.get_command_field());
    
    this->set_affected_sop_class_uid(
        message.get_command_set().as_string(registry::AffectedSOPClassUID, 0));
}

CEchoResponse
::~CEchoResponse()
{
    // Nothing to do.
}

}

}
