/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/logging.h"

#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>

#include "odil/odil.h"

namespace odil
{

namespace logging
{

bool configure()
{
    boost::log::core::get()->set_filter(
        boost::log::trivial::severity >= boost::log::trivial::warning);
    
    return true;

    
}

boost::log::sources::severity_logger<int> logger = {};

static bool const configured = configure();

}

}
