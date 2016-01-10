/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/Exception.h"

#include <stdexcept>
#include <string>

namespace odil
{

Exception
::Exception(std::string const & message)
: _message(message)
{
    // Nothing else.
}

Exception
::~Exception() throw()
{
    // Nothing to do.
}

char const *
Exception
::what() const throw()
{
    return this->_message.c_str();
}

}
