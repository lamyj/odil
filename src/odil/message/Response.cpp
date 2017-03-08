/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Response.h"

#include "odil/message/Message.h"
#include "odil/registry.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

bool
Response
::is_pending(Value::Integer status)
{
    return (status == Response::Pending || status == 0xFF01);
}

bool
Response
::is_warning(Value::Integer status)
{
    return (
        status == 0x0001 || (status>>12) == 0xB ||
        status == Response::AttributeListError ||
        status == Response::AttributeValueOutOfRange);
}

bool
Response
::is_failure(Value::Integer status)
{
    return (
        (status>>12) == 0xA || (status>>12) == 0xC ||
        ((status>>8) == 0x01 && !is_warning(status)) ||
        (status>>8) == 0x02
    );
}

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
    return Response::is_pending(this->get_status());
}

bool
Response
::is_warning() const
{
    return Response::is_warning(this->get_status());
}

bool
Response
::is_failure() const
{
    return Response::is_failure(this->get_status());
}

void
Response
::set_status_fields(DataSet const & status_fields)
{
    for(auto const & tag_and_element: status_fields)
    {
        if(this->_command_set.has(tag_and_element.first))
        {
            this->_command_set[tag_and_element.first] = tag_and_element.second;
        }
        else
        {
            this->_command_set.add(tag_and_element.first, tag_and_element.second);
        }
    }
}

}

}
