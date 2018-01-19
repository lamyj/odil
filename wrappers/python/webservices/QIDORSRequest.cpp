/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "odil/webservices/QIDORSRequest.h"
#include "odil/webservices/HTTPRequest.h"
#include "odil/webservices/Utils.h"


void wrap_webservices_QIDORSRequest()
{
    using namespace boost::python;
    using namespace odil::webservices;

    class_<QIDORSRequest>(
        "QIDORSRequest", no_init)
        .def(init<URL>())
        .def(init<HTTPRequest>())
        .def(
            "get_base_url", &QIDORSRequest::get_base_url,
            return_value_policy<copy_const_reference>())
        .def(
            "set_base_url", &QIDORSRequest::set_base_url)
        .def(
            "get_media_type", &QIDORSRequest::get_media_type,
            return_value_policy<copy_const_reference>())
        .def(
            "get_representation", &QIDORSRequest::get_representation,
            return_value_policy<copy_const_reference>())
        .def(
            "get_url", &QIDORSRequest::get_url,
            return_value_policy<copy_const_reference>())
        .def(
            "get_selector", &QIDORSRequest::get_selector,
            return_value_policy<copy_const_reference>())
        .def(
            "get_query_data_set", &QIDORSRequest::get_query_data_set,
            return_value_policy<copy_const_reference>())
        .def(
            "get_fuzzymatching", &QIDORSRequest::get_fuzzymatching)
        .def(
            "get_limit", &QIDORSRequest::get_limit)
        .def(
            "get_offset", &QIDORSRequest::get_offset)
        .def(
            "get_http_request", &QIDORSRequest::get_http_request)
        .def(
            "request_datasets", &QIDORSRequest::request_datasets,
                (arg("representation"),
                 arg("selector"),
                 arg("data_sets"),
                 arg("fuzzymatching") = false,
                 arg("limit") = -1,
                 arg("offset") = 0,
                 arg("numerical_tags") = false
            ))
        .def(self == self)
        .def(self != self)
    ;
}
