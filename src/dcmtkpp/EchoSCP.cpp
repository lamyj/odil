/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/EchoSCP.h"

#include <functional>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/SCP.h"
#include "dcmtkpp/Value.h"
#include "dcmtkpp/message/CEchoRequest.h"
#include "dcmtkpp/message/CEchoResponse.h"
#include "dcmtkpp/message/Message.h"

namespace dcmtkpp
{

EchoSCP
::EchoSCP(Association & association)
: SCP(association), _callback()
{
    // Nothing else.
}

EchoSCP
::EchoSCP(Association & association, Callback const & callback)
: SCP(association), _callback()
{
    this->set_callback(callback);
}

EchoSCP
::~EchoSCP()
{
    // Nothing to do.
}

EchoSCP::Callback const &
EchoSCP::get_callback() const
{
    return this->_callback;
}

void
EchoSCP
::set_callback(Callback const & callback)
{
    this->_callback = callback;
}

void
EchoSCP
::operator()(message::Message const & message)
{
    message::CEchoRequest const request(message);

    Value::Integer status=message::CEchoResponse::Success;

    try
    {
        status = this->_callback(request);
    }
    catch(Exception const &)
    {
        status = message::CEchoResponse::ProcessingFailure;
        // Error Comment
        // Error ID
        // Affected SOP Class UID
    }

    message::CEchoResponse const response(
        request.get_message_id(), status, request.get_affected_sop_class_uid());
    this->_association.send_message(
        response, request.get_affected_sop_class_uid());
}

}
