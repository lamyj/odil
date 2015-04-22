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

#include "dcmtkpp/ElementAccessor.h"
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

    std::string const affected_sop_class_uid = ElementAccessor<std::string>::get(
        message.get_command_set(), DCM_AffectedSOPClassUID);
    this->set_affected_sop_class_uid(affected_sop_class_uid);

    Uint16 const priority = ElementAccessor<Uint16>::get(
        message.get_command_set(), DCM_Priority);
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

}
