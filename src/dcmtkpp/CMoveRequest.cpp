/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "CMoveRequest.h"

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

CMoveRequest
::CMoveRequest(Uint16 message_id, std::string const & affected_sop_class_uid,
    Uint16 priority, std::string const & move_destination,
    DcmDataset const * dataset)
: Request(message_id)
{
    this->set_command_field(DIMSE_C_MOVE_RQ);
    this->set_affected_sop_class_uid(affected_sop_class_uid);
    this->set_priority(priority);
    this->set_move_destination(move_destination);
    if(dataset == NULL || const_cast<DcmDataset*>(dataset)->isEmpty())
    {
        throw Exception("Data set is required");
    }
    this->set_data_set(dataset);
}

CMoveRequest
::CMoveRequest(Message const & message)
: Request(message)
{
    if(message.get_command_field() != DIMSE_C_MOVE_RQ)
    {
        throw Exception("Message is not a C-MOVE-RQ");
    }
    this->set_command_field(message.get_command_field());

    std::string const affected_sop_class_uid = ElementAccessor<EVR_UI>::get(
        message.get_command_set(), DCM_AffectedSOPClassUID);
    this->set_affected_sop_class_uid(affected_sop_class_uid);

    Uint16 const priority = ElementAccessor<EVR_US>::get(
        message.get_command_set(), DCM_Priority);
    this->set_priority(priority);

    std::string const move_destination = ElementAccessor<EVR_AE>::get(
        message.get_command_set(), DCM_MoveDestination);
    this->set_move_destination(move_destination);

    if(message.get_data_set() == NULL ||
       const_cast<DcmDataset*>(message.get_data_set())->isEmpty())
    {
        throw Exception("Data set is required");
    }
    this->set_data_set(message.get_data_set());
}

CMoveRequest
::~CMoveRequest()
{
    // Nothing to do.
}

}
