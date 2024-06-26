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

#include "Value.h"

void wrap_Element(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    using namespace odil::wrappers;

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
            init([](sequence & source, VR vr) {
                return convert_sequence<Element>(source, vr);
            }),
            "source"_a, "vr"_a=VR::INVALID)
        .def("empty", &Element::empty)
        .def("size", &Element::size)
        .def(
            "get_value", (Value const & (Element::*)() const) &Element::get_value,
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
        .def(
            "__getitem__", [](Element const & self, pybind11::ssize_t index) {
                if(index < 0)
                {
                    index += self.size();
                }
                
                if(index >= self.size())
                {
                    throw std::out_of_range("list index out of range");
                }
                
                return apply_visitor(GetItem(index), self.get_value());
            })
        .def(
            "__getitem__", [](Element const & self, slice slice_) {
                return apply_visitor(
                    GetSlice(self.size(), slice_), self.get_value());
            })
        .def(
            "__setitem__", [](Element & self, pybind11::ssize_t index, object item) {
                if(index < 0)
                {
                    index += self.size();
                }
                
                if(index >= self.size())
                {
                    throw std::out_of_range("list index out of range");
                }
                
                return apply_visitor(SetItem(index, item), self.get_value());
            })
        .def(
            "__iter__", 
            [](Element const & self) 
            { 
                return apply_visitor(Iterate(), self.get_value());
            })
        .def(
            "append", [](Element & self, object item) {
                return apply_visitor(Append(item), self.get_value());
            })
        .def(pickle(
            [](Element const & element) {
                return make_tuple(element.get_value(), element.vr);
            },
            [](tuple pickled) {
                auto const vr = pickled[1].cast<VR>();
                if(len(pickled[0]) == 0)
                {
                    return Element(vr);
                }
                else
                {
                    auto const value = pickled[0].cast<Value>();
                    return Element(value, vr);
                }
            }
        ))
    ;
}
