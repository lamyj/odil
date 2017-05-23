/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/Association.h"
#include "odil/NSetSCP.h"
#include "odil/SCP.h"
#include "odil/Value.h"
#include "odil/message/NSetResponse.h"

#include <functional>

namespace odil
{

NSetSCP
::NSetSCP(Association& association)
    : SCP(association), _callback()
{
    // Nothing else.
}

NSetSCP
::NSetSCP(Association& association, Callback const& callback)
    : SCP(association), _callback()
{
    this->set_callback(callback);
}

NSetSCP
::~NSetSCP()
{
    // Nothing to do.
}

NSetSCP::Callback const&
NSetSCP::get_callback() const
{
    return this->_callback;
}

void
NSetSCP
::set_callback(Callback const& callback)
{
    this->_callback = callback;
}

void
NSetSCP
::operator()(message::Message const & message)
{
    message::NSetRequest const request(message);
    this->operator()(request);
}

void
NSetSCP
::operator()(message::Message && message)
{
    message::NSetRequest const request(std::move(message));
    this->operator()(request);
}

void
NSetSCP
::operator()(message::NSetRequest const & request)
{
    Value::Integer status = message::NSetResponse::Success;
    DataSet status_fields;

    try
    {
        status = this->_callback(request);
    }
    catch(SCP::Exception const& e)
    {
        status        = e.status;
        status_fields = e.status_fields;
    }
    catch(odil::Exception const&)
    {
        status = message::NSetResponse::ProcessingFailure;
    }

    message::NSetResponse response(
        request.get_message_id(),
        status,
        request.get_requested_sop_class_uid(),
        request.get_requested_sop_instance_uid() );

    response.set_status_fields(status_fields);

    this->_association.send_message(
        response, request.get_requested_sop_class_uid());
}

}
