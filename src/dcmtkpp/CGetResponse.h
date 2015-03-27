/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#ifndef _7b9819f1_d7a2_4898_a850_3ed6a61f08c6
#define _7b9819f1_d7a2_4898_a850_3ed6a61f08c6

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/Message.h"
#include "dcmtkpp/Response.h"

namespace dcmtkpp
{

/// @brief C-GET-RSP message.
class CGetResponse: public Response
{
public:
    /**
     * @brief Create an get response with given Message ID, status,
     * and data set.
     */
    CGetResponse(
        Uint16 message_id_being_responded_to, Uint16 status,
        DcmDataset const * dataset);

    /**
     * @brief Create a C-GET-RSP from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-GET-RSP.
     */
    CGetResponse(Message const & message);

    /// @brief Destructor.
    virtual ~CGetResponse();
    
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(message_id, DCM_MessageID, EVR_US)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(
        affected_sop_class_uid, DCM_AffectedSOPClassUID, EVR_UI)

    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(
        number_of_remaining_sub_operations, DcmTagKey(0x0000, 0x1020), EVR_US)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(
        number_of_completed_sub_operations, DcmTagKey(0x0000, 0x1021), EVR_US)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(
        number_of_failed_sub_operations, DcmTagKey(0x0000, 0x1022), EVR_US)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(
        number_of_warning_sub_operations, DcmTagKey(0x0000, 0x1023), EVR_US)
};

}

#endif // _7b9819f1_d7a2_4898_a850_3ed6a61f08c6
