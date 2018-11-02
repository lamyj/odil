/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include <odil/uid.h>

#include "opaque_types.h"
#include "type_casters.h"

void wrap_uid(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    m.attr("uid_prefix") = uid_prefix;
    m.attr("implementation_class_uid") = implementation_class_uid;
    m.attr("implementation_version_name") = implementation_version_name;
    m.def("generate_uid", generate_uid);
}
