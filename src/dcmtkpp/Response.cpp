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

bool
Response
::is_pending() const
{
    return (this->get_status()==Pending || this->get_status()==0xFF01);
}

bool
Response
::is_warning() const
{
    return (
        this->get_status()==0x0001 || (this->get_status()>>12)==0xB ||
        this->get_status() == AttributeListError ||
        this->get_status() == AttributeValueOutOfRange);
}

bool
Response
::is_failure() const
{
    return (
        (this->get_status()>>12)==0xA || (this->get_status()>>12)==0xC || (
            (this->get_status()>>8) == 0x01 && this->get_status() != AttributeListError &&
            this->get_status() != AttributeValueOutOfRange) ||
        (this->get_status()>>8) == 0x02
    );
}

}
