/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/GetSCU.h"

namespace
{

void 
get_with_python_callback(
    odil::GetSCU const & scu, 
    odil::DataSet const & query,
    boost::python::object const & store_callback,
    boost::python::object const & get_callback)
{
    odil::GetSCU::StoreCallback store_callback_cpp;
    if(!store_callback.is_none())
    {
        store_callback_cpp = [store_callback](odil::DataSet const & data_set)
        {
            boost::python::call<void>(store_callback.ptr(), data_set);
        };
    }

    odil::GetSCU::GetCallback get_callback_cpp;
    if(!get_callback.is_none())
    {
        get_callback_cpp = [get_callback](odil::message::CGetResponse const & message)
        {
            boost::python::call<void>(get_callback.ptr(), message);
        };
    }

    scu.get(query, store_callback_cpp, get_callback_cpp);
}

}

void wrap_GetSCU()
{
    using namespace boost::python;
    using namespace odil;

    class_<GetSCU>("GetSCU", init<Association &>())
        .def(
            "get",
            &get_with_python_callback,
            (
                arg("scu"), arg("query"), arg("store_callback"),
                arg("get_callback")=object()
            )
        )
        .def(
            "get", 
            static_cast<
                std::vector<DataSet> (GetSCU::*)(DataSet const &) const
            >(&GetSCU::get)
        )
        .def("set_affected_sop_class", &GetSCU::set_affected_sop_class)
    ;
}
