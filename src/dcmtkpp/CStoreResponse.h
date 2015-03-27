/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7e193624_081c_47dd_a011_986e96916ea9
#define _7e193624_081c_47dd_a011_986e96916ea9

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/Response.h"

namespace dcmtkpp
{

/// @brief C-STORE-RSP message.
class CStoreResponse: public Response
{
public:
    /**
     * @brief Create an store response with given Message ID, and status.
     */
    CStoreResponse(Uint16 message_id_being_responded_to, Uint16 status);

    /**
     * @brief Create a C-STORE-RSP from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-STORE-RSP.
     */
    CStoreResponse(Message const & message);

    /// @brief Destructor.
    virtual ~CStoreResponse();

    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(message_id, DCM_MessageID, EVR_US)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(
        affected_sop_class_uid, DCM_AffectedSOPClassUID, EVR_UI)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(
        affected_sop_instance_uid, DCM_AffectedSOPInstanceUID, EVR_UI)
};

}

#endif // _7e193624_081c_47dd_a011_986e96916ea9
