/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "CFindRequest.h"

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmnet/dimse.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Request.h"

namespace dcmtkpp
{

CFindRequest
::CFindRequest(Uint16 message_id, std::string const & affected_sop_class_uid,
    Uint16 priority, const DcmDataset * dataset)
: Request(message_id)
{
    this->set_command_field(DIMSE_C_FIND_RQ);
    this->set_affected_sop_class_uid(affected_sop_class_uid);
    this->set_priority(priority);
    if(dataset == NULL || const_cast<DcmDataset*>(dataset)->isEmpty())
    {
        throw Exception("Data set is required");
    }
    this->set_data_set(dataset);
}

CFindRequest
::CFindRequest(Message const & message)
: Request(message)
{
    if(message.get_command_field() != DIMSE_C_FIND_RQ)
    {
        throw Exception("Message is not a C-FIND-RQ");
    }
    this->set_command_field(message.get_command_field());

    auto command_set = const_cast<DcmDataset &>(message.get_command_set());

    OFCondition condition;

    OFString affected_sop_class_uid;
    condition = command_set.findAndGetOFString(
        DCM_AffectedSOPClassUID, affected_sop_class_uid);
    if(condition.bad())
    {
        throw Exception(condition);
    }
    this->set_affected_sop_class_uid(affected_sop_class_uid.c_str());

    Uint16 priority;
    condition = command_set.findAndGetUint16(DCM_Priority, priority);
    if(condition.bad())
    {
        throw Exception(condition);
    }
    this->set_priority(priority);

    if(message.get_data_set() == NULL ||
       const_cast<DcmDataset*>(message.get_data_set())->isEmpty())
    {
        throw Exception("Data set is required");
    }
    this->set_data_set(message.get_data_set());
}

CFindRequest
::~CFindRequest()
{
    // Nothing to do.
}

std::string 
CFindRequest
::get_affected_sop_class_uid() const
{
    auto command_set = const_cast<DcmDataset &>(this->_command_set);
    OFString affected_sop_class_uid;
    
    auto const condition = command_set.findAndGetOFString(
        DCM_AffectedSOPClassUID, affected_sop_class_uid);
    if(condition.bad())
    {
        throw Exception(condition);
    }
    
    return std::string(affected_sop_class_uid.c_str());
}

void 
CFindRequest
::set_affected_sop_class_uid(std::string const & affected_sop_class_uid)
{
    auto const condition = this->_command_set.putAndInsertOFStringArray(
        DCM_AffectedSOPClassUID, affected_sop_class_uid.c_str());
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

Uint16
CFindRequest
::get_priority() const
{
    auto command_set = const_cast<DcmDataset &>(this->_command_set);
    Uint16 priority;

    auto const condition = command_set.findAndGetUint16(
        DCM_Priority, priority);
    if(condition.bad())
    {
        throw Exception(condition);
    }

    return priority;
}

void
CFindRequest
::set_priority(Uint16 priority)
{
    auto const condition = this->_command_set.putAndInsertUint16(
        DCM_Priority, priority);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

}
