/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/python.hpp>

#include "odil/message/CMoveResponse.h"
#include "odil/MoveSCU.h"

namespace
{

void
move_with_python_callback(
    odil::MoveSCU const & scu,
    std::shared_ptr<odil::DataSet> query,
    boost::python::object const & store_callback,
    boost::python::object const & move_callback)
{
    odil::MoveSCU::StoreCallback store_callback_cpp;
    if(!store_callback.is_none())
    {
        store_callback_cpp = [store_callback](std::shared_ptr<odil::DataSet> data_set)
        {
            boost::python::call<void>(store_callback.ptr(), data_set);
        };
    }

    odil::MoveSCU::MoveCallback move_callback_cpp;
    if(!move_callback.is_none())
    {
        move_callback_cpp = [move_callback](std::shared_ptr<odil::message::CMoveResponse> message)
        {
            boost::python::call<void>(move_callback.ptr(), message);
        };
    }

    scu.move(query, store_callback_cpp, move_callback_cpp);
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
            &move_with_python_callback,
            (
                arg("scu"), arg("query"), arg("store_callback"),
                arg("move_callback")
            )
        )
        .def(
            "move",
            static_cast<
                Value::DataSets (MoveSCU::*)(std::shared_ptr<DataSet>) const
            >(&MoveSCU::move)
        )
        .def("set_affected_sop_class", &MoveSCU::set_affected_sop_class)
    ;
}
