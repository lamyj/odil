/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "SCP.h"

#include "dcmtkpp/Association.h"
#include "dcmtkpp/CEchoRequest.h"
#include "dcmtkpp/CEchoResponse.h"
#include "dcmtkpp/Message.h"
#include "dcmtkpp/Network.h"
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
::SCP(Network * network, Association * association)
: ServiceRole(network, association)
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
::receive_and_process()
{
    auto const message = this->_receive();
    (*this)(message);
}

void
SCP
::_send_echo_response(CEchoRequest const & request) const
{
    CEchoResponse response(
        request.get_message_id(), CEchoResponse::Success,
        request.get_affected_sop_class_uid());
    this->_send(response, request.get_affected_sop_class_uid());
}

}
