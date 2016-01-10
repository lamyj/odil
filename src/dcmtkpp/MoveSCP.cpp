/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/MoveSCP.h"

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

#include "odil/Association.h"
#include "odil/Exception.h"
#include "odil/SCP.h"
#include "odil/StoreSCU.h"
#include "odil/message/CMoveRequest.h"
#include "odil/message/CMoveResponse.h"
#include "odil/message/Response.h"

namespace odil
{

MoveSCP
::MoveSCP(Association & association)
: SCP(association), _generator(nullptr)
{
    // Nothing else.
}

MoveSCP
::MoveSCP(
    Association & association,
    std::shared_ptr<DataSetGenerator> const & generator)
: SCP(association), _generator(nullptr)
{
    this->set_generator(generator);
}

MoveSCP
::~MoveSCP()
{
    // Nothing to do.
}

MoveSCP::DataSetGenerator const &
MoveSCP
::get_generator() const
{
    return *this->_generator;
}

void
MoveSCP
::set_generator(std::shared_ptr<DataSetGenerator> const & generator)
{
    this->_generator = generator;
}

void
MoveSCP
::operator()(message::Message const & message)
{
    message::CMoveRequest const request(message);

    auto move_association = this->_generator->get_association(request);
    move_association.associate();
    StoreSCU store_scu(move_association);

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
            message::CMoveResponse response(
                request.get_message_id(), message::CMoveResponse::Pending);
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
                --remaining_sub_operations;
                ++failed_sub_operations;
            }

            this->_generator->next();
        }
    }
    catch(Exception const &)
    {
        message::CMoveResponse response(
            request.get_message_id(), message::CMoveResponse::UnableToProcess);
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

    message::CMoveResponse response(
        request.get_message_id(), message::CMoveResponse::Success);
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
