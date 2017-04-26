/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "NCreateRequest.h"

#include "odil/message/Request.h"
#include "odil/registry.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

NCreateRequest
::NCreateRequest(Value::Integer message_id, const Value::String &affected_sop_class_uid, DataSet const & dataset)
: Request(message_id)
{
    this->set_command_field(Command::N_CREATE_RQ);
    this->set_affected_sop_class_uid( affected_sop_class_uid ) ;

    if(dataset.empty() )
    {
        throw Exception("Data set is required");
    }
    this->set_data_set(dataset);
}

NCreateRequest
::NCreateRequest(Message const & message)
: Request(message)
{
    if(message.get_command_field() != Command::N_CREATE_RQ)
    {
        throw Exception("Message is not a N-CREATE-RQ");
    }
    this->set_command_field(message.get_command_field());

    this->set_affected_sop_class_uid(
        message.get_command_set().as_string( registry::AffectedSOPClassUID, 0));

    ODIL_MESSAGE_SET_OPTIONAL_FIELD_MACRO( message.get_command_set(), affected_sop_instance_uid,
                                           registry::AffectedSOPInstanceUID, as_string)

    if(!message.has_data_set() || message.get_data_set().empty() )
    {
        throw Exception("Data set is required");
    }
    this->set_data_set(message.get_data_set());
}

NCreateRequest
::~NCreateRequest()
{
    // Nothing to do.
}

}

}
