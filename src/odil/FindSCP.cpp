/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/FindSCP.h"

#include <memory>

#include "odil/Association.h"
#include "odil/Exception.h"
#include "odil/SCP.h"
#include "odil/message/CFindRequest.h"
#include "odil/message/CFindResponse.h"
#include "odil/message/Response.h"

namespace odil
{

FindSCP
::FindSCP(Association & association)
: SCP(association), _generator(nullptr)
{
    // Nothing else.
}

FindSCP
::FindSCP(
    Association & association,
    std::shared_ptr<DataSetGenerator> const & generator)
: SCP(association), _generator(nullptr)
{
    this->set_generator(generator);
}

FindSCP
::~FindSCP()
{
    // Nothing to do.
}

SCP::DataSetGenerator const &
FindSCP
::get_generator() const
{
    return *this->_generator;
}

void
FindSCP
::set_generator(std::shared_ptr<DataSetGenerator> const & generator)
{
    this->_generator = generator;
}

void
FindSCP
::operator()(message::Message const & message)
{
    message::CFindRequest const request(message);

    Value::Integer final_status = message::CFindResponse::Success;
    DataSet status_fields;

    try
    {
        this->_generator->initialize(request);
        while(!this->_generator->done())
        {
            auto const data_set = this->_generator->get();
            message::CFindResponse const response(
                request.get_message_id(), message::CFindResponse::Pending,
                data_set);
            this->_association.send_message(
                response, request.get_affected_sop_class_uid());
            this->_generator->next();
        }
    }
    catch(SCP::Exception const & e)
    {
        final_status = e.status;
        status_fields = e.status_fields;
    }
    catch(odil::Exception const & e)
    {
        status_fields.add(registry::ErrorComment, {e.what()});
        final_status = message::CFindResponse::UnableToProcess;
    }

    message::CFindResponse response(request.get_message_id(), final_status);
    response.set_status_fields(status_fields);
    this->_association.send_message(
        response, request.get_affected_sop_class_uid());
}

}
