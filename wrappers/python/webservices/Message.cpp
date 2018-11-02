/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "odil/webservices/Message.h"

void wrap_webservices_Message(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil::webservices;

    class_<Message>(m, "Message")
        .def(
            init<Message::Headers, std::string>(),
            "Constructor. By default, headers and body will be empty.",
            arg("headers")=Message::Headers(), arg("body")="")
        .def("get_headers", &Message::get_headers, return_value_policy::copy)
        .def("set_headers", &Message::set_headers)
        .def("has_header", &Message::has_header)
        .def("get_header", &Message::get_header, return_value_policy::copy)
        .def("set_header", &Message::set_header)
        .def("get_body", [](Message const & m) { return bytes(m.get_body()); })
        .def("set_body", &Message::set_body)
    ;
}
