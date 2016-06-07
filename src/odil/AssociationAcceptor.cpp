/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/AssociationAcceptor.h"

#include <functional>
#include <string>
#include <vector>

#include "odil/AssociationParameters.h"
#include "odil/Exception.h"

namespace odil
{

AssociationParameters
default_association_acceptor(AssociationParameters const & input)
{
    AssociationParameters output;

    output.set_called_ae_title(input.get_called_ae_title());
    output.set_calling_ae_title(input.get_calling_ae_title());

    std::vector<AssociationParameters::PresentationContext>
        presentation_contexts = input.get_presentation_contexts();
    for(auto & presentation_context: presentation_contexts)
    {
        presentation_context.transfer_syntaxes =
            { presentation_context.transfer_syntaxes[0] };
        presentation_context.result =
            AssociationParameters::PresentationContext::Result::Acceptance;
    }
    output.set_presentation_contexts(presentation_contexts);

    output.set_maximum_length(input.get_maximum_length());

    return output;
}

AssociationRejected
::AssociationRejected(
    unsigned char result, unsigned char source, unsigned char reason,
    std::string const & message)
: Exception(message)
{
    this->set_result(result);
    this->set_source(source);
    this->set_reason(reason);
}

unsigned char
AssociationRejected
::get_result() const
{
    return this->_result;
}

void
AssociationRejected
::set_result(unsigned char value)
{
    this->_result = value;
}

unsigned char
AssociationRejected
::get_source() const
{
    return this->_source;
}

void
AssociationRejected
::set_source(unsigned char value)
{
    this->_source = value;
}

unsigned char
AssociationRejected
::get_reason() const
{
    return this->_reason;
}

void
AssociationRejected
::set_reason(unsigned char value)
{
    this->_reason = value;
}

}
