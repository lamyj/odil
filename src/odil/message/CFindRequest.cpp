/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "CFindRequest.h"

#include <string>

#include "odil/Exception.h"
#include "odil/registry.h"
#include "odil/message/Request.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

CFindRequest
::CFindRequest(
    Value::Integer message_id, Value::String const & affected_sop_class_uid,
    Value::Integer priority, DataSet const & dataset)
: Request(message_id)
{
    this->_create(affected_sop_class_uid, priority, dataset);
    this->set_data_set(dataset);
}

CFindRequest
::CFindRequest(
    Value::Integer message_id, Value::String const & affected_sop_class_uid,
    Value::Integer priority, DataSet && dataset)
: Request(message_id)
{
    this->_create(affected_sop_class_uid, priority, dataset);
    this->set_data_set(std::move(dataset));
}

CFindRequest
::CFindRequest(Message const & message)
: Request(message)
{
    this->_parse(message);
    this->set_data_set(message.get_data_set());
}

CFindRequest
::CFindRequest(Message && message)
: Request(message)
{
    this->_parse(message);
    this->set_data_set(std::move(message.get_data_set()));
}

CFindRequest
::~CFindRequest()
{
    // Nothing to do.
}

void
CFindRequest
::_create(
    Value::String const & affected_sop_class_uid, Value::Integer priority,
    DataSet const & dataset)
{
    this->set_command_field(Command::C_FIND_RQ);
    this->set_affected_sop_class_uid(affected_sop_class_uid);
    this->set_priority(priority);
    if(dataset.empty())
    {
        throw Exception("Data set is required");
    }
}

void
CFindRequest
::_parse(Message const & message)
{
    if(message.get_command_field() != Command::C_FIND_RQ)
    {
        throw Exception("Message is not a C-FIND-RQ");
    }
    this->set_command_field(message.get_command_field());

    this->set_affected_sop_class_uid(
        message.get_command_set().as_string(registry::AffectedSOPClassUID, 0));

    this->set_priority(message.get_command_set().as_int(registry::Priority, 0));

    if(!message.has_data_set() || message.get_data_set().empty())
    {
        throw Exception("Data set is required");
    }
}

}

}
