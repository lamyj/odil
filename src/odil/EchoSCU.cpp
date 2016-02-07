/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/EchoSCU.h"

#include "odil/Association.h"
#include "odil/Exception.h"
#include "odil/message/CEchoRequest.h"
#include "odil/message/CEchoResponse.h"
#include "odil/registry.h"

namespace odil
{

EchoSCU
::EchoSCU(Association & association)
: SCU(association)
{
    // Nothing else.
}

EchoSCU
::~EchoSCU()
{
    // Nothing to do.
}

void
EchoSCU
::echo() const
{
    auto const message_id = this->_association.next_message_id();
    
    message::CEchoRequest const request(
        message_id, registry::VerificationSOPClass);
    this->_association.send_message(
        request, request.get_affected_sop_class_uid());
    
    message::CEchoResponse const response = this->_association.receive_message();
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

