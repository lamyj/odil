/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#ifndef _5fd36547_9498_4cf3_87cc_737af51e93a9
#define _5fd36547_9498_4cf3_87cc_737af51e93a9

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Response.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

/// @brief C-FIND-RSP message.
class CFindResponse: public Response
{
public:
    /**
     * @brief Create an find response with given Message ID, and status.
     */
    CFindResponse(
        Value::Integer message_id_being_responded_to, Value::Integer status);

    /**
     * @brief Create an find response with given Message ID, status,
     * and data set.
     */
    CFindResponse(
        Value::Integer message_id_being_responded_to, Value::Integer status,
        DataSet const & dataset);

    /**
     * @brief Create a C-FIND-RSP from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-FIND-RSP.
     */
    CFindResponse(Message const & message);

    /// @brief Destructor.
    virtual ~CFindResponse();
    
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(message_id, registry::MessageID)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(
        affected_sop_class_uid, registry::AffectedSOPClassUID)
};

}

#endif // _5fd36547_9498_4cf3_87cc_737af51e93a9
