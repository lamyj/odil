/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <functional>
#include <pybind11/pybind11.h>
#include "odil/StoreSCP.h"

namespace
{
using namespace std;
void
set_callback(odil::StoreSCP& scp, pybind11::object const& f)
{
    scp.set_callback(
        [f](std::shared_ptr<odil::message::CStoreRequest> message)
        {
            auto result = f(message);
            return result.cast<odil::Value::Integer>();
        });
}

}

void wrap_StoreSCP(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    class_<StoreSCP>(m, "StoreSCP")
    .def(init<Association&>())
    .def(init<Association&, StoreSCP::Callback&>())
    .def("set_callback", &set_callback)
    .def(
        "__call__",
        static_cast<
            void (StoreSCP::*)(std::shared_ptr<message::Message>)
        >(&StoreSCP::operator()))
    ;

}
