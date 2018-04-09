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
#include "odil/logging.h"
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

std::shared_ptr<MoveSCP::DataSetGenerator const>
MoveSCP
::get_generator() const
{
    return this->_generator;
}

void
MoveSCP
::set_generator(std::shared_ptr<DataSetGenerator> const & generator)
{
    this->_generator = generator;
}

void
MoveSCP
::operator()(std::shared_ptr<message::Message> message)
{
    auto request = std::make_shared<message::CMoveRequest const>(message);
    this->operator()(request);
}

void
MoveSCP
::operator()(std::shared_ptr<message::CMoveRequest const> request)
{
    Association move_association;
    try
    {
        move_association = this->_generator->get_association(request);
    }
    catch(odil::Exception const & e)
    {
        ODIL_LOG(ERROR) << "Cannot get move association: " << e.what();
        auto response = std::make_shared<message::CMoveResponse>(
            request->get_message_id(),
            message::CMoveResponse::RefusedMoveDestinationUnknown);
        this->_association.send_message(
            response, request->get_affected_sop_class_uid());
        return;
    }

    move_association.associate();
    StoreSCU store_scu(move_association);

    Value::Integer final_status = message::CMoveResponse::Success;
    std::shared_ptr<DataSet> status_fields;
    unsigned int remaining_sub_operations = 0;
    unsigned int completed_sub_operations=0;
    unsigned int failed_sub_operations=0;
    unsigned int warning_sub_operations=0;

    auto const & move_originator_aet =
        this->_association.get_negotiated_parameters().get_calling_ae_title();
    auto const & move_originator_message_id = request->get_message_id();

    try
    {
        this->_generator->initialize(request);
        remaining_sub_operations = this->_generator->count();

        while(!this->_generator->done())
        {
            auto response = std::make_shared<message::CMoveResponse>(
                request->get_message_id(), message::CMoveResponse::Pending);
            response->set_number_of_remaining_sub_operations(
                remaining_sub_operations);
            response->set_number_of_completed_sub_operations(
                completed_sub_operations);
            response->set_number_of_failed_sub_operations(
                failed_sub_operations);
            response->set_number_of_warning_sub_operations(
                warning_sub_operations);
            this->_association.send_message(
                response, request->get_affected_sop_class_uid());

            auto data_set = this->_generator->get();
            store_scu.set_affected_sop_class(data_set);
            try
            {
                store_scu.store(
                    data_set, move_originator_aet, move_originator_message_id);

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
    catch(SCP::Exception const & e)
    {
        final_status = e.status;
        status_fields = e.status_fields;
    }
    catch(odil::Exception const & e)
    {
        status_fields->add(registry::ErrorComment, {e.what()});
        final_status = message::CMoveResponse::UnableToProcess;
    }

    auto response = std::make_shared<message::CMoveResponse>(
        request->get_message_id(), final_status);
    response->set_status_fields(status_fields);
    response->set_number_of_remaining_sub_operations(remaining_sub_operations);
    response->set_number_of_completed_sub_operations(completed_sub_operations);
    response->set_number_of_failed_sub_operations(failed_sub_operations);
    response->set_number_of_warning_sub_operations(warning_sub_operations);
    this->_association.send_message(
        response, request->get_affected_sop_class_uid());
}

}
