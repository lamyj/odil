/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/webservices/HTTPRequest.h"
#include "odil/webservices/WADORSRequest.h"

void wrap_webservices_WADORSRequest()
{
    using namespace boost::python;
    using namespace odil::webservices;

    class_<WADORSRequest>(
        "WADORSRequest",
        init<URL, std::string, std::string, bool, bool>((
            arg("base_url")=URL(), arg("transfer_syntax")="",
            arg("character_set")="", arg("include_media_type_in_query")=false,
            arg("include_character_set_in_query")=false
        )))
        .def(init<HTTPRequest>())
        .def(
            "get_base_url", &WADORSRequest::get_base_url,
            return_value_policy<copy_const_reference>())
        .def("set_base_url", &WADORSRequest::set_base_url)
        .def(
            "get_transfer_syntax", &WADORSRequest::get_transfer_syntax,
            return_value_policy<copy_const_reference>())
        .def("set_transfer_syntax", &WADORSRequest::set_transfer_syntax)
        .def(
            "get_character_set", &WADORSRequest::get_character_set,
            return_value_policy<copy_const_reference>())
        .def("set_character_set", &WADORSRequest::set_character_set)
        .def(
            "get_include_media_type_in_query",
            &WADORSRequest::get_include_media_type_in_query)
        .def(
            "set_include_media_type_in_query",
            &WADORSRequest::set_include_media_type_in_query)
        .def(
            "get_include_character_set_in_query",
            &WADORSRequest::get_include_character_set_in_query)
        .def(
            "set_include_character_set_in_query",
            &WADORSRequest::set_include_character_set_in_query)
        .def("get_type", &WADORSRequest::get_type)
        .def(
            "get_selector", &WADORSRequest::get_selector,
            return_value_policy<copy_const_reference>())
        .def(
            "get_url", &WADORSRequest::get_url,
            return_value_policy<copy_const_reference>())
        .def(
            "get_media_type", &WADORSRequest::get_media_type,
            return_value_policy<copy_const_reference>())
        .def(
            "get_representation", &WADORSRequest::get_representation,
            return_value_policy<copy_const_reference>())
        .def("request_dicom", &WADORSRequest::request_dicom)
        .def(
            "request_bulk_data",
            static_cast<void(WADORSRequest::*)(odil::webservices::Selector const &)>(
                &WADORSRequest::request_bulk_data))
        .def(
            "request_bulk_data",
            static_cast<void(WADORSRequest::*)(URL const &)>(
                &WADORSRequest::request_bulk_data))
        .def("request_pixel_data", &WADORSRequest::request_pixel_data)
        .def("get_http_request", &WADORSRequest::get_http_request)
        .def(self == self)
        .def(self != self)
    ;
}
