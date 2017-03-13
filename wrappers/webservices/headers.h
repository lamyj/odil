/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _e1d65654_be77_42ec_99e2_8691e3df99d0
#define _e1d65654_be77_42ec_99e2_8691e3df99d0

#include <boost/python.hpp>

#include "odil/webservices/Message.h"

boost::python::dict
convert_headers(odil::webservices::Message::Headers const & headers);

odil::webservices::Message::Headers
convert_headers(boost::python::dict const & headers);

#endif // _e1d65654_be77_42ec_99e2_8691e3df99d0
