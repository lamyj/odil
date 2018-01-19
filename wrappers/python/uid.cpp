/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/python.hpp>

#include "odil/uid.h"

void wrap_uid()
{
    using namespace boost::python;
    using namespace odil;

    scope().attr("uid_prefix") = uid_prefix;
    scope().attr("implementation_class_uid") = implementation_class_uid;
    scope().attr("implementation_version_name") = implementation_version_name;
    def("generate_uid", generate_uid);
}
