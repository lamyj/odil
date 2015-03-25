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

class CEchoResponse: public Response
{
public:
    CEchoResponse(
        Uint16 message_id_being_responded_to, Uint16 status,
        std::string const & affected_sop_class_uid);
    CEchoResponse(Message const & message);
    virtual ~CEchoResponse();
    
    std::string get_affected_sop_class_uid() const;
    void set_affected_sop_class_uid(std::string const & affected_sop_class_uid);
};

}

#endif // _266252d9_e801_479e_a805_004b101c5250
