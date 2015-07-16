/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f6e243d2_6113_4fe3_8d04_3f034fc796bf
#define _f6e243d2_6113_4fe3_8d04_3f034fc796bf

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Request.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

/// @brief C-MOVE-RQ message.
class CMoveRequest: public Request
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
     * @brief Create a C-MOVE-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-MOVE-RQ.
     */
    CMoveRequest(Message const & message);

    /// @brief Destructor.
    virtual ~CMoveRequest();

    DCMTKPP_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        affected_sop_class_uid, registry::AffectedSOPClassUID)
    DCMTKPP_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(priority, registry::Priority)
    DCMTKPP_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        move_destination, registry::MoveDestination)
};

}

#endif // _f6e243d2_6113_4fe3_8d04_3f034fc796bf
