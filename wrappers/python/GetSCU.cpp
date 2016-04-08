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
    odil::DataSet const & query, boost::python::object const & f)
{
    scu.get(
        query, 
        [f](odil::DataSet const & data_set) 
        { 
            boost::python::call<void>(f.ptr(), data_set); 
        }
    );
}

}

void wrap_GetSCU()
{
    using namespace boost::python;
    using namespace odil;

    class_<GetSCU>("GetSCU", init<Association &>())
        .def(
            "get",
            &get_with_python_callback
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
