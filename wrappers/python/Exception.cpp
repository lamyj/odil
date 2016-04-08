/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/Exception.h"

void translator(odil::Exception const & e)
{
    PyErr_SetString(PyExc_UserWarning, e.what());
}

void wrap_Exception()
{
    using namespace boost::python;
    using namespace odil;

    register_exception_translator<Exception>(translator);
}

