/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/StoreSCP.h"

#include <functional>

#include "dcmtkpp/DcmtkAssociation.h"
#include "dcmtkpp/message/CStoreRequest.h"
#include "dcmtkpp/message/CStoreResponse.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/message/Message.h"
#include "dcmtkpp/Network.h"
#include "dcmtkpp/SCP.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

StoreSCP
::StoreSCP()
: SCP(), _callback()
{
    // Nothing else.
}

StoreSCP
::StoreSCP(Network * network, DcmtkAssociation * association)
: SCP(network, association), _callback()
{
    // Nothing else.
}

StoreSCP
::StoreSCP(Network * network, DcmtkAssociation * association, Callback const & callback)
: SCP(network, association), _callback()
{
    this->set_callback(callback);
}

StoreSCP
::~StoreSCP()
{
    // Nothing to do.
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
::operator()(message::Message const & message)
{
    message::CStoreRequest const request(message);

    Value::Integer status=message::CStoreResponse::Success;

    try
    {
        status = this->_callback(request);
    }
    catch(Exception const & exception)
    {
        status = message::CStoreResponse::ProcessingFailure;
        // Error Comment
        // Error ID
        // Affected SOP Class UID
    }

    message::CStoreResponse const response(request.get_message_id(), status);
    this->_send(response, request.get_affected_sop_class_uid());
}

}
