/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _8d06a300_6aee_4d1f_bf10_ecdf4916ae9f
#define _8d06a300_6aee_4d1f_bf10_ecdf4916ae9f

#include "odil/message/Message.h"
#include "odil/odil.h"
#include "odil/registry.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief Base class for all DIMSE request messages.
class ODIL_API Request: public Message
{
public:
    /// @brief Create a request with given Message ID.
    Request(Value::Integer message_id);

    /**
     * @brief Create a request from the Message ID stored in the message
     * command set.
     *
     * Raise an exception is either of this element is missing.
     */
    Request(std::shared_ptr<Message const> message);

    ODIL_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(
        message_id, registry::MessageID)
};

}

}

#endif // _8d06a300_6aee_4d1f_bf10_ecdf4916ae9f
