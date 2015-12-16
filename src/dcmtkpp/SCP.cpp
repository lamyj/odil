/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "SCP.h"

#include "dcmtkpp/DcmtkAssociation.h"
#include "dcmtkpp/message/CEchoRequest.h"
#include "dcmtkpp/message/CEchoResponse.h"
#include "dcmtkpp/message/Message.h"
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
::SCP(Network * network, DcmtkAssociation * association)
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
::_send_echo_response(message::CEchoRequest const & request) const
{
    message::CEchoResponse response(
        request.get_message_id(), message::CEchoResponse::Success,
        request.get_affected_sop_class_uid());
    this->_send(response, request.get_affected_sop_class_uid());
}

}
