/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "odil/webservices/QIDORSRequest.h"
#include "odil/webservices/HTTPRequest.h"
#include "odil/webservices/Utils.h"


void wrap_webservices_QIDORSRequest(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil::webservices;

    class_<QIDORSRequest>(m, "QIDORSRequest")
        .def(init<URL>())
        .def(init<HTTPRequest>())
        .def("get_base_url", &QIDORSRequest::get_base_url)
        .def("set_base_url", &QIDORSRequest::set_base_url)
        .def("get_media_type", &QIDORSRequest::get_media_type)
        .def("get_representation", &QIDORSRequest::get_representation)
        .def("get_url", &QIDORSRequest::get_url)
        .def("get_selector", &QIDORSRequest::get_selector)
        .def("get_query_data_set", &QIDORSRequest::get_query_data_set)
        .def("get_fuzzymatching", &QIDORSRequest::get_fuzzymatching)
        .def("get_limit", &QIDORSRequest::get_limit)
        .def("get_offset", &QIDORSRequest::get_offset)
        .def("get_http_request", &QIDORSRequest::get_http_request)
        .def(
            "request_datasets", &QIDORSRequest::request_datasets,
            "",
            arg("representation"), arg("selector"), arg("data_sets"),
            arg("fuzzymatching") = false, arg("limit") = -1, arg("offset") = 0,
            arg("numerical_tags") = false)
        .def(self == self)
        .def(self != self)
    ;
}
