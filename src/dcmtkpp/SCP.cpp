/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "SCP.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CEchoRequest.h"
#include "dcmtkpp/CEchoResponse.h"
#include "dcmtkpp/ServiceRole.h"

namespace dcmtkpp
{

SCP
::SCP()
: ServiceRole()
{
    // Nothing else.
}

SCP
::~SCP()
{
    // Nothing to do.
}

void
SCP
::_send_echo_response(CEchoRequest const & request) const
{
    CEchoResponse response(
        request.get_message_id(), STATUS_Success,
        request.get_affected_sop_class_uid());
    this->_send(response, request.get_affected_sop_class_uid());
}

}
