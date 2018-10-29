/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/message/CMoveResponse.h"
#include "odil/MoveSCU.h"

namespace
{

void
move_with_python_callback(
    odil::MoveSCU const & scu,
    std::shared_ptr<odil::DataSet> query,
    pybind11::object const & store_callback,
    pybind11::object const & move_callback)
{
    odil::MoveSCU::StoreCallback store_callback_cpp;
    if(!store_callback.is_none())
    {
        store_callback_cpp = [store_callback](std::shared_ptr<odil::DataSet> data_set)
        {
            store_callback(data_set);
        };
    }

    odil::MoveSCU::MoveCallback move_callback_cpp;
    if(!move_callback.is_none())
    {
        move_callback_cpp = [move_callback](std::shared_ptr<odil::message::CMoveResponse> message)
        {
            move_callback(message);
        };
    }

    scu.move(query, store_callback_cpp, move_callback_cpp);
}

}

void wrap_MoveSCU(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    class_<MoveSCU>(m, "MoveSCU")
        .def(init<Association &>())
        .def(
            "get_move_destination", &MoveSCU::get_move_destination,
            return_value_policy::copy)
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
        .def("move", &move_with_python_callback)
        .def(
            "move",
            static_cast<
                Value::DataSets (MoveSCU::*)(std::shared_ptr<DataSet>) const
            >(&MoveSCU::move)
        )
        .def("set_affected_sop_class", &MoveSCU::set_affected_sop_class)
    ;
}
