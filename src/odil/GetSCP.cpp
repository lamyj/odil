/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/GetSCP.h"

#include <memory>

#include "odil/Association.h"
#include "odil/Exception.h"
#include "odil/SCP.h"
#include "odil/StoreSCU.h"
#include "odil/message/CGetRequest.h"
#include "odil/message/CGetResponse.h"
#include "odil/message/Response.h"

namespace odil
{

GetSCP
::GetSCP(Association & association)
: SCP(association), _generator(nullptr)
{
    // Nothing else.
}

GetSCP
::GetSCP(
    Association & association,
    std::shared_ptr<DataSetGenerator> const & generator)
: SCP(association), _generator(nullptr)
{
    this->set_generator(generator);
}

GetSCP
::~GetSCP()
{
    // Nothing to do.
}

GetSCP::DataSetGenerator const &
GetSCP
::get_generator() const
{
    return *this->_generator;
}

void
GetSCP
::set_generator(std::shared_ptr<DataSetGenerator> const & generator)
{
    this->_generator = generator;
}

void
GetSCP
::operator()(message::Message const & message)
{
    message::CGetRequest const request(message);

    StoreSCU store_scu(this->_association);

    Value::Integer final_status = message::CGetResponse::Success;
    DataSet status_fields;
    unsigned int remaining_sub_operations = 0;
    unsigned int completed_sub_operations=0;
    unsigned int failed_sub_operations=0;
    unsigned int warning_sub_operations=0;

    try
    {
        this->_generator->initialize(request);
        remaining_sub_operations = this->_generator->count();

        while(!this->_generator->done())
        {
            message::CGetResponse response(
                request.get_message_id(), message::CGetResponse::Pending);
            response.set_number_of_remaining_sub_operations(
                remaining_sub_operations);
            response.set_number_of_completed_sub_operations(
                completed_sub_operations);
            response.set_number_of_failed_sub_operations(
                failed_sub_operations);
            response.set_number_of_warning_sub_operations(
                warning_sub_operations);
            this->_association.send_message(
                response, request.get_affected_sop_class_uid());

            auto const data_set = this->_generator->get();
            store_scu.set_affected_sop_class(data_set);
            try
            {
                store_scu.store(data_set);

                --remaining_sub_operations;
                ++completed_sub_operations;
            }
            catch(Exception const &)
            {
                ++failed_sub_operations;
            }

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
        final_status = message::CGetResponse::UnableToProcess;
    }

    message::CGetResponse response(request.get_message_id(), final_status);
    response.set_status_fields(status_fields);
    response.set_number_of_remaining_sub_operations(remaining_sub_operations);
    response.set_number_of_completed_sub_operations(completed_sub_operations);
    response.set_number_of_failed_sub_operations(failed_sub_operations);
    response.set_number_of_warning_sub_operations(warning_sub_operations);
    this->_association.send_message(
        response, request.get_affected_sop_class_uid());
}

}
