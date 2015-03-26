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

#include "dcmtkpp/ElementAccessor.h"
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
    Uint16 const message_id = ElementAccessor<EVR_US>::get(
        message.get_command_set(), DCM_MessageIDBeingRespondedTo);
    this->set_message_id_being_responded_to(message_id);

    Uint16 const status = ElementAccessor<EVR_US>::get(
        message.get_command_set(), DCM_Status);
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
    return ElementAccessor<EVR_US>::get(
        this->_command_set, DCM_MessageIDBeingRespondedTo);
}

void 
Response
::set_message_id_being_responded_to(Uint16 message_id_being_responded_to)
{
    ElementAccessor<EVR_US>::set(
        this->_command_set,
        DCM_MessageIDBeingRespondedTo, message_id_being_responded_to);
}

Uint16 
Response
::get_status() const
{
    return ElementAccessor<EVR_US>::get(this->_command_set, DCM_Status);
}

void 
Response
::set_status(Uint16 status)
{
    ElementAccessor<EVR_US>::set(this->_command_set, DCM_Status, status);
}

}
