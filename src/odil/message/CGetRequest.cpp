/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "CGetRequest.h"

#include <string>

#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/registry.h"
#include "odil/message/Request.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

CGetRequest
::CGetRequest(
    Value::Integer message_id, Value::String const & affected_sop_class_uid,
    Value::Integer priority, std::shared_ptr<DataSet> dataset)
: Request(message_id)
{
    this->_create(affected_sop_class_uid, priority, dataset);
    this->set_data_set(dataset);
}

CGetRequest
::CGetRequest(std::shared_ptr<Message> message)
: Request(message)
{
    this->_parse(message);
    this->set_data_set(message->get_data_set());
}

void
CGetRequest
::_create(
    Value::String const & affected_sop_class_uid, Value::Integer priority,
    std::shared_ptr<DataSet const> dataset)
{
    this->set_command_field(Command::C_GET_RQ);
    this->set_affected_sop_class_uid(affected_sop_class_uid);
    this->set_priority(priority);
    if(!dataset || dataset->empty())
    {
        throw Exception("Data set is required");
    }
}

void
CGetRequest
::_parse(std::shared_ptr<Message const> message)
{
    if(!message || message->get_command_field() != Command::C_GET_RQ)
    {
        throw Exception("Message is not a C-GET-RQ");
    }
    this->set_command_field(message->get_command_field());

    this->set_affected_sop_class_uid(
        message->get_command_set()->as_string(registry::AffectedSOPClassUID, 0));

    this->set_priority(message->get_command_set()->as_int(registry::Priority, 0));

    if(!message->has_data_set() || message->get_data_set()->empty())
    {
        throw Exception("Data set is required");
    }
}

}

}
