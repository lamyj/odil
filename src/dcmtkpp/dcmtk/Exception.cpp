/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dcmtk/Exception.h"

#include <stdexcept>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/ofcond.h>

#include "odil/Exception.h"

namespace odil
{

namespace dcmtk
{

Exception
::Exception(std::string const & message)
: ::odil::Exception(message), _source(Source::Message), _condition()
{
    // Nothing else.
}

Exception
::Exception(OFCondition const & condition)
: ::odil::Exception(), _source(Source::Condition), _condition(condition)
{
    // Nothing else.
}

Exception
::~Exception() noexcept
{
    // Nothing to do.
}

char const *
Exception
::what() const throw()
{
    if(this->_source == Source::Message)
    {
        return this->_message.c_str();
    }
    else if(this->_source == Source::Condition)
    {
        return this->_condition.text();
    }
    else
    {
        throw std::runtime_error("Invalid source");
    }
}

Exception::Source
Exception
::get_source() const
{
    return this->_source;
}

OFCondition const &
Exception
::get_condition() const
{
    if(this->_source != Source::Condition)
    {
        throw Exception("Wrong source");
    }
    return this->_condition;
}

}

}
