/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#ifndef _266252d9_e801_479e_a805_004b101c5250
#define _266252d9_e801_479e_a805_004b101c5250

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/Message.h"
#include "dcmtkpp/Response.h"

namespace dcmtkpp
{

/// @brief C-ECHO-RSP message.
class CEchoResponse: public Response
{
public:
    /**
     * @brief Create an echo response with given Message ID and
     * affected SOP class UID.
     */
    CEchoResponse(
        Uint16 message_id_being_responded_to, Uint16 status,
        std::string const & affected_sop_class_uid);

    /**
     * @brief Create a C-ECHO-RSP from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-ECHO-RSP.
     */
    CEchoResponse(Message const & message);

    /// @brief Destructor.
    virtual ~CEchoResponse();
    
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(
        affected_sop_class_uid, DCM_AffectedSOPClassUID, EVR_UI)
};

}

#endif // _266252d9_e801_479e_a805_004b101c5250
