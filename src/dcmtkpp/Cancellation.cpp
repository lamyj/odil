/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/Cancellation.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcvr.h>
#include <dcmtk/dcmnet/dimse.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/Message.h"

namespace dcmtkpp
{

Cancellation
::Cancellation(Uint16 message_id_being_responded_to)
: Message()
{
    this->set_command_field(DIMSE_C_CANCEL_RQ);
    this->set_message_id_being_responded_to(message_id_being_responded_to);
}

Cancellation
::Cancellation(Message const & message)
{
    if(message.get_command_field() != DIMSE_C_CANCEL_RQ)
    {
        throw Exception("Message is not a C-CANCEL-RQ");
    }
    this->set_command_field(message.get_command_field());

    Uint16 const message_id = ElementAccessor<Uint16>::get(
        message.get_command_set(), DCM_MessageIDBeingRespondedTo);
    this->set_message_id_being_responded_to(message_id);

    this->set_data_set(message.get_data_set());
}

Cancellation
::~Cancellation()
{
    // Nothing to do.
}

}
