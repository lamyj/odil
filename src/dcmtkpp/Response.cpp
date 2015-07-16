/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Response.h"

#include "dcmtkpp/Message.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

Response
::Response(Value::Integer message_id_being_responded_to, Value::Integer status)
: Message()
{
    this->set_message_id_being_responded_to(message_id_being_responded_to);
    this->set_status(status);
}

Response
::Response(Message const & message)
: Message()
{
    this->set_message_id_being_responded_to(
        message.get_command_set().as_int(
            registry::MessageIDBeingRespondedTo, 0));

    this->set_status(message.get_command_set().as_int(registry::Status, 0));
}

Response
::~Response()
{
    // Nothing to do.
}

}
