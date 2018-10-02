/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/message/Request.h"

void wrap_Request(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    using namespace odil::message;

    class_<Request, Message>(m, "Request")
        .def(init<Value::Integer>())
        .def(init<std::shared_ptr<Message>>())
        .def(
            "get_message_id", &Request::get_message_id,
            return_value_policy::copy)
        .def("set_message_id", &Request::set_message_id)
    ;
}
