/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/message/CStoreResponse.h"

void wrap_CStoreResponse(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    using namespace odil::message;

    class_<CStoreResponse, Response>(m, "CStoreResponse")
            .def(init< Value::Integer, Value::Integer>())
            .def(init<std::shared_ptr<Message>>())
            .def(
                "has_message_id",
                &CStoreResponse::has_message_id)
            .def(
                "get_message_id",
                &CStoreResponse::get_message_id,
                return_value_policy::copy)
            .def(
                "set_message_id",
                &CStoreResponse::set_message_id)
            .def(
                "has_affected_sop_class_uid",
                &CStoreResponse::has_affected_sop_class_uid)
            .def(
                "get_affected_sop_class_uid",
                &CStoreResponse::get_affected_sop_class_uid,
                return_value_policy::copy)
            .def(
                "set_affected_sop_class_uid",
                &CStoreResponse::set_affected_sop_class_uid)
            .def(
                "has_affected_sop_instance_uid",
                &CStoreResponse::has_affected_sop_instance_uid)
            .def(
                "get_affected_sop_instance_uid",
                &CStoreResponse::get_affected_sop_instance_uid,
                return_value_policy::copy)
            .def(
                "set_affected_sop_instance_uid",
                &CStoreResponse::set_affected_sop_instance_uid)
            ;
}
