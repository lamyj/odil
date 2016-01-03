/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/FindSCP.h"

#include <memory>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/SCP.h"
#include "dcmtkpp/message/CFindRequest.h"
#include "dcmtkpp/message/CFindResponse.h"
#include "dcmtkpp/message/Response.h"

namespace dcmtkpp
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
    std::shared_ptr<ResponseGenerator> const & generator)
: SCP(association), _generator(nullptr)
{
    this->set_generator(generator);
}

FindSCP
::~FindSCP()
{
    // Nothing to do.
}

SCP::ResponseGenerator const &
FindSCP
::get_generator() const
{
    return *this->_generator;
}

void
FindSCP
::set_generator(std::shared_ptr<ResponseGenerator> const & generator)
{
    this->_generator = generator;
}

void
FindSCP
::operator()(message::Message const & message)
{
    message::CFindRequest const request(message);

    try
    {
        this->_generator->initialize(request);
        while(!this->_generator->done())
        {
            auto const message = this->_generator->get();
            this->_association.send_message(
                message, request.get_affected_sop_class_uid());
            this->_generator->next();
        }
    }
    catch(Exception const & e)
    {
        message::CFindResponse response(
            request.get_message_id(), message::CFindResponse::UnableToProcess);
        this->_association.send_message(
            response, request.get_affected_sop_class_uid());
        return;
    }

    message::CFindResponse response(
        request.get_message_id(), message::CFindResponse::Success);
    this->_association.send_message(
        response, request.get_affected_sop_class_uid());
}

}
