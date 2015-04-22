/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _74cfa9e7_da35_4130_a941_e17cb6932f60
#define _74cfa9e7_da35_4130_a941_e17cb6932f60

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/Request.h"

namespace dcmtkpp
{

/// @brief C-FIND-RQ message.
class CFindRequest: public Request
{
public:
    /**
     * @brief Create an find request with given Message ID,
     * affected SOP class UID, priority, and data set.
     */
    CFindRequest(
        Uint16 message_id, std::string const & affected_sop_class_uid,
        Uint16 priority, DcmDataset const * dataset);

    /**
     * @brief Create a C-FIND-RQ from a generic Message.
     *
     * Raise an exception if the Message does not contain a C-FIND-RQ.
     */
    CFindRequest(Message const & message);

    /// @brief Destructor.
    virtual ~CFindRequest();
    
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(
        affected_sop_class_uid, DCM_AffectedSOPClassUID, std::string)
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(priority, DCM_Priority, Uint16)
};

}

#endif // _74cfa9e7_da35_4130_a941_e17cb6932f60
