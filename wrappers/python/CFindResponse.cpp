/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/message/CFindResponse.h"

void wrap_CFindResponse(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    using namespace odil::message;

    class_<CFindResponse, std::shared_ptr<CFindResponse>, Response>(m, "CFindResponse")
        .def(init<Value::Integer,Value::Integer>())
        .def(init<Value::Integer,Value::Integer, std::shared_ptr<DataSet>>())
        .def(init<std::shared_ptr<Message>>())
        .def(
            "get_message_id", &CFindResponse::get_message_id,
            return_value_policy::copy)
        .def("set_message_id", &CFindResponse::set_message_id)
        .def(
            "get_affected_sop_class_uid",
            &CFindResponse::get_affected_sop_class_uid,
            return_value_policy::copy)
        .def(
            "set_affected_sop_class_uid",
            &CFindResponse::set_affected_sop_class_uid)
    ;
}
