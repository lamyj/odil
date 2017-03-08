/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _6a22f126_7cc6_47ab_81c2_5f66b2714345
#define _6a22f126_7cc6_47ab_81c2_5f66b2714345

#include "odil/DataSet.h"
#include "odil/odil.h"
#include "odil/registry.h"
#include "odil/message/Request.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief C-GET-RQ message.
class ODIL_API CGetRequest: public Request
{
public:
    /**
     * @brief Create an get request with given Message ID,
     * affected SOP class UID, priority, and data set.
     */
    CGetRequest(
        Value::Integer message_id, Value::String const & affected_sop_class_uid,
        Value::Integer priority, DataSet const & dataset);

    /**
     * @brief Create a C-GET-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-GET-RQ.
     */
    CGetRequest(Message const & message);

    /// @brief Destructor.
    virtual ~CGetRequest();

    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        affected_sop_class_uid, registry::AffectedSOPClassUID)
    ODIL_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(priority, registry::Priority)
};

}

}

#endif // _6a22f126_7cc6_47ab_81c2_5f66b2714345
