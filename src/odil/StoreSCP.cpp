/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/StoreSCP.h"

#include <functional>

#include "odil/Association.h"
#include "odil/Exception.h"
#include "odil/SCP.h"
#include "odil/Value.h"
#include "odil/message/CStoreRequest.h"
#include "odil/message/CStoreResponse.h"
#include "odil/message/CStoreRequest.h"
#include "odil/message/CStoreResponse.h"

namespace odil
{

StoreSCP
::StoreSCP(Association & association)
: SCP(association), _callback()
{
    // Nothing else.
}

StoreSCP
::StoreSCP(Association & association, Callback const & callback)
: SCP(association), _callback()
{
    this->set_callback(callback);
}

StoreSCP::Callback const &
StoreSCP
::get_callback() const
{
    return this->_callback;
}

void
StoreSCP
::set_callback(Callback const & callback)
{
    this->_callback = callback;
}

void
StoreSCP
::operator()(std::shared_ptr<message::CStoreRequest> request)
{
    Value::Integer status=message::CStoreResponse::Success;
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
        status = message::CStoreResponse::ProcessingFailure;
    }

    auto response = std::make_shared<message::CStoreResponse>(
        request->get_message_id(), status);
    response->set_status_fields(status_fields);
    this->_association.send_message(
        response, request->get_affected_sop_class_uid());
}

void
StoreSCP
::operator()(std::shared_ptr<message::Message const> message)
{
    auto request = std::make_shared<message::CStoreRequest>(message);
    this->operator()(request);
}

}
