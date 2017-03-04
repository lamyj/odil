/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/webservices/HTTPRequest.h"

#include "headers.h"

namespace
{

boost::shared_ptr<odil::webservices::HTTPRequest>
constructor(
    std::string const & method="", std::string const & target="",
    std::string const & http_version="HTTP/1.0",
    boost::python::dict const & headers=boost::python::dict(),
    std::string const & body=std::string())
{
    using namespace odil::webservices;

    // Old versions of Boost.Python (Debian 7, Ubuntu 12.04) do not like
    // std::shared_ptr
    auto request = new HTTPRequest(
        method, URL::parse(target), http_version,
        convert_headers(headers), body);
    return boost::shared_ptr<HTTPRequest>(request);
}

std::string get_target(odil::webservices::HTTPRequest const & request)
{
    return std::string(request.get_target());
}

void set_target(
    odil::webservices::HTTPRequest & request, std::string const & target)
{
    request.set_target(odil::webservices::URL::parse(target));
}

}

void wrap_webservices_HTTPRequest()
{
    using namespace boost::python;
    using namespace odil::webservices;

    class_<HTTPRequest, bases<Message>>("HTTPRequest", no_init)
        .def(
            "__init__",
            make_constructor(
                constructor, default_call_policies(),
                (
                    arg("method")=std::string(), arg("target")=std::string(),
                    arg("http_version")="HTTP/1.0",
                    arg("headers")=dict(), arg("body")=std::string())))
        .def(
            "get_method", &HTTPRequest::get_method,
            return_value_policy<copy_const_reference>())
        .def("set_method", &HTTPRequest::set_method)
        .def("get_target", &get_target)
        .def("set_target", &set_target)
        .def(
            "get_http_version", &HTTPRequest::get_http_version,
            return_value_policy<copy_const_reference>())
        .def("set_http_version", &HTTPRequest::set_http_version)
    ;
}
