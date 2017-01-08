/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b85a19af_b74d_4c96_89a0_f30a41b790b3
#define _b85a19af_b74d_4c96_89a0_f30a41b790b3

#include <string>

#include "odil/DataSet.h"
#include "odil/odil.h"
#include "odil/registry.h"
#include "odil/message/Request.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief C-STORE-RQ message.
class ODIL_API CStoreRequest: public Request
{
public:
    /**
     * @brief Create an store request with given Message ID,
     * affected SOP class UID, priority, and data set.
     */
    CStoreRequest(
        Value::Integer message_id, Value::String const & affected_sop_class_uid,
        Value::String const & affected_sop_instance_uid,
        Value::Integer priority, DataSet const & dataset,
        Value::String const & move_originator_ae_title = "",
        Value::Integer move_originator_message_id = -1);

    /**
     * @brief Create a C-STORE-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-STORE-RQ.
     */
    CStoreRequest(Message const & message);

    /// @brief Destructor.
    virtual ~CStoreRequest();
    
    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        affected_sop_class_uid, registry::AffectedSOPClassUID)
    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        affected_sop_instance_uid, registry::AffectedSOPInstanceUID)
    ODIL_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(priority, registry::Priority)
    ODIL_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(
        move_originator_ae_title, registry::MoveOriginatorApplicationEntityTitle)
    ODIL_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(
        move_originator_message_id, registry::MoveOriginatorMessageID)
};

}

}

#endif // _b85a19af_b74d_4c96_89a0_f30a41b790b3
