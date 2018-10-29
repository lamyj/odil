/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "odil/Element.h"
#include "odil/VR.h"

#include "opaque_types.h"
#include "type_casters.h"

void wrap_Element(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    class_<Element>(m, "Element")
        // WARNING: the VR is not handled correctly
        //.def_readwrite("vr", &Element::vr)
        .def_property(
            "vr",
            [](Element const & e) { return e.vr; },
            [](Element & e, VR v) { e.vr = v; })
        .def(init<VR>())
        .def(init<Value const &, VR>())
        .def(
            init([](iterable & source, VR vr) {
                return convert_iterable<Element>(source, vr);
            }),
            "source"_a, "vr"_a=VR::INVALID)
        .def("empty", &Element::empty)
        .def("size", &Element::size)
        .def(
            "get_value", &Element::get_value,
            return_value_policy::reference_internal)
        .def("is_int", &Element::is_int)
        .def(
            "as_int", (Value::Integers & (Element::*)()) &Element::as_int,
            return_value_policy::reference_internal)
        .def("is_real", &Element::is_real)
        .def(
            "as_real", (Value::Reals & (Element::*)()) &Element::as_real,
            return_value_policy::reference_internal)
        .def("is_string", &Element::is_string)
        .def(
            "as_string", (Value::Strings & (Element::*)()) &Element::as_string,
            return_value_policy::reference_internal)
        .def("is_data_set", &Element::is_data_set)
        .def(
            "as_data_set", (Value::DataSets & (Element::*)()) &Element::as_data_set,
            return_value_policy::reference_internal)
        .def("is_binary", &Element::is_binary)
        .def(
            "as_binary", (Value::Binary & (Element::*)()) &Element::as_binary,
            return_value_policy::reference_internal)
        .def(self == self)
        .def(self != self)
        .def("__len__", &Element::size)
        .def("clear", &Element::clear)
    ;
}
