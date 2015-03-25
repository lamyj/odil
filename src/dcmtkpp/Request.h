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
    Request(Uint16 message_id);
    virtual ~Request();
    
    Uint16 get_message_id() const;
    void set_message_id(Uint16 message_id);
};

}

#endif // _8d06a300_6aee_4d1f_bf10_ecdf4916ae9f
