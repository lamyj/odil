/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _6a22f126_7cc6_47ab_81c2_5f66b2714345
#define _6a22f126_7cc6_47ab_81c2_5f66b2714345

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcvr.h>

#include "dcmtkpp/Request.h"

namespace dcmtkpp
{

/// @brief C-GET-RQ message.
class CGetRequest: public Request
{
public:
    /**
     * @brief Create an get request with given Message ID,
     * affected SOP class UID, priority, and data set.
     */
    CGetRequest(
        Uint16 message_id, std::string const & affected_sop_class_uid,
        Uint16 priority, DcmDataset const * dataset);

    /**
     * @brief Create a C-GET-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-GET-RQ.
     */
    CGetRequest(Message const & message);

    /// @brief Destructor.
    virtual ~CGetRequest();

    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(
        affected_sop_class_uid, DCM_AffectedSOPClassUID, std::string)
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(priority, DCM_Priority, Uint16)
};

}

#endif // _6a22f126_7cc6_47ab_81c2_5f66b2714345
