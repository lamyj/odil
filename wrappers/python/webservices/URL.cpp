/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "odil/webservices/URL.h"

namespace
{

odil::webservices::URL
constructor(
    std::string const & scheme="", std::string const & authority="",
    std::string const & path="", std::string const & query="",
    std::string const & fragment="")
{
    odil::webservices::URL url;
    url.scheme = scheme;
    url.authority = authority;
    url.path = path;
    url.query = query;
    url.fragment = fragment;

    return url;
}

}

void wrap_webservices_URL(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil::webservices;

    class_<URL>(m, "URL")
        .def(
            init(&constructor), "",
            arg("scheme")="", arg("authority")="", arg("path")="",
            arg("query")="", arg("fragment")="")
        .def_readwrite("scheme", &URL::scheme)
        .def_readwrite("authority", &URL::authority)
        .def_readwrite("path", &URL::path)
        .def_readwrite("query", &URL::query)
        .def_readwrite("fragment", &URL::fragment)
        .def("__str__", &URL::operator std::string)
        .def(self == self)
        .def(self != self)
        .def_static("parse", &URL::parse)
    ;
}
