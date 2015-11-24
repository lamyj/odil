/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _97fc1bfc_4cff_40f2_a1ed_4550c71a0bda
#define _97fc1bfc_4cff_40f2_a1ed_4550c71a0bda

#include "dcmtkpp/message/Message.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

namespace message
{

/// @brief Base class for cancellation messages.
class Cancellation: public Message
{
public:
    /// @brief Create a response with given message id being responded to.
    Cancellation(Uint16 message_id_being_responded_to);

    /**
     * @brief Create a response from the Message ID Being Responded To.
     *
     * Raise an exception is this element is missing.
     */
    Cancellation(Message const & message);

    /// @brief Destructor.
    ~Cancellation();

    DCMTKPP_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(
        message_id_being_responded_to, registry::MessageIDBeingRespondedTo);
};

}

}

#endif // _97fc1bfc_4cff_40f2_a1ed_4550c71a0bda
