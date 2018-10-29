/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/message/CStoreRequest.h"

void wrap_CStoreRequest(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    using namespace odil::message;

    class_<CStoreRequest, std::shared_ptr<CStoreRequest>, Request>(m, "CStoreRequest")
        .def(init<
                Value::Integer, Value::String const &, Value::String const &,
                Value::Integer, std::shared_ptr<DataSet>
            >())
        .def(init<std::shared_ptr<Message>>())
        .def(
            "get_affected_sop_class_uid",
            &CStoreRequest::get_affected_sop_class_uid,
            return_value_policy::copy)
        .def(
            "set_affected_sop_class_uid",
            &CStoreRequest::set_affected_sop_class_uid)
        .def(
            "get_affected_sop_instance_uid",
            &CStoreRequest::get_affected_sop_instance_uid,
            return_value_policy::copy)
        .def(
            "set_affected_sop_instance_uid",
            &CStoreRequest::set_affected_sop_instance_uid)
        .def(
            "get_priority", &CStoreRequest::get_priority,
            return_value_policy::copy)
        .def("set_priority", &CStoreRequest::set_priority)
        .def(
            "has_move_originator_ae_title",
            &CStoreRequest::has_move_originator_ae_title)
        .def(
            "get_move_originator_ae_title",
            &CStoreRequest::get_move_originator_ae_title,
            return_value_policy::copy)
        .def(
            "set_move_originator_ae_title",
            &CStoreRequest::set_move_originator_ae_title)
        .def(
            "has_move_originator_message_id",
            &CStoreRequest::has_move_originator_message_id)
        .def(
            "get_move_originator_message_id",
            &CStoreRequest::get_move_originator_message_id,
            return_value_policy::copy)
        .def(
            "set_move_originator_message_id",
            &CStoreRequest::set_move_originator_message_id)
    ;
}
