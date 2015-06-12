/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Request.h"

#include "dcmtkpp/Message.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

Request
::Request(Value::Integer message_id)
: Message()
{
    this->set_message_id(message_id);
}

Request
::Request(Message const & message)
: Message()
{
    this->set_message_id(message.get_command_set().as_int(registry::MessageID, 0));
}

Request
::~Request()
{
    // Nothing to do.
}

}
