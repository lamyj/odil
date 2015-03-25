/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _8d06a300_6aee_4d1f_bf10_ecdf4916ae9f
#define _8d06a300_6aee_4d1f_bf10_ecdf4916ae9f

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/Message.h"

namespace dcmtkpp
{

/// @brief Base class for all DIMSE request messages.
class Request: public Message
{
public:
    /// @brief Create a request with given Message ID.
    Request(Uint16 message_id);

    /**
     * @brief Create a request from the Message ID stored in the message
     * command set.
     *
     * Raise an exception is either of this element is missing.
     */
    Request(Message const & message);

    /// @brief Destructor.
    virtual ~Request();
    
    /// @brief Return the Message ID element of the command set.
    Uint16 get_message_id() const;

    /// @brief Set the Message ID element of the command set.
    void set_message_id(Uint16 message_id);
};

}

#endif // _8d06a300_6aee_4d1f_bf10_ecdf4916ae9f
