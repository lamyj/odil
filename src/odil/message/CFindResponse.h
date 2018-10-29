/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _5fd36547_9498_4cf3_87cc_737af51e93a9
#define _5fd36547_9498_4cf3_87cc_737af51e93a9

#include "odil/DataSet.h"
#include "odil/odil.h"
#include "odil/registry.h"
#include "odil/message/Response.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief C-FIND-RSP message.
class ODIL_API CFindResponse: public Response
{
public:
    /// @brief C-FIND status codes, PS 3.4, C.4.1.1.4
    enum Status
    {
        // Failure
        RefusedOutOfResources=0xA700,
        IdentifierDoesNotMatchSOPClass=0xA900,
        UnableToProcess=0xC000,
        // Pending
        PendingWarningOptionalKeysNotSupported=0xFF01,
    };

    /**
     * @brief Create an find response with given Message ID, and status.
     */
    CFindResponse(
        Value::Integer message_id_being_responded_to, Value::Integer status);

    /**
     * @brief Create an find response with given Message ID, status,
     * and data set.
     */
    CFindResponse(
        Value::Integer message_id_being_responded_to, Value::Integer status,
        std::shared_ptr<DataSet> dataset);

    /**
     * @brief Create a C-FIND-RSP from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-FIND-RSP.
     */
    CFindResponse(std::shared_ptr<Message> message);

    ODIL_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(message_id, registry::MessageID)
    ODIL_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(
        affected_sop_class_uid, registry::AffectedSOPClassUID)

private:
    void _parse(std::shared_ptr<Message const> message);
};

}

}

#endif // _5fd36547_9498_4cf3_87cc_737af51e93a9
