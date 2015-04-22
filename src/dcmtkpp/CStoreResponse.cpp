/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "CStoreResponse.h"

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

CStoreResponse
::CStoreResponse(Uint16 message_id_being_responded_to, Uint16 status)
: Response(message_id_being_responded_to, status)
{
    this->set_command_field(DIMSE_C_STORE_RSP);
}

CStoreResponse
::CStoreResponse(Message const & message)
: Response(message)
{
    if(message.get_command_field() != DIMSE_C_STORE_RSP)
    {
        throw Exception("Message is not a C-STORE-RSP");
    }
    this->set_command_field(message.get_command_field());

    DCMTKPP_MESSAGE_SET_OPTIONAL_FIELD_MACRO(
        message.get_command_set(), message_id, DCM_MessageID, Uint16)
    DCMTKPP_MESSAGE_SET_OPTIONAL_FIELD_MACRO(
        message.get_command_set(), affected_sop_class_uid,
        DCM_AffectedSOPClassUID, std::string)
    DCMTKPP_MESSAGE_SET_OPTIONAL_FIELD_MACRO(
        message.get_command_set(),
        affected_sop_instance_uid, DCM_AffectedSOPInstanceUID, std::string)

    if(message.get_data_set() != NULL &&
       !const_cast<DcmDataset*>(message.get_data_set())->isEmpty())
    {
        throw Exception("Data set must not be present");
    }
    this->set_data_set(message.get_data_set());
}

CStoreResponse
::~CStoreResponse()
{
    // Nothing to do.
}

}
