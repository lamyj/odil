/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "CStoreRequest.h"

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

CStoreRequest
::CStoreRequest(
    Uint16 message_id, std::string const & affected_sop_class_uid,
    std::string const & affected_sop_instance_uid,
    Uint16 priority, DcmDataset const * dataset)
: Request(message_id)
{
    this->set_command_field(DIMSE_C_STORE_RQ);
    this->set_affected_sop_class_uid(affected_sop_class_uid);
    this->set_affected_sop_instance_uid(affected_sop_instance_uid);
    this->set_priority(priority);

    if(dataset == NULL || const_cast<DcmDataset*>(dataset)->isEmpty())
    {
        throw Exception("Data set is required");
    }
    this->set_data_set(dataset);
}

CStoreRequest
::CStoreRequest(Message const & message)
: Request(message)
{
    if(message.get_command_field() != DIMSE_C_STORE_RQ)
    {
        throw Exception("Message is not a C-STORE-RQ");
    }
    this->set_command_field(message.get_command_field());

    DcmDataset const & command_set(message.get_command_set());

    this->set_affected_sop_class_uid(
        ElementAccessor<EVR_UI>::get(command_set, DCM_AffectedSOPClassUID));
    this->set_affected_sop_instance_uid(
        ElementAccessor<EVR_UI>::get(command_set, DCM_AffectedSOPInstanceUID));
    this->set_priority(ElementAccessor<EVR_US>::get(command_set, DCM_Priority));

    DCMTKPP_MESSAGE_SET_OPTIONAL_FIELD_MACRO(
        this->_command_set,
        move_originator_ae_title, MoveOriginatorApplicationEntityTitle, EVR_AE)
    DCMTKPP_MESSAGE_SET_OPTIONAL_FIELD_MACRO(
        this->_command_set,
        move_originator_message_id, MoveOriginatorMessageID, EVR_US)

    if(message.get_data_set() == NULL ||
       const_cast<DcmDataset*>(message.get_data_set())->isEmpty())
    {
        throw Exception("Data set is required");
    }
    this->set_data_set(message.get_data_set());
}

CStoreRequest
::~CStoreRequest()
{
    // Nothing to do.
}

}
