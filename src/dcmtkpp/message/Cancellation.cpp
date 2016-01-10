/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/message/Cancellation.h"

#include "odil/Exception.h"
#include "odil/message/Message.h"
#include "odil/registry.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

Cancellation
::Cancellation(uint16_t message_id_being_responded_to)
: Message()
{
    this->set_command_field(Command::C_CANCEL_RQ);
    this->set_message_id_being_responded_to(message_id_being_responded_to);
}

Cancellation
::Cancellation(Message const & message)
{
    if(message.get_command_field() != Command::C_CANCEL_RQ)
    {
        throw Exception("Message is not a C-CANCEL-RQ");
    }
    this->set_command_field(message.get_command_field());

    this->set_message_id_being_responded_to(
        message.get_command_set().as_int(registry::MessageIDBeingRespondedTo, 0));
}

Cancellation
::~Cancellation()
{
    // Nothing to do.
}

}

}
