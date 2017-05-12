/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _9a741b7f_0254_4eac_9bbd_04b719c1f86a
#define _9a741b7f_0254_4eac_9bbd_04b719c1f86a

#include "odil/message/Request.h"
#include "odil/odil.h"
#include "odil/registry.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief N-Create-RQ message.
class ODIL_API NCreateRequest: public Request
{
public:
    /**
     * @brief Create an NCreate request with given Message ID and
     * affected SOP class UID.
     */
    NCreateRequest(
        Value::Integer message_id,
        Value::String const & affected_sop_class_uid,
        DataSet const & dataset);

    /**
     * @brief Create a N-Create-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a N-Create-RQ.
     */
    NCreateRequest(Message const & message);

    /// @brief Destructor.
    virtual ~NCreateRequest();

    ODIL_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(
        message_id, registry::MessageID)

    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        affected_sop_class_uid, registry::AffectedSOPClassUID)

    ODIL_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(
        affected_sop_instance_uid, registry::AffectedSOPInstanceUID)

    ODIL_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(
        attribute_list, registry::AttributeIdentifierList)

};

}

}

#endif // _9a741b7f_0254_4eac_9bbd_04b719c1f86a
