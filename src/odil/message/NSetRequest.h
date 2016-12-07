/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef __NSETREQUEST_H__
#define __NSETREQUEST_H__

#include "odil/message/Request.h"
#include "odil/registry.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief N-Set-RQ message.
class NSetRequest: public Request
{
public:
    /**
     * @brief Create an NSet request with given Message ID and
     * affected SOP class UID.
     */
    NSetRequest(
            Value::Integer message_id,
            Value::String const & requested_sop_class_uid,
            Value::String const & requested_sop_instance_uid,
            Value::Integer const & command_data_set_type,
            DataSet const & dataset);

    /**
     * @brief Create a N-Set-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a N-Set-RQ.
     */
    NSetRequest(Message const & message);

    /// @brief Destructor.
    virtual ~NSetRequest();

    ODIL_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(
            message_id, registry::MessageID )
    
    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        requested_sop_class_uid, registry::RequestedSOPClassUID)
    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        requested_sop_instance_uid, registry::RequestedSOPInstanceUID)
    ODIL_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(command_data_set_type, registry::CommandDataSetType)
    ODIL_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(command_field, registry::CommandDataSetType)


};

}

}

#endif // __NSETREQUEST_H__
