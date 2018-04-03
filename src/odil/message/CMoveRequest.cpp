/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "CMoveRequest.h"

#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/registry.h"
#include "odil/message/Request.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

CMoveRequest
::CMoveRequest(
    Value::Integer message_id, Value::String const & affected_sop_class_uid,
    Value::Integer priority, Value::String const & move_destination,
    std::shared_ptr<DataSet> dataset)
: Request(message_id)
{
    this->_create(affected_sop_class_uid, priority, move_destination, dataset);
    this->set_data_set(dataset);
}

CMoveRequest
::CMoveRequest(std::shared_ptr<Message> message)
: Request(message)
{
    this->_parse(message);
    this->set_data_set(message->get_data_set());
}

void
CMoveRequest
::_create(
    Value::String const & affected_sop_class_uid,
    Value::Integer priority, Value::String const & move_destination,
    std::shared_ptr<DataSet const> dataset)
{
    this->set_command_field(Command::C_MOVE_RQ);
    this->set_affected_sop_class_uid(affected_sop_class_uid);
    this->set_priority(priority);
    this->set_move_destination(move_destination);
    if(dataset->empty())
    {
        throw Exception("Data set is required");
    }
}

void
CMoveRequest
::_parse(std::shared_ptr<Message const> message)
{
    if(!message || message->get_command_field() != Command::C_MOVE_RQ)
    {
        throw Exception("Message is not a C-MOVE-RQ");
    }
    this->set_command_field(message->get_command_field());

    this->set_affected_sop_class_uid(
        message->get_command_set()->as_string(registry::AffectedSOPClassUID, 0));

    this->set_priority(message->get_command_set()->as_int(registry::Priority, 0));

    this->set_move_destination(
        message->get_command_set()->as_string(registry::MoveDestination, 0));

    if(!message->has_data_set()  || message->get_data_set()->empty())
    {
        throw Exception("Data set is required");
    }
}

}

}
