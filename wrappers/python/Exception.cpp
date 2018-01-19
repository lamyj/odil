/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/python.hpp>

#include "odil/Exception.h"

#include "exception_factory.h"

namespace
{

PyObject * wrapped_Exception;

void translator(odil::Exception const & e)
{
    PyErr_SetString(wrapped_Exception, e.what());
}

}

void wrap_Exception()
{
    wrapped_Exception = exception_factory("Exception");
    boost::python::register_exception_translator<odil::Exception>(translator);
}
