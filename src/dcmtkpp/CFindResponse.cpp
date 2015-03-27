/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "CFindResponse.h"

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmnet/dimse.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Response.h"

namespace dcmtkpp
{

CFindResponse
::CFindResponse(
    Uint16 message_id_being_responded_to, Uint16 status,
    DcmDataset const * dataset)
: Response(message_id_being_responded_to, status)
{
    this->set_command_field(DIMSE_C_FIND_RSP);

    this->set_data_set(dataset);
}

CFindResponse
::CFindResponse(Message const & message)
: Response(message)
{
    if(message.get_command_field() != DIMSE_C_FIND_RSP)
    {
        throw Exception("Message is not a C-FIND-RSP");
    }
    this->set_command_field(message.get_command_field());
    
    DCMTKPP_MESSAGE_SET_OPTIONAL_FIELD_MACRO(
        this->_command_set, message_id, MessageID, EVR_US)
    DCMTKPP_MESSAGE_SET_OPTIONAL_FIELD_MACRO(
        this->_command_set, affected_sop_class_uid, AffectedSOPClassUID, EVR_UI)

    this->set_data_set(message.get_data_set());
}

CFindResponse
::~CFindResponse()
{
    // Nothing to do.
}

}
