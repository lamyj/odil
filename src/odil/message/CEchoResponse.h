/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#ifndef _266252d9_e801_479e_a805_004b101c5250
#define _266252d9_e801_479e_a805_004b101c5250

#include "odil/odil.h"
#include "odil/registry.h"
#include "odil/message/Response.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief C-ECHO-RSP message.
class ODIL_API CEchoResponse: public Response
{
public:
    /**
     * @brief Create an echo response with given Message ID and
     * affected SOP class UID.
     */
    CEchoResponse(
        Value::Integer message_id_being_responded_to, Value::Integer status,
        Value::String const & affected_sop_class_uid);

    /**
     * @brief Create a C-ECHO-RSP from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-ECHO-RSP.
     */
    CEchoResponse(std::shared_ptr<Message const> message);

    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        affected_sop_class_uid, registry::AffectedSOPClassUID)
};

}

}

#endif // _266252d9_e801_479e_a805_004b101c5250
