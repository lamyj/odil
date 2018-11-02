/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <pybind11/pybind11.h>

#include "odil/Exception.h"

#include "opaque_types.h"
#include "type_casters.h"

void wrap_Exception(pybind11::module & m)
{
    pybind11::register_exception<odil::Exception>(m, "Exception");
}
