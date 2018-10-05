/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/NSetSCU.h"


void wrap_NSetSCU(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    class_<NSetSCU>(m, "NSetSCU")
        .def(init<Association &>())
        .def(
            "get_affected_sop_class", &NSetSCU::get_affected_sop_class,
            return_value_policy::copy)
        .def(
            "set_affected_sop_class",
            static_cast<void(NSetSCU::*)(std::shared_ptr<DataSet const>)>(
                &NSetSCU::set_affected_sop_class)
        )
        .def("set", &NSetSCU::set)
    ;
}
