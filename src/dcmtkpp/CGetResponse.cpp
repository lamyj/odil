/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "CGetResponse.h"

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Response.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

CGetResponse
::CGetResponse(
    Value::Integer message_id_being_responded_to, Value::Integer status)
: Response(message_id_being_responded_to, status)
{
    this->set_command_field(Command::C_GET_RSP);
}

CGetResponse
::CGetResponse(
    Value::Integer message_id_being_responded_to, Value::Integer status,
    DataSet const & dataset)
: Response(message_id_being_responded_to, status)
{
    this->set_command_field(Command::C_GET_RSP);
    this->set_data_set(dataset);
}

CGetResponse
::CGetResponse(Message const & message)
: Response(message)
{
    if(message.get_command_field() != Command::C_GET_RSP)
    {
        throw Exception("Message is not a C-GET-RSP");
    }
    this->set_command_field(message.get_command_field());
    
    DCMTKPP_MESSAGE_SET_OPTIONAL_FIELD_MACRO(
        message.get_command_set(), message_id, registry::MessageID, as_int)
    DCMTKPP_MESSAGE_SET_OPTIONAL_FIELD_MACRO(
        message.get_command_set(), affected_sop_class_uid,
        registry::AffectedSOPClassUID, as_string)

    DCMTKPP_MESSAGE_SET_OPTIONAL_FIELD_MACRO(
        message.get_command_set(), number_of_remaining_sub_operations,
        registry::NumberOfRemainingSuboperations, as_int)
    DCMTKPP_MESSAGE_SET_OPTIONAL_FIELD_MACRO(
        message.get_command_set(), number_of_completed_sub_operations,
        registry::NumberOfCompletedSuboperations, as_int)
    DCMTKPP_MESSAGE_SET_OPTIONAL_FIELD_MACRO(
        message.get_command_set(), number_of_failed_sub_operations,
        registry::NumberOfFailedSuboperations, as_int)
    DCMTKPP_MESSAGE_SET_OPTIONAL_FIELD_MACRO(
        message.get_command_set(), number_of_warning_sub_operations,
        registry::NumberOfWarningSuboperations, as_int)

    if(message.has_data_set())
    {
        this->set_data_set(message.get_data_set());
    }
}

CGetResponse
::~CGetResponse()
{
    // Nothing to do.
}

}
