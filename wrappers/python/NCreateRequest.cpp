/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/message/NCreateRequest.h"

void wrap_NCreateRequest(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    using namespace odil::message;

    class_<NCreateRequest, std::shared_ptr<NCreateRequest>, Request>(m, "NCreateRequest")
        .def(init<
                Value::Integer, Value::String const &,
                std::shared_ptr<DataSet>
            >())
        .def(init<std::shared_ptr<Message>>())
        .def(
            "get_affected_sop_class_uid",
            &NCreateRequest::get_affected_sop_class_uid,
            return_value_policy::copy)
        .def(
            "set_affected_sop_class_uid",
            &NCreateRequest::set_affected_sop_class_uid)
        .def(
            "get_affected_sop_instance_uid",
            &NCreateRequest::get_affected_sop_instance_uid,
            return_value_policy::copy)
        .def(
            "set_affected_sop_instance_uid",
            &NCreateRequest::set_affected_sop_instance_uid)
        .def(
            "get_command_field",
            &NCreateRequest::get_command_field,
            return_value_policy::copy)
        .def(
            "set_command_field",
            &NCreateRequest::set_command_field)
        .def("has_attribute_list",
             &NCreateRequest::has_attribute_list)
        .def(
            "get_attribute_list",
            &NCreateRequest::get_attribute_list,
            return_value_policy::copy)
        .def(
            "set_attribute_field",
            &NCreateRequest::set_attribute_list)

    ;
}
