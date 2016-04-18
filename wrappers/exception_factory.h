/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <string>
#include <boost/python.hpp>

/// @brief Create a new Python exception type, in the current scope.
PyObject * exception_factory(
    std::string const & name, PyObject * parent=PyExc_Exception);
