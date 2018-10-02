/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/message/CEchoRequest.h"

void wrap_CEchoRequest(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    using namespace odil::message;

    class_<CEchoRequest, Request>(m, "CEchoRequest")
        .def(init<Value::Integer, Value::String const &>())
        .def(init<std::shared_ptr<Message const>>())
        .def(
            "get_affected_sop_class_uid",
            &CEchoRequest::get_affected_sop_class_uid,
            return_value_policy::copy)
        .def(
            "set_affected_sop_class_uid",
            &CEchoRequest::set_affected_sop_class_uid)
    ;
}
