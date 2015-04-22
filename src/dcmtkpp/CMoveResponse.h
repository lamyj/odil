/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#ifndef _b245f6f2_50c3_4c7c_80e1_f03d9c831301
#define _b245f6f2_50c3_4c7c_80e1_f03d9c831301

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/Message.h"
#include "dcmtkpp/Response.h"

namespace dcmtkpp
{

/// @brief C-MOVE-RSP message.
class CMoveResponse: public Response
{
public:
    /**
     * @brief Create an move response with given Message ID, status,
     * and data set.
     */
    CMoveResponse(
        Uint16 message_id_being_responded_to, Uint16 status,
        DcmDataset const * dataset);

    /**
     * @brief Create a C-MOVE-RSP from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-MOVE-RSP.
     */
    CMoveResponse(Message const & message);

    /// @brief Destructor.
    virtual ~CMoveResponse();
    
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(message_id, DCM_MessageID, Uint16)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(
        affected_sop_class_uid, DCM_AffectedSOPClassUID, std::string)

    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(
        number_of_remaining_sub_operations, DcmTagKey(0x0000, 0x1020), Uint16)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(
        number_of_completed_sub_operations, DcmTagKey(0x0000, 0x1021), Uint16)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(
        number_of_failed_sub_operations, DcmTagKey(0x0000, 0x1022), Uint16)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(
        number_of_warning_sub_operations, DcmTagKey(0x0000, 0x1023), Uint16)
};

}

#endif // _b245f6f2_50c3_4c7c_80e1_f03d9c831301
