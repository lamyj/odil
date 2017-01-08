/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _0dd2e31e_212a_494a_a8d3_93b235336658
#define _0dd2e31e_212a_494a_a8d3_93b235336658

#include "odil/message/Message.h"
#include "odil/odil.h"
#include "odil/registry.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief Base class for all DIMSE response messages.
class ODIL_API Response: public Message
{
public:
    /// @brief General status codes, from PS3.7, C
    enum Status
    {
        Success=0x0000,
        // Warning: 0001 or Bxxx
        // Failure: Axxx or Cxxx
        Cancel=0xFE00,
        Pending=0xFF00,

        // Warning Status Classes, PS3.7, C.3
        AttributeListError=0x0107,
        AttributeValueOutOfRange=0x0116,

        // Failure Status Classes, PS3.7, C.4
        SOPClassNotSupported=0x0122,
        ClassInstanceConflict=0x0119,
        DuplicateSOPInstance=0x0111,
        DuplicateInvocation=0x0210,
        InvalidArgumentValue=0x0115,
        InvalidAttributeValue=0x0106,
        InvalidObjectInstance=0x0117,
        MissingAttribute=0x0120,
        MissingAttributeValue=0x0121,
        MistypedArgument=0x0212,
        NoSuchArgument=0x0114,
        NoSuchAttribute=0x0105,
        NoSuchEventType=0x0113,
        NoSuchSOPInstance=0x0112,
        NoSuchSOPClass=0x0118,
        ProcessingFailure=0x0110,
        ResourceLimitation=0x0213,
        UnrecognizedOperation=0x0211,
        NoSuchActionType=0x0123,
        RefusedNotAuthorized=0x0124,
    };

    /// @brief Test whether the status class is pending.
    static bool is_pending(Value::Integer status);

    /// @brief Test whether the status class is warning.
    static bool is_warning(Value::Integer status);

    /// @brief Test whether the status class is failure.
    static bool is_failure(Value::Integer status);

    /// @brief Create a response with given message id and status;
    Response(Value::Integer message_id_being_responded_to, Value::Integer status);

    /**
     * @brief Create a response from the Message ID Being Responded To and the
     * Status stored in the message command set.
     *
     * Raise an exception is either of those elements is missing.
     */
    Response(Message const & message);

    /// @brief Destructor.
    virtual ~Response();

    ODIL_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(
        message_id_being_responded_to, registry::MessageIDBeingRespondedTo)
    ODIL_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(status, registry::Status)

    ODIL_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(
        offending_element, registry::OffendingElement)
    ODIL_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(
        error_comment, registry::ErrorComment)
    ODIL_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(
        error_id, registry::ErrorID)
    ODIL_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(
        affected_sop_instance_uid, odil::registry::AffectedSOPInstanceUID)
    ODIL_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(
        attribute_identifier_list, odil::registry::AttributeIdentifierList)

    /// @brief Test whether the status class is pending.
    bool is_pending() const;

    /// @brief Test whether the status class is warning.
    bool is_warning() const;

    /// @brief Test whether the status class is failure.
    bool is_failure() const;

    /// @brief Set the status fields (cf. PS.37, C)
    void set_status_fields(DataSet const & status_fields);
};

}

}

#endif // _0dd2e31e_212a_494a_a8d3_93b235336658
