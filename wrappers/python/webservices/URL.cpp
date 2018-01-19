/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/python.hpp>

#include "odil/webservices/URL.h"

namespace
{
boost::shared_ptr<odil::webservices::URL>
constructor(
    std::string const & scheme="", std::string const & authority="",
    std::string const & path="", std::string const & query="",
    std::string const & fragment="")
{
    // Old versions of Boost.Python (Debian 7, Ubuntu 12.04) do not like
    // std::shared_ptr
    boost::shared_ptr<odil::webservices::URL> url(new odil::webservices::URL());
    url->scheme = scheme;
    url->authority = authority;
    url->path = path;
    url->query = query;
    url->fragment = fragment;

    return url;
}

}
void wrap_webservices_URL()
{
    using namespace boost::python;
    using namespace odil::webservices;

    class_<URL>("URL", no_init)
        .def(
            "__init__",
            make_constructor(constructor, default_call_policies(),
            (
                arg("scheme")="", arg("authority")="", arg("path")="",
                arg("query")="", arg("fragment")="")))
        .def_readwrite("scheme", &URL::scheme)
        .def_readwrite("authority", &URL::authority)
        .def_readwrite("path", &URL::path)
        .def_readwrite("query", &URL::query)
        .def_readwrite("fragment", &URL::fragment)
        .def("__str__", &URL::operator std::string)
        .def("parse", &URL::parse)
        .def(self == self)
        .def(self != self)
        .staticmethod("parse")
    ;
}
