/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/webservices/HTTPResponse.h"

#include "headers.h"

namespace
{

boost::shared_ptr<odil::webservices::HTTPResponse>
constructor(
    std::string const & http_version="", unsigned int status=0,
    std::string const & reason="",
    boost::python::dict const & headers=boost::python::dict(),
    std::string const & body=std::string())
{
    using namespace odil::webservices;

    // Old versions of Boost.Python (Debian 7, Ubuntu 12.04) do not like
    // std::shared_ptr
    auto response = new HTTPResponse(
        http_version, status, reason, convert_headers(headers), body);
    return boost::shared_ptr<HTTPResponse>(response);
}

}

void wrap_webservices_HTTPResponse()
{
    using namespace boost::python;
    using namespace odil::webservices;

    class_<HTTPResponse, bases<Message>>("HTTPResponse", no_init)
        .def(
            "__init__",
            make_constructor(
                constructor, default_call_policies(),
                (
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
