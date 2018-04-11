/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include "odil/StoreSCP.h"

#include <boost/python.hpp>

#include <functional>

namespace
{
using namespace std;
void
set_callback(odil::StoreSCP& scp, boost::python::object const& f)
{
    scp.set_callback(
        [f](std::shared_ptr<odil::message::CStoreRequest> message)
        {
            return boost::python::call<odil::Value::Integer>(f.ptr(), message);
        }
        );
}

}

void wrap_StoreSCP()
{
    using namespace boost::python;
    using namespace std;
    using namespace odil;

    class_<StoreSCP>("StoreSCP", init<Association&>())
    .def(init<Association&, StoreSCP::Callback& >())
    .def("set_callback", &set_callback)
    .def(
        "__call__",
        static_cast<
            void (StoreSCP::*)(std::shared_ptr<message::Message>)
        >(&StoreSCP::operator())
    )
    ;

}
