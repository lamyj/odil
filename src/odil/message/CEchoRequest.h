/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _aec786b8_0074_4cb2_b9a1_4bf26bbd20fc
#define _aec786b8_0074_4cb2_b9a1_4bf26bbd20fc

#include "odil/message/Request.h"
#include "odil/odil.h"
#include "odil/registry.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief C-ECHO-RQ message.
class ODIL_API CEchoRequest: public Request
{
public:
    /**
     * @brief Create an echo request with given Message ID and
     * affected SOP class UID.
     */
    CEchoRequest(
        Value::Integer message_id,
        Value::String const & affected_sop_class_uid);

    /**
     * @brief Create a C-ECHO-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-ECHO-RQ.
     */
    CEchoRequest(std::shared_ptr<Message const> message);

    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        affected_sop_class_uid, registry::AffectedSOPClassUID)
};

}

}

#endif // _aec786b8_0074_4cb2_b9a1_4bf26bbd20fc
