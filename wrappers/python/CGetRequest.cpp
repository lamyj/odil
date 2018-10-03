/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/message/CGetRequest.h"

void wrap_CGetRequest(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    using namespace odil::message;

    class_<CGetRequest, std::shared_ptr<CGetRequest>, Request>(m, "CGetRequest")
        .def(init<
                Value::Integer, Value::String const &, Value::Integer,
                std::shared_ptr<DataSet>
            >())
        .def(init<std::shared_ptr<Message>>())
        .def(
            "get_affected_sop_class_uid",
            &CGetRequest::get_affected_sop_class_uid,
            return_value_policy::copy)
        .def(
            "set_affected_sop_class_uid",
            &CGetRequest::set_affected_sop_class_uid)
        .def(
            "get_priority", &CGetRequest::get_priority,
            return_value_policy::copy)
        .def("set_priority", &CGetRequest::set_priority)
    ;
}
