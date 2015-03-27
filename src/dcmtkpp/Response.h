/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _0dd2e31e_212a_494a_a8d3_93b235336658
#define _0dd2e31e_212a_494a_a8d3_93b235336658

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/Message.h"

namespace dcmtkpp
{

/// @brief Base class for all DIMSE response messages.
class Response: public Message
{
public:
    /// @brief Create a response with given message id and status;
    Response(Uint16 message_id_being_responded_to, Uint16 status);

    /**
     * @brief Create a response from the Message ID Being Responded To and the
     * Status stored in the message command set.
     *
     * Raise an exception is either of those elements is missing.
     */
    Response(Message const & message);

    /// @brief Destructor.
    virtual ~Response();
    
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(
        message_id_being_responded_to, DCM_MessageIDBeingRespondedTo, EVR_US)
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(status, DCM_Status, EVR_US)
};

}

#endif // _0dd2e31e_212a_494a_a8d3_93b235336658
