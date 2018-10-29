/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/message/NSetRequest.h"

void wrap_NSetRequest(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    using namespace odil::message;

    class_<NSetRequest, std::shared_ptr<NSetRequest>, Request>(m, "NSetRequest")
        .def(init<
                Value::Integer, Value::String const &, Value::String const &,
                std::shared_ptr<DataSet>
            >())
        .def(init<std::shared_ptr<Message>>())
        .def(
            "get_requested_sop_class_uid",
            &NSetRequest::get_requested_sop_class_uid,
            return_value_policy::copy)
        .def(
            "set_requested_sop_class_uid",
            &NSetRequest::set_requested_sop_class_uid)
        .def(
            "get_requested_sop_instance_uid",
            &NSetRequest::get_requested_sop_instance_uid,
            return_value_policy::copy)
        .def(
            "set_requested_sop_instance_uid",
            &NSetRequest::set_requested_sop_instance_uid)
        .def("has_command_field",
             &NSetRequest::set_command_field)
        .def(
            "get_command_field",
            &NSetRequest::get_command_field,
            return_value_policy::copy)
        .def(
            "set_command_field",
            &NSetRequest::set_command_field)
    ;
}
