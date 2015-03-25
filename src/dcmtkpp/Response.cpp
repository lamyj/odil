/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Response.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Message.h"

namespace dcmtkpp
{

Response
::Response(Uint16 message_id_being_responded_to, Uint16 status)
: Message()
{
    this->set_message_id_being_responded_to(message_id_being_responded_to);
    this->set_status(status);
}

Response
::Response(Message const & message)
: Message()
{
    auto command_set = const_cast<DcmDataset &>(message.get_command_set());
    
    OFCondition condition;
    
    Uint16 message_id;
    condition = command_set.findAndGetUint16(
        DCM_MessageIDBeingRespondedTo, message_id);
    if(condition.bad())
    {
        throw Exception(condition);
    }
    this->set_message_id_being_responded_to(message_id);
    
    Uint16 status;
    condition = command_set.findAndGetUint16(DCM_Status, status);
    if(condition.bad())
    {
        throw Exception(condition);
    }
    this->set_status(status);
}

Response
::~Response()
{
    // Nothing to do.
}

Uint16 
Response
::get_message_id_being_responded_to() const
{
    auto command_set = const_cast<DcmDataset &>(this->_command_set);
    Uint16 message_id;
    
    auto const condition = command_set.findAndGetUint16(
        DCM_MessageIDBeingRespondedTo, message_id);
    if(condition.bad())
    {
        throw Exception(condition);
    }
    
    return message_id;
}

void 
Response
::set_message_id_being_responded_to(Uint16 message_id_being_responded_to)
{
    auto const condition = this->_command_set.putAndInsertUint16(
        DCM_MessageIDBeingRespondedTo, message_id_being_responded_to);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

Uint16 
Response
::get_status() const
{
    auto command_set = const_cast<DcmDataset &>(this->_command_set);
    Uint16 status;
    
    auto const condition = command_set.findAndGetUint16(DCM_Status, status);
    if(condition.bad())
    {
        throw Exception(condition);
    }
    
    return status;
}

void 
Response
::set_status(Uint16 status)
{
    auto const condition = this->_command_set.putAndInsertUint16(
        DCM_Status, status);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

}
