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
     * affected SOP class UID, and data set.
     */
    CFindResponse(
        Uint16 message_id_being_responded_to, Uint16 status,
        std::string const & affected_sop_class_uid, DcmDataset const * dataset);

    /**
     * @brief Create a C-FIND-RSP from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-FIND-RSP.
     */
    CFindResponse(Message const & message);

    /// @brief Destructor.
    virtual ~CFindResponse();
    
    /// @brief Return the Affected SOP Class UID element of the command set.
    std::string get_affected_sop_class_uid() const;

    /// @brief Set the Affected SOP Class UID element of the command set.
    void set_affected_sop_class_uid(std::string const & affected_sop_class_uid);
};

}

#endif // _5fd36547_9498_4cf3_87cc_737af51e93a9
