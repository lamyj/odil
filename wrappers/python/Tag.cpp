/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "odil/Tag.h"

#include "opaque_types.h"
#include "type_casters.h"

void wrap_Tag(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    class_<Tag>(m, "Tag")
        .def(init<uint16_t, uint16_t>())
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
        .def_property_readonly("name", &Tag::get_name)
        .def("__hash__", [](Tag const & x) { return (x.group<<16)+x.element; })
        .def(pickle(
            [](Tag const & t) {
                return make_tuple(t.group, t.element);
            },
            [](tuple t) {
                if (t.size() != 2)
                {
                    throw std::runtime_error("Invalid state");
                }
                return Tag(t[0].cast<uint16_t>(), t[1].cast<uint16_t>());
            }
        ))
    ;
    implicitly_convertible<std::string, Tag>();
}
