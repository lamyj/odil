/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/GetSCU.h"

#include "opaque_types.h"
#include "type_casters.h"

namespace
{

void 
get_with_python_callback(
    odil::GetSCU const & scu, 
    std::shared_ptr<odil::DataSet> query,
    pybind11::object const & store_callback,
    pybind11::object const & get_callback)
{
    odil::GetSCU::StoreCallback store_callback_cpp;
    if(!store_callback.is_none())
    {
        store_callback_cpp = [store_callback](std::shared_ptr<odil::DataSet> data_set)
        {
            store_callback(data_set);
        };
    }

    odil::GetSCU::GetCallback get_callback_cpp;
    if(!get_callback.is_none())
    {
        get_callback_cpp = [get_callback](std::shared_ptr<odil::message::CGetResponse> message)
        {
            get_callback(message);
        };
    }

    scu.get(query, store_callback_cpp, get_callback_cpp);
}

}

void wrap_GetSCU(pybind11::module & m)
{
    using namespace pybind11;
    using namespace pybind11::literals;
    using namespace odil;

    class_<GetSCU>(m, "GetSCU")
        .def(init<Association &>())
        .def(
            // FIXME
            "get", &get_with_python_callback,
            "Perform the C-GET using callbacks",
            "query"_a, "store_callback"_a, "get_callback"_a=none())
        .def(
            "get", 
            static_cast<
                Value::DataSets (GetSCU::*)(std::shared_ptr<DataSet>) const
            >(&GetSCU::get)
        )
        .def("set_affected_sop_class", &GetSCU::set_affected_sop_class)
    ;
}
