/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "CEchoRequest.h"

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmnet/dimse.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Request.h"

namespace dcmtkpp
{

CEchoRequest
::CEchoRequest(Uint16 message_id, std::string const & affected_sop_class_uid)
: Request(message_id)
{
    this->set_command_field(DIMSE_C_ECHO_RQ);
    this->set_affected_sop_class_uid(affected_sop_class_uid);
}

CEchoRequest
::CEchoRequest(Message const & message)
: Request(message)
{
    if(message.get_command_field() != DIMSE_C_ECHO_RQ)
    {
        throw Exception("Message is not a C-ECHO-RQ");
    }
    this->set_command_field(message.get_command_field());

    std::string const affected_sop_class_uid = ElementAccessor<EVR_UI>::get(
        message.get_command_set(), DCM_AffectedSOPClassUID);
    this->set_affected_sop_class_uid(affected_sop_class_uid);
}

CEchoRequest
::~CEchoRequest()
{
    // Nothing to do.
}

std::string 
CEchoRequest
::get_affected_sop_class_uid() const
{
    return ElementAccessor<EVR_UI>::get(
        this->_command_set, DCM_AffectedSOPClassUID);
}

void 
CEchoRequest
::set_affected_sop_class_uid(std::string const & affected_sop_class_uid)
{
    ElementAccessor<EVR_UI>::set(
        this->_command_set, DCM_AffectedSOPClassUID, affected_sop_class_uid);
}

}
