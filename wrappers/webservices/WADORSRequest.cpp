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

namespace
{

std::string get_base_url(odil::webservices::WADORSRequest const & request)
{
    return std::string(request.get_base_url());
}

void set_base_url(
    odil::webservices::WADORSRequest & request, std::string const & base_url)
{
    request.set_base_url(odil::webservices::URL::parse(base_url));
}

std::string get_url(odil::webservices::WADORSRequest const & request)
{
    return std::string(request.get_url());
}

}

void wrap_webservices_WADORSRequest()
{
    using namespace boost::python;
    using namespace odil::webservices;

    scope wado_rs_request_scope = class_<WADORSRequest>(
            "WADORSRequest", init<HTTPRequest>())
        // TODO: full constructor
        .def("get_base_url", &get_base_url)
        .def("set_base_url", &set_base_url)
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
        .def("get_url", &get_url)
        .def(
            "get_media_type", &WADORSRequest::get_media_type,
            return_value_policy<copy_const_reference>())
        .def(
            "get_representation", &WADORSRequest::get_representation,
            return_value_policy<copy_const_reference>())
        // request_dicom
        // request_bulk_data
        // request_pixel_data
        .def("get_http_request", &WADORSRequest::get_http_request)
        .def(self == self)
        .def(self != self)
    ;

    // FIXME: frames
    class_<WADORSRequest::Selector>(
            "Selector", init<std::string, std::string, std::string>())
        .def_readwrite("study", &WADORSRequest::Selector::study)
        .def_readwrite("series", &WADORSRequest::Selector::series)
        .def_readwrite("instance", &WADORSRequest::Selector::instance)
        .def("get_path", &WADORSRequest::Selector::get_path)
        .def(self == self)
        .def(self != self)
    ;
}
