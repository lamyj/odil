/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _74cfa9e7_da35_4130_a941_e17cb6932f60
#define _74cfa9e7_da35_4130_a941_e17cb6932f60

#include "dcmtkpp/registry.h"
#include "dcmtkpp/Request.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

/// @brief C-FIND-RQ message.
class CFindRequest: public Request
{
public:
    /**
     * @brief Create an find request with given Message ID,
     * affected SOP class UID, priority, and data set.
     */
    CFindRequest(
        Value::Integer message_id, Value::String const & affected_sop_class_uid,
        Value::Integer priority, DataSet const & dataset);

    /**
     * @brief Create a C-FIND-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-FIND-RQ.
     */
    CFindRequest(Message const & message);

    /// @brief Destructor.
    virtual ~CFindRequest();
    
    DCMTKPP_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        affected_sop_class_uid, registry::AffectedSOPClassUID)
    DCMTKPP_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(priority, registry::Priority)
};

}

#endif // _74cfa9e7_da35_4130_a941_e17cb6932f60
