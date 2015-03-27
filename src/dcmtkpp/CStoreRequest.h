/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b85a19af_b74d_4c96_89a0_f30a41b790b3
#define _b85a19af_b74d_4c96_89a0_f30a41b790b3

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/Request.h"

namespace dcmtkpp
{

/// @brief C-STORE-RQ message.
class CStoreRequest: public Request
{
public:
    /**
     * @brief Create an store request with given Message ID,
     * affected SOP class UID, priority, and data set.
     */
    CStoreRequest(
        Uint16 message_id, std::string const & affected_sop_class_uid,
        std::string const & affected_sop_instance_uid,
        Uint16 priority, DcmDataset const * dataset);

    /**
     * @brief Create a C-STORE-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-STORE-RQ.
     */
    CStoreRequest(Message const & message);

    /// @brief Destructor.
    virtual ~CStoreRequest();
    
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(
        affected_sop_class_uid, AffectedSOPClassUID, EVR_UI)
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(
        affected_sop_instance_uid, AffectedSOPInstanceUID, EVR_UI)
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(priority, Priority, EVR_US)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(
        move_originator_ae_title, MoveOriginatorApplicationEntityTitle, EVR_AE)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(
        move_originator_message_id, MoveOriginatorMessageID, EVR_US)
};

}

#endif // _b85a19af_b74d_4c96_89a0_f30a41b790b3
