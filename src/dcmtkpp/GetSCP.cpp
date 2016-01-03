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
    std::shared_ptr<ResponseGenerator> const & generator)
: SCP(association), _generator(nullptr)
{
    this->set_generator(generator);
}

GetSCP
::~GetSCP()
{
    // Nothing to do.
}

SCP::ResponseGenerator const &
GetSCP
::get_generator() const
{
    return *this->_generator;
}

void
GetSCP
::set_generator(std::shared_ptr<ResponseGenerator> const & generator)
{
    this->_generator = generator;
}

void
GetSCP
::operator()(message::Message const & message)
{
    message::CGetRequest const request(message);

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
        message::CGetResponse response(
            request.get_message_id(), message::CGetResponse::UnableToProcess);
        this->_association.send_message(
            response, request.get_affected_sop_class_uid());
        return;
    }
}

}
