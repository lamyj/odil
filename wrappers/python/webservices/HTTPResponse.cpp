/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/python.hpp>

#include "odil/webservices/HTTPResponse.h"

void wrap_webservices_HTTPResponse()
{
    using namespace boost::python;
    using namespace odil::webservices;

    class_<HTTPResponse, bases<Message>>(
        "HTTPResponse",
        init<std::string, int, std::string, Message::Headers, std::string>((
            arg("http_version")="", arg("status")=0, arg("reason")="",
            arg("headers")=dict(), arg("body")=std::string())))
        .def(
            "get_http_version", &HTTPResponse::get_http_version,
            return_value_policy<copy_const_reference>())
        .def("set_http_version", &HTTPResponse::set_http_version)
        .def("get_status", &HTTPResponse::get_status)
        .def("set_status", &HTTPResponse::set_status)
        .def(
            "get_reason", &HTTPResponse::get_reason,
            return_value_policy<copy_const_reference>())
        .def("set_reason", &HTTPResponse::set_reason)

    ;
}
