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
    
    /// @brief Return the Affected SOP Class UID element of the command set.
    std::string get_affected_sop_class_uid() const;

    /// @brief Set the Affected SOP Class UID element of the command set.
    void set_affected_sop_class_uid(std::string const & affected_sop_class_uid);

    /// @brief Return the Priority element of the command set.
    Uint16 get_priority() const;

    /// @brief Set the Affected SOP Class UID element of the command set.
    void set_priority(Uint16 priority);
};

}

#endif // _74cfa9e7_da35_4130_a941_e17cb6932f60
