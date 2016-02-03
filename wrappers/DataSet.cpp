/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include "odil/DataSet.h"


BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(add_overloads_2, odil::DataSet::add, 1, 2);
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(add_overloads_3, odil::DataSet::add, 2, 3);

void wrap_DataSet()
{
    using namespace boost::python;
    using namespace odil;


    class_<DataSet>("DataSet", init<>())
        .def(
            "add", 
            static_cast<void (DataSet::*)(Tag const &, Element const &)>(
                &DataSet::add))
        .def(
            "add", 
            static_cast<void (DataSet::*)(Tag const &, VR)>(&DataSet::add),
            add_overloads_2())
        .def(
            "add", 
            static_cast<void (DataSet::*)(Tag const &, Value::Integers const &, VR)>(
                &DataSet::add),
            add_overloads_3())
        .def(
            "add", 
            static_cast<void (DataSet::*)(Tag const &, Value::Reals const &, VR)>(
                &DataSet::add),
            add_overloads_3())
        .def(
            "add", 
            static_cast<void (DataSet::*)(Tag const &, Value::Strings const &, VR)>(
                &DataSet::add),
            add_overloads_3())
        .def(
            "add", 
            static_cast<void (DataSet::*)(Tag const &, Value::DataSets const &, VR)>(
                &DataSet::add),
            add_overloads_3())
        .def(
            "add", 
            static_cast<void (DataSet::*)(Tag const &, Value::Binary const &, VR)>(
                &DataSet::add),
            add_overloads_3())
        .def("remove", &DataSet::remove)
        .def("has", &DataSet::has)
        .def("empty", static_cast<bool (DataSet::*)() const>(&DataSet::empty))
        .def(
            "size", 
            static_cast<std::size_t (DataSet::*)() const>(&DataSet::size))
        .def("get_vr", &DataSet::get_vr)
        .def(
            "empty", 
            static_cast<bool (DataSet::*)(Tag const &) const>(&DataSet::empty))
        .def(
            "size", 
            static_cast<std::size_t (DataSet::*)(Tag const &) const>(
                &DataSet::size))
        // operator[], cf. map
        .def("is_int", &DataSet::is_int)
        .def(
            "as_int", 
            static_cast<Value::Integers & (DataSet::*)(Tag const &)>(
                &DataSet::as_int), 
            return_value_policy<reference_existing_object>())
        .def("is_real", &DataSet::is_real)
        .def(
            "as_real", 
            static_cast<Value::Reals & (DataSet::*)(Tag const &)>(
                &DataSet::as_real), 
            return_value_policy<reference_existing_object>())
        .def("is_string", &DataSet::is_string)
        .def(
            "as_string", 
            static_cast<Value::Strings & (DataSet::*)(Tag const &)>(
                &DataSet::as_string), 
            return_value_policy<reference_existing_object>())
        .def("is_data_set", &DataSet::is_data_set)
        .def(
            "as_data_set", 
            static_cast<Value::DataSets & (DataSet::*)(Tag const &)>(
                &DataSet::as_data_set), 
            return_value_policy<reference_existing_object>())
        .def("is_binary", &DataSet::is_binary)
        .def(
            "as_binary", 
            static_cast<Value::Binary & (DataSet::*)(Tag const &)>(
                &DataSet::as_binary), 
            return_value_policy<reference_existing_object>())
        // iteration
        .def(self == self)
        .def(self != self)
        //.def(map_indexing_suite<DataSet>())
        .def(
            "__len__", 
            static_cast<std::size_t (DataSet::*)() const>(&DataSet::size)) 
    ;
}
