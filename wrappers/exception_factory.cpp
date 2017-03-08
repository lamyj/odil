/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "exception_factory.h"

#include <string>
#include <boost/python.hpp>

PyObject * exception_factory(std::string const & name, PyObject * parent)
{
    auto scope = boost::python::scope();
    std::string const scope_name = 
        boost::python::extract<std::string>(scope.attr("__name__"));
    auto const qualified_name = scope_name + "." + name;
    PyObject * wrapped_type = 
        PyErr_NewException(
            const_cast<char*>(qualified_name.c_str()), parent, NULL);
    scope.attr(name.c_str()) = 
        boost::python::handle<>(boost::python::borrowed(wrapped_type));
    return wrapped_type;
}
