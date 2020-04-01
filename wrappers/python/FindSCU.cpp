/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/FindSCU.h"

#include "opaque_types.h"
#include "type_casters.h"

namespace
{

void 
find_with_python_callback(
    odil::FindSCU const & scu, 
    std::shared_ptr<odil::DataSet> query, pybind11::object const & f)
{
    scu.find(
        query, 
        [f](std::shared_ptr<odil::DataSet> data_set)
        {
            f(data_set);
        }
    );
}

}

void wrap_FindSCU(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    class_<FindSCU>(m, "FindSCU")
        .def(init<Association &>())
        .def(
            "find",
            &find_with_python_callback
        )
        .def(
            "find", 
            static_cast<
                Value::DataSets (FindSCU::*)(std::shared_ptr<DataSet>) const
            >(&FindSCU::find)
        )
        .def("set_affected_sop_class", &FindSCU::set_affected_sop_class)
    ;
}
