/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/SCU.h"

#include <string>

#include <unistd.h>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/CEchoRequest.h"
#include "dcmtkpp/CEchoResponse.h"
#include "dcmtkpp/Message.h"

namespace dcmtkpp
{

SCU
::SCU()
: ServiceRole(), _affected_sop_class("")
{
    // Nothing else
}

SCU
::~SCU()
{
    // Nothing to do.
}

std::string const &
SCU
::get_affected_sop_class() const
{
    return this->_affected_sop_class;
}
    
void 
SCU
::set_affected_sop_class(std::string const & sop_class)
{
    this->_affected_sop_class = sop_class;
}

void
SCU
::echo() const
{
    Uint16 const message_id = this->_association->get_association()->nextMsgID++;
    
    CEchoRequest const request(message_id, UID_VerificationSOPClass);
    this->_send(request, request.get_affected_sop_class_uid());
    
    CEchoResponse const response = this->_receive<CEchoResponse>();
    if(response.get_message_id_being_responded_to() != message_id)
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response MsgId: "
                << response.get_message_id_being_responded_to() 
                << "(expected: " << message_id << ")";
        throw Exception(message.str());
    }
}

}
