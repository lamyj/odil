/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/GetSCP.h"

#include <memory>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/SCP.h"
#include "dcmtkpp/StoreSCU.h"
#include "dcmtkpp/message/CGetRequest.h"
#include "dcmtkpp/message/CGetResponse.h"
#include "dcmtkpp/message/Response.h"

namespace dcmtkpp
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

SCP::DataSetGenerator const &
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

    unsigned int remaining_sub_operations=0;
    unsigned int completed_sub_operations=0;
    unsigned int failed_sub_operations=0;
    unsigned int warning_sub_operations=0;

    try
    {
        this->_generator->initialize(request);
        while(!this->_generator->done())
        {
            auto const data_set = this->_generator->get();
            store_scu.set_affected_sop_class(data_set);
            store_scu.store(data_set);

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

            this->_generator->next();
        }
    }
    catch(Exception const & e)
    {
        message::CGetResponse response(
            request.get_message_id(), message::CGetResponse::UnableToProcess);
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
        return;
    }

    message::CGetResponse response(
        request.get_message_id(), message::CGetResponse::Success);
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
}

}
