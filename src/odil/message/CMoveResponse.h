/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b245f6f2_50c3_4c7c_80e1_f03d9c831301
#define _b245f6f2_50c3_4c7c_80e1_f03d9c831301

#include "odil/DataSet.h"
#include "odil/odil.h"
#include "odil/registry.h"
#include "odil/message/Response.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief C-MOVE-RSP message.
class ODIL_API CMoveResponse: public Response
{
public:
    /// @brief C-MOVE status codes, PS 3.4, C.4.2.1.5
    enum Status
    {
        // Failure
        RefusedOutOfResourcesUnableToCalculateNumberOfMatches=0xA701,
        RefusedOutOfResourcesUnableToPerformSubOperations=0xA702,
        RefusedMoveDestinationUnknown=0xA801,
        IdentifierDoesNotMatchSOPClass=0xA900,
        UnableToProcess=0xC000,
        // Warning
        SubOperationsCompleteOneOrMoreFailuresOrWarnings=0xB000
    };

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
        std::shared_ptr<DataSet> dataset);

    /**
     * @brief Create a C-MOVE-RSP from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-MOVE-RSP.
     */
    CMoveResponse(std::shared_ptr<Message> message);

    ODIL_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(message_id, registry::MessageID)
    ODIL_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(
        affected_sop_class_uid, registry::AffectedSOPClassUID)

    ODIL_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(
        number_of_remaining_sub_operations, registry::NumberOfRemainingSuboperations)
    ODIL_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(
        number_of_completed_sub_operations, registry::NumberOfCompletedSuboperations)
    ODIL_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(
        number_of_failed_sub_operations, registry::NumberOfFailedSuboperations)
    ODIL_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(
        number_of_warning_sub_operations, registry::NumberOfWarningSuboperations)

private:
    void _parse(std::shared_ptr<Message const> message);
};

}

}

#endif // _b245f6f2_50c3_4c7c_80e1_f03d9c831301
