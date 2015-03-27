/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#ifndef _5fd36547_9498_4cf3_87cc_737af51e93a9
#define _5fd36547_9498_4cf3_87cc_737af51e93a9

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/Message.h"
#include "dcmtkpp/Response.h"

namespace dcmtkpp
{

/// @brief C-FIND-RSP message.
class CFindResponse: public Response
{
public:
    /**
     * @brief Create an find response with given Message ID, status,
     * and data set.
     */
    CFindResponse(
        Uint16 message_id_being_responded_to, Uint16 status,
        DcmDataset const * dataset);

    /**
     * @brief Create a C-FIND-RSP from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-FIND-RSP.
     */
    CFindResponse(Message const & message);

    /// @brief Destructor.
    virtual ~CFindResponse();
    
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(message_id, DCM_MessageID, EVR_US)
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(
        affected_sop_class_uid, DCM_AffectedSOPClassUID, EVR_UI)
};

}

#endif // _5fd36547_9498_4cf3_87cc_737af51e93a9
