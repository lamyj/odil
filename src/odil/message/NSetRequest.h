/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _8125ab8d_bf37_4116_8ca8_93151ba022a8
#define _8125ab8d_bf37_4116_8ca8_93151ba022a8

#include "odil/message/Request.h"
#include "odil/odil.h"
#include "odil/registry.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief N-Set-RQ message.
class ODIL_API NSetRequest: public Request
{
public:
    /**
     * @brief Create a N-Set-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a N-Set-RQ.
     */
    NSetRequest(Message const & message);

    /**
     * @brief Create an NSet request with given Message ID and
     * requested SOP class UID and SOP Instance UID.
     */
    NSetRequest(
            Value::Integer message_id,
            Value::String const & requested_sop_class_uid,
            Value::String const & requested_sop_instance_uid,
            DataSet const & dataset //will be used to describe list of modifications to do.
            );

    /// @brief Destructor.
    virtual ~NSetRequest();

    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        requested_sop_class_uid, registry::RequestedSOPClassUID)
    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        requested_sop_instance_uid, registry::RequestedSOPInstanceUID)

};

}

}

#endif // _8125ab8d_bf37_4116_8ca8_93151ba022a8
