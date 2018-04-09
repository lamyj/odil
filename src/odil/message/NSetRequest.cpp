/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "NSetRequest.h"

#include <string>

#include "odil/Exception.h"
#include "odil/VR.h"

namespace odil
{

namespace message
{

NSetRequest
::NSetRequest(
    Value::Integer message_id,
    Value::String const & requested_sop_class_uid,
    Value::String const & requested_sop_instance_uid,
    std::shared_ptr<DataSet> dataset)
: Request(message_id)
{
    this->set_command_field( ::odil::message::Message::Command::N_SET_RQ);
    this->set_requested_sop_class_uid(requested_sop_class_uid);
    this->set_requested_sop_instance_uid(requested_sop_instance_uid);

    if(!dataset || dataset->empty())
    {
        throw Exception("Data set is required");
    }
    this->set_data_set(dataset);
}

NSetRequest
::NSetRequest(std::shared_ptr<Message> message)
: Request(message)
{
    if(!message || message->get_command_field() != Command::N_SET_RQ)
    {
        throw Exception("Message is not a N-SET-RQ");
    }

    this->set_command_field(message->get_command_field());

    this->set_requested_sop_class_uid(
        message->get_command_set()->as_string(registry::RequestedSOPClassUID, 0));
    this->set_requested_sop_instance_uid(
        message->get_command_set()->as_string(registry::RequestedSOPInstanceUID, 0));

    if(!message->has_data_set() || message->get_data_set()->empty())
    {
        throw Exception("Data set is required");
    }
    this->set_data_set(message->get_data_set());
}

}

}
