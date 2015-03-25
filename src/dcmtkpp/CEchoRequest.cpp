/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "CEchoRequest.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dctagkey.h>
#include <dcmtk/ofstd/oftypes.h>

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
::~CEchoRequest()
{
    // Nothing to do.
}

std::string 
CEchoRequest
::get_affected_sop_class_uid() const
{
    DcmDataset & command_set = const_cast<DcmDataset &>(this->_command_set);
    OFString affected_sop_class_uid;
    
    OFCondition const condition = command_set.findAndGetOFString(
        DCM_AffectedSOPClassUID, affected_sop_class_uid);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

void 
CEchoRequest
::set_affected_sop_class_uid(std::string const & affected_sop_class_uid)
{
    OFCondition const condition = this->_command_set.putAndInsertOFStringArray(
        DCM_AffectedSOPClassUID, affected_sop_class_uid.c_str());
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

}
