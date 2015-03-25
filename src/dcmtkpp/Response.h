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
    Response(Uint16 message_id_being_responded_to, Uint16 status);
    Response(Message const & message);
    virtual ~Response();
    
    Uint16 get_message_id_being_responded_to() const;
    void set_message_id_being_responded_to(Uint16 message_id_being_responded_to);
    
    Uint16 get_status() const;
    void set_status(Uint16 status);
};

}

#endif // _0dd2e31e_212a_494a_a8d3_93b235336658
