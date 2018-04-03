/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/NCreateSCP.h"

#include <functional>

#include "odil/Association.h"
#include "odil/SCP.h"
#include "odil/Value.h"
#include "odil/message/NCreateResponse.h"

namespace odil
{

NCreateSCP
::NCreateSCP(Association & association)
: SCP(association), _callback()
{
    // Nothing else.
}

NCreateSCP
::NCreateSCP(Association & association, Callback const & callback)
: SCP(association), _callback()
{
    this->set_callback(callback);
}

NCreateSCP::Callback const &
NCreateSCP::get_callback() const
{
    return this->_callback;
}

void
NCreateSCP
::set_callback(Callback const & callback)
{
    this->_callback = callback;
}

void
NCreateSCP
::operator()(std::shared_ptr<message::Message const> message)
{
    auto request = std::make_shared<message::NCreateRequest const>(message);
    this->operator()(request);
}

void
NCreateSCP
::operator()(std::shared_ptr<message::NCreateRequest const> request)
{
    Value::Integer status=message::NCreateResponse::Success;
    auto status_fields = std::make_shared<DataSet>();

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
        status = message::NCreateResponse::ProcessingFailure;
    }

    auto response = std::make_shared<message::NCreateResponse>(
        request->get_message_id(), status,
        request->get_affected_sop_class_uid());
    if(request->has_affected_sop_instance_uid())
    {
        response->set_affected_sop_instance_uid(
            request->get_affected_sop_instance_uid());
    }
    response->set_status_fields(status_fields);
    this->_association.send_message(
        response, request->get_affected_sop_class_uid());
}

}
