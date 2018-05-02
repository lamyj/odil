/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <algorithm>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include "odil/DataSet.h"
#include "odil/Value.h"

#include "opaque_types.h"
#include "type_casters.h"

namespace
{

pybind11::object
as_memory_view(odil::Value::Binary::value_type const & binary_item)
{
    Py_buffer buffer;
    PyBuffer_FillInfo(
        &buffer, nullptr,
        const_cast<odil::Value::Binary::value_type::value_type*>(&binary_item[0]),
        binary_item.size(), 1, PyBUF_SIMPLE);
    PyObject * memory_view = PyMemoryView_FromBuffer(&buffer);

    return pybind11::reinterpret_steal<pybind11::object>(memory_view);
}

}

void wrap_Value(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    class_<Value> value(m, "Value");
    value
        .def(init<Value::Integers>())
        .def(init<Value::Reals>())
        .def(init<Value::Strings>())
        .def(init<Value::DataSets>())
        .def(init<Value::Binary>())
        // Explicit constructor since Value::XXX are opaque
        // WARNING: define *after* other constructors for correct priority
        .def(
            init([](iterable & source) {
                return convert_iterable<Value>(source);
            }))
        .def("get_type", &Value::get_type)
        .def("empty", &Value::empty)
        .def("size", &Value::size)
        .def(
            "as_integers", (Value::Integers & (Value::*)()) &Value::as_integers,
            return_value_policy::reference_internal)
        .def(
            "as_reals", (Value::Reals & (Value::*)()) &Value::as_reals,
            return_value_policy::reference_internal)
        .def(
            "as_strings", (Value::Strings & (Value::*)()) &Value::as_strings,
            return_value_policy::reference_internal)
        .def(
            "as_data_sets", (Value::DataSets & (Value::*)()) &Value::as_data_sets,
            return_value_policy::reference_internal)
        .def(
            "as_binary", (Value::Binary & (Value::*)()) &Value::as_binary,
            return_value_policy::reference_internal)
        .def(self == self)
        .def(self != self)
        .def("clear", &Value::clear)
        .def("__len__", &Value::size)
        .def_property_readonly("type", &Value::get_type)
    ;

    enum_<Value::Type>(value, "Type")
        .value("Integers", Value::Type::Integers)
        .value("Reals", Value::Type::Reals)
        .value("Strings", Value::Type::Strings)
        .value("DataSets", Value::Type::DataSets)
        .value("Binary", Value::Type::Binary)
    ;

    bind_vector<Value::Integers>(value, "Integers");
    bind_vector<Value::Reals>(value, "Reals");
    bind_vector<Value::Strings>(value, "Strings");
    bind_vector<Value::DataSets>(value, "DataSets");
    bind_vector<Value::Binary::value_type>(value, "BinaryItem")
        .def("get_memory_view", as_memory_view);
    bind_vector<Value::Binary>(value, "Binary");
}
