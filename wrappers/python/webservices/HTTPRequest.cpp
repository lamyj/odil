/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "odil/webservices/HTTPRequest.h"

void wrap_webservices_HTTPRequest(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil::webservices;

    class_<HTTPRequest, Message>(m, "HTTPRequest")
        .def(
            init<std::string, URL, std::string, Message::Headers, std::string>(),
            "",
            arg("method")="", arg("target")=URL(),
            arg("http_version")="HTTP/1.0", arg("headers")=Message::Headers(),
            arg("body")="")
        .def("get_method", &HTTPRequest::get_method, return_value_policy::copy)
        .def("set_method", &HTTPRequest::set_method)
        .def( "get_target", &HTTPRequest::get_target, return_value_policy::copy)
        .def("set_target", &HTTPRequest::set_target)
        .def(
            "get_http_version", &HTTPRequest::get_http_version,
            return_value_policy::copy)
        .def("set_http_version", &HTTPRequest::set_http_version)
    ;
}
