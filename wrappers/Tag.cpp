/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/Tag.h"

uint32_t hash(odil::Tag const & tag)
{
    return ((tag.group<<16)+tag.element);
}

void wrap_Tag()
{
    using namespace boost::python;
    using namespace odil;

    class_<Tag>("Tag", init<uint16_t, uint16_t>())
        .def(init<uint32_t>())
        .def(init<std::string>())
        .def_readwrite("group", &Tag::group)
        .def_readwrite("element", &Tag::element)
        .def("is_private", &Tag::is_private)
        .def("get_name", &Tag::get_name)
        .def(self == self)
        .def(self != self)
        .def(self < self)
        .def(self > self)
        .def(self <= self)
        .def(self >= self)
        .def("__str__", &Tag::operator std::string)
        .def("__hash__", &hash)
    ;
    implicitly_convertible<std::string, Tag>();
}
