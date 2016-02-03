/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/DataSet.h"
#include "odil/Element.h"
#include "odil/Value.h"

void wrap_Element()
{
    using namespace boost::python;
    using namespace odil;

    typedef Value::Integers & (Element::*AsIntegers)();
    typedef Value::Reals & (Element::*AsReals)();
    typedef Value::Strings & (Element::*AsStrings)();
    typedef Value::DataSets & (Element::*AsDataSets)();
    typedef Value::Binary & (Element::*AsBinary)();

    class_<Element>("Element", init<>())
        .def_readwrite("vr", &Element::vr)
        .def(init<Value, optional<VR>>())
        .def(init<Value::Integers, optional<VR>>())
        .def(init<Value::Reals, optional<VR>>())
        .def(init<Value::Strings, optional<VR>>())
        .def(init<Value::DataSets, optional<VR>>())
        .def(init<Value::Binary, optional<VR>>())
        .def("empty", &Element::empty)
        .def("size", &Element::size)
        .def(
            "get_value", &Element::get_value, 
            return_value_policy<reference_existing_object>())
        .def("is_int", &Element::is_int)
        .def(
            "as_int", AsIntegers(&Element::as_int), 
            return_value_policy<reference_existing_object>())
        .def("is_real", &Element::is_real)
        .def(
            "as_real", AsReals(&Element::as_real), 
            return_value_policy<reference_existing_object>())
        .def("is_string", &Element::is_string)
        .def(
            "as_string", AsStrings(&Element::as_string), 
            return_value_policy<reference_existing_object>())
        .def("is_data_set", &Element::is_data_set)
        .def(
            "as_data_set", AsDataSets(&Element::as_data_set), 
            return_value_policy<reference_existing_object>())
        .def("is_binary", &Element::is_binary)
        .def(
            "as_binary", AsBinary(&Element::as_binary), 
            return_value_policy<reference_existing_object>())
        .def(self == self)
        .def(self != self)
        .def("__len__", &Element::size)
    ;
}
