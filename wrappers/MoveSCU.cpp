/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/MoveSCU.h"

namespace
{

void 
move_with_python_callback(
    odil::MoveSCU const & scu, 
    odil::DataSet const & query, boost::python::object const & f)
{
    scu.move(
        query, 
        [f](odil::DataSet const & data_set) 
        { 
            boost::python::call<void>(f.ptr(), data_set); 
        }
    );
}

}

void wrap_MoveSCU()
{
    using namespace boost::python;
    using namespace odil;

    class_<MoveSCU>("MoveSCU", init<Association &>())
        .def(
            "get_move_destination",
            &MoveSCU::get_move_destination,
            return_value_policy<copy_const_reference>()
        )
        .def(
            "set_move_destination",
            &MoveSCU::set_move_destination
        )
        .def(
            "get_incoming_port",
            &MoveSCU::get_incoming_port
        )
        .def(
            "set_incoming_port",
            &MoveSCU::set_incoming_port
        )
        .def(
            "move",
            &move_with_python_callback
        )
        .def(
            "move", 
            static_cast<
                std::vector<DataSet> (MoveSCU::*)(DataSet const &) const
            >(&MoveSCU::move)
        )
        .def("set_affected_sop_class", &MoveSCU::set_affected_sop_class)
    ;
}
