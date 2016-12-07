/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#ifndef __NSETRESPONSE_H__
#define __NSETRESPONSE_H__

#include "odil/registry.h"
#include "odil/message/Response.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief N-Set-RSP message.
class NSetResponse: public Response
{
public:
    /**
     * @brief Create an NSet response with given Message ID and
     * affected SOP class UID.
     */
    NSetResponse(
        Value::Integer const & message_id_being_responded_to,
        Value::Integer status,
        Value::String const & requested_sop_class_uid ,
        Value::String const & requested_sop_instance_uid
            );

    /**
     * @brief Create a N-Set-RSP from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-NSet-RSP.
     */
    NSetResponse(Message const & message);

    /// @brief Destructor.
    virtual ~NSetResponse();
    
    ODIL_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO( message_id_being_responded_to, registry::MessageIDBeingRespondedTo )
    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO( requested_sop_class_uid, registry::AffectedSOPClassUID )
    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO( requested_sop_instance_uid, registry::RequestedSOPInstanceUID )

};

}

}

#endif // __NSETRESPONSE_H__
