/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/NSetSCP.h"

namespace
{

void
set_callback(odil::NSetSCP& scp, pybind11::object const& f)
{
    scp.set_callback(
        [f](std::shared_ptr<odil::message::NSetRequest const> message)
        {
            return f(message).cast<odil::Value::Integer>();
        });
}

}

void wrap_NSetSCP(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    class_<NSetSCP>(m, "NSetSCP")
        .def(init<Association&>())
        .def (init<Association&, NSetSCP::Callback&>())
        .def("set_callback", &set_callback)
        .def(
            "__call__",
            static_cast<
                void (NSetSCP::*)(std::shared_ptr<message::Message>)
            >(&NSetSCP::operator())
        )
    ;
}
