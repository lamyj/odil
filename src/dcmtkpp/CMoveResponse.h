/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#ifndef _b245f6f2_50c3_4c7c_80e1_f03d9c831301
#define _b245f6f2_50c3_4c7c_80e1_f03d9c831301

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Response.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

/// @brief C-MOVE-RSP message.
class CMoveResponse: public Response
{
public:
    /**
     * @brief Create an move response with given Message ID, and status.
     */
    CMoveResponse(
        Value::Integer message_id_being_responded_to, Value::Integer status);

    /**
     * @brief Create an move response with given Message ID, status,
     * and data set.
     */
    CMoveResponse(
        Value::Integer message_id_being_responded_to, Value::Integer status,
        DataSet const & dataset);

    /**
     * @brief Create a C-MOVE-RSP from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-MOVE-RSP.
     */
    CMoveResponse(Message const & message);

    /// @brief Destructor.
    virtual ~CMoveResponse();
    
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

#endif // _b245f6f2_50c3_4c7c_80e1_f03d9c831301
