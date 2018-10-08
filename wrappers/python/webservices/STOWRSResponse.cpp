/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "odil/webservices/STOWRSResponse.h"

void
wrap_webservices_STOWRSResponse(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil::webservices;


    class_<STOWRSResponse>(m, "STOWRSResponse")
        .def(init())
        .def(init<HTTPResponse>())
        .def(self == self)
        .def(self != self)
        .def(
            "set_store_instance_responses",
            &STOWRSResponse::set_store_instance_responses)
        .def(
            "get_store_instance_responses",
            &STOWRSResponse::get_store_instance_responses)
        .def("get_media_type", &STOWRSResponse::get_media_type)
        .def("set_representation", &STOWRSResponse::set_representation)
        .def("get_representation", &STOWRSResponse::get_representation)
        .def("set_warning", &STOWRSResponse::set_warning)
        .def("is_status_warning", &STOWRSResponse::is_status_warning)
        .def("set_failure_code", &STOWRSResponse::set_failure_code)
        .def("get_failure_code", &STOWRSResponse::get_failure_code)
        .def("set_reason", &STOWRSResponse::set_reason)
        .def("get_reason", &STOWRSResponse::get_reason)
        .def("get_http_response", &STOWRSResponse::get_http_response)
        ;
}
