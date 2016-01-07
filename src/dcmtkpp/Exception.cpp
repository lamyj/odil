/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/Exception.h"

#include <stdexcept>
#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/ofcond.h>

namespace dcmtkpp
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

}
