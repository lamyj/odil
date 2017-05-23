/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f6e243d2_6113_4fe3_8d04_3f034fc796bf
#define _f6e243d2_6113_4fe3_8d04_3f034fc796bf

#include "odil/DataSet.h"
#include "odil/odil.h"
#include "odil/registry.h"
#include "odil/message/Request.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief C-MOVE-RQ message.
class ODIL_API CMoveRequest: public Request
{
public:
    /**
     * @brief Create an move request with given Message ID,
     * affected SOP class UID, priority, move destination, and data set.
     */
    CMoveRequest(
        Value::Integer message_id, Value::String const & affected_sop_class_uid,
        Value::Integer priority, Value::String const & move_destination,
        DataSet const & dataset);

    /**
     * @brief Create an move request with given Message ID,
     * affected SOP class UID, priority, move destination, and data set.
     */
    CMoveRequest(
        Value::Integer message_id, Value::String const & affected_sop_class_uid,
        Value::Integer priority, Value::String const & move_destination,
        DataSet && dataset);

    /**
     * @brief Create a C-MOVE-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-MOVE-RQ.
     */
    CMoveRequest(Message const & message);

    /**
     * @brief Create a C-MOVE-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-MOVE-RQ.
     */
    CMoveRequest(Message && message);

    /// @brief Destructor.
    virtual ~CMoveRequest();

    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        affected_sop_class_uid, registry::AffectedSOPClassUID)
    ODIL_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(priority, registry::Priority)
    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        move_destination, registry::MoveDestination)

private:
    void _create(
        Value::String const & affected_sop_class_uid,
        Value::Integer priority, Value::String const & move_destination,
        DataSet const & dataset);
    void _parse(Message const & message);
};

}

}

#endif // _f6e243d2_6113_4fe3_8d04_3f034fc796bf
