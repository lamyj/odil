/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/EchoSCP.h"

#include <functional>

#include "odil/Association.h"
#include "odil/SCP.h"
#include "odil/Value.h"
#include "odil/message/CEchoRequest.h"
#include "odil/message/CEchoResponse.h"
#include "odil/message/Message.h"

namespace odil
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
::operator()(std::shared_ptr<message::Message const> message)
{
    auto request = std::make_shared<message::CEchoRequest const>(message);
    this->operator()(request);
}

void
EchoSCP
::operator()(std::shared_ptr<message::CEchoRequest const> request)
{
    Value::Integer status=message::CEchoResponse::Success;
    std::shared_ptr<DataSet> status_fields;

    try
    {
        status = this->_callback(request);
    }
    catch(SCP::Exception const & e)
    {
        status = e.status;
        status_fields = e.status_fields;
    }
    catch(odil::Exception const &)
    {
        status = message::CEchoResponse::ProcessingFailure;
    }

    auto response = std::make_shared<message::CEchoResponse>(
        request->get_message_id(), status, request->get_affected_sop_class_uid());
    response->set_status_fields(status_fields);
    this->_association.send_message(
        response, request->get_affected_sop_class_uid());
}

}
