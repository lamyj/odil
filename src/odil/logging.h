/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _5382f5e0_e993_4966_9447_542844edb635
#define _5382f5e0_e993_4966_9447_542844edb635

#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>

#include "odil/odil.h"

#define ODIL_LOG(level) \
    BOOST_LOG_SEV(odil::logging::logger, boost::log::trivial::level)

namespace odil
{
namespace logging
{

extern ODIL_API boost::log::sources::severity_logger<int> logger;

}

}

#endif // _5382f5e0_e993_4966_9447_542844edb635
