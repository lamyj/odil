/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/EchoSCU.h"

void wrap_EchoSCU(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    class_<EchoSCU>(m, "EchoSCU")
        .def(init<Association &>())
        .def(
            "get_affected_sop_class",
            &EchoSCU::get_affected_sop_class,
            return_value_policy::copy)
        .def("set_affected_sop_class", &EchoSCU::set_affected_sop_class)
        .def("echo", &EchoSCU::echo)
    ;
}
