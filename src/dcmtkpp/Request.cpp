/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Request.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Message.h"

namespace dcmtkpp
{

Request
::Request(Uint16 message_id)
: Message()
{
    this->set_message_id(message_id);
}

Request
::Request(Message const & message)
: Message()
{
    Uint16 const message_id = ElementAccessor<Uint16>::get(
        message.get_command_set(), DCM_MessageID);
    this->set_message_id(message_id);
}

Request
::~Request()
{
    // Nothing to do.
}

}
