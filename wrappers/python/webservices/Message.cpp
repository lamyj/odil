/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/python.hpp>

#include "odil/webservices/Message.h"

void wrap_webservices_Message()
{
    using namespace boost::python;
    using namespace odil::webservices;

    class_<Message>(
        "Message",
        init<Message::Headers, std::string>((
            arg("headers")=Message::Headers(), arg("body")=""
        )))
        .def(
            "get_headers", &Message::get_headers,
            return_value_policy<copy_const_reference>())
        .def("set_headers", &Message::set_headers)
        .def("has_header", &Message::has_header)
        .def(
            "get_header", &Message::get_header,
            return_value_policy<copy_const_reference>())
        .def("set_header", &Message::set_header)
        .def(
            "get_body", &Message::get_body,
            return_value_policy<copy_const_reference>())
        .def("set_body", &Message::set_body)
    ;
}
