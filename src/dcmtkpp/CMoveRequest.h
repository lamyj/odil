/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f6e243d2_6113_4fe3_8d04_3f034fc796bf
#define _f6e243d2_6113_4fe3_8d04_3f034fc796bf

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcvr.h>

#include "dcmtkpp/Request.h"

namespace dcmtkpp
{

/// @brief C-MOVE-RQ message.
class CMoveRequest: public Request
{
public:
    /**
     * @brief Create an move request with given Message ID,
     * affected SOP class UID, priority, move destination, and data set.
     */
    CMoveRequest(
        Uint16 message_id, std::string const & affected_sop_class_uid,
        Uint16 priority, std::string const & move_destination,
        DcmDataset const * dataset);

    /**
     * @brief Create a C-MOVE-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-MOVE-RQ.
     */
    CMoveRequest(Message const & message);

    /// @brief Destructor.
    virtual ~CMoveRequest();

    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(
        affected_sop_class_uid, DCM_AffectedSOPClassUID, EVR_UI)
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(priority, DCM_Priority, EVR_US)
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(
        move_destination, DCM_MoveDestination, EVR_AE)
};

}

#endif // _f6e243d2_6113_4fe3_8d04_3f034fc796bf
