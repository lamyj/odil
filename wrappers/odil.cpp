/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/Tag.h"
#include "odil/uid.h"

BOOST_PYTHON_MODULE(_odil)
{
    using namespace boost::python;
    using namespace odil;

    scope().attr("uid_prefix") = uid_prefix;
    scope().attr("implementation_class_uid") = implementation_class_uid;
    scope().attr("implementation_version_name") = implementation_version_name;
    def("generate_uid", generate_uid);

    class_<Tag>("Tag", init<uint16_t, uint16_t>())
        .def(init<uint32_t>())
        .def(init<std::string>())
        .def_readwrite("group", &Tag::group)
        .def_readwrite("element", &Tag::element)
        .def("is_private", &Tag::is_private)
        .def("get_name", &Tag::get_name)
        .def("__eq__", &Tag::operator==)
        .def("__ne__", &Tag::operator!=)
        .def("__lt__", &Tag::operator<)
        .def("__gt__", &Tag::operator>)
        .def("__le__", &Tag::operator<=)
        .def("__ge__", &Tag::operator>=)
        .def("__str__", &Tag::operator std::string)
    ;
}
