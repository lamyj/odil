/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#ifndef _7b9819f1_d7a2_4898_a850_3ed6a61f08c6
#define _7b9819f1_d7a2_4898_a850_3ed6a61f08c6

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Response.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

/// @brief C-GET-RSP message.
class CGetResponse: public Response
{
public:
    /**
     * @brief Create an get response with given Message ID, and status.
     */
    CGetResponse(
        Value::Integer message_id_being_responded_to, Value::Integer status);

    /**
     * @brief Create an get response with given Message ID, status,
     * and data set.
     */
    CGetResponse(
        Value::Integer message_id_being_responded_to, Value::Integer status,
        DataSet const & dataset);

    /**
     * @brief Create a C-GET-RSP from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-GET-RSP.
     */
    CGetResponse(Message const & message);

    /// @brief Destructor.
    virtual ~CGetResponse();
    
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(message_id, registry::MessageID)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(
        affected_sop_class_uid, registry::AffectedSOPClassUID)

    DCMTKPP_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(
        number_of_remaining_sub_operations, registry::NumberOfRemainingSuboperations)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(
        number_of_completed_sub_operations, registry::NumberOfCompletedSuboperations)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(
        number_of_failed_sub_operations, registry::NumberOfFailedSuboperations)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(
        number_of_warning_sub_operations, registry::NumberOfWarningSuboperations)
};

}

#endif // _7b9819f1_d7a2_4898_a850_3ed6a61f08c6
