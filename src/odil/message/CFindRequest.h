/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _74cfa9e7_da35_4130_a941_e17cb6932f60
#define _74cfa9e7_da35_4130_a941_e17cb6932f60

#include "odil/odil.h"
#include "odil/registry.h"
#include "odil/message/Request.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

/// @brief C-FIND-RQ message.
class ODIL_API CFindRequest: public Request
{
public:
    /**
     * @brief Create an find request with given Message ID,
     * affected SOP class UID, priority, and data set.
     */
    CFindRequest(
        Value::Integer message_id, Value::String const & affected_sop_class_uid,
        Value::Integer priority, std::shared_ptr<DataSet> dataset);

    /**
     * @brief Create a C-FIND-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-FIND-RQ.
     */
    CFindRequest(std::shared_ptr<Message> message);
    
    ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO(
        affected_sop_class_uid, registry::AffectedSOPClassUID)
    ODIL_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(priority, registry::Priority)

private:
    void _create(
        Value::String const & affected_sop_class_uid, Value::Integer priority,
        std::shared_ptr<DataSet const> dataset);
    void _parse(std::shared_ptr<Message const> message);
};

}

}

#endif // _74cfa9e7_da35_4130_a941_e17cb6932f60
