/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/VRFinder.h"

#include "opaque_types.h"
#include "type_casters.h"

void wrap_VRFinder(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    
    class_<VRFinder>(m, "VRFinder")
        .def(init<>())
        .def("__call__", &VRFinder::operator())
    ;
}
