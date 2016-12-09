/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#ifndef __NCREATERESPONSE_H__
#define __NCREATERESPONSE_H__

#include "odil/registry.h"
#include "odil/message/Response.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief C-NCreate-RSP message.
class NCreateResponse: public Response
{
public:
    /**
     * @brief Create an NCreate response with given Message ID and
     * affected SOP class UID.
     */
    NCreateResponse(
        Value::Integer const & message_id_being_responded_to
            , Value::Integer const & status
            , Value::String const & affected_sop_class_uid);

    /**
     * @brief Create a C-NCreate-RSP from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-NCreate-RSP.
     */
    NCreateResponse(Message const & message);

    /// @brief Destructor.
    virtual ~NCreateResponse();
    
    ODIL_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(
        message_id_being_responded_to, registry::MessageIDBeingRespondedTo)

    ODIL_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(
        affected_sop_class_uid, registry::AffectedSOPClassUID)




};

}

}

#endif // _266252d9_e801_479e_a805_004b101c5250
