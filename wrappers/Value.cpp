/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "odil/DataSet.h"
#include "odil/Value.h"

boost::python::object create_integers(
    boost::python::tuple args, boost::python::dict kwargs)
{
    auto self = args[0];
    args = boost::python::tuple(args.slice(1, boost::python::_));
    return self.attr("__init__")();
}

void wrap_Value()
{
    using namespace boost::python;
    using namespace odil;

    typedef Value::Integers & (Value::*AsIntegers)();
    typedef Value::Reals & (Value::*AsReals)();
    typedef Value::Strings & (Value::*AsStrings)();
    typedef Value::DataSets & (Value::*AsDataSets)();
    typedef Value::Binary & (Value::*AsBinary)();

    // Define scope to enclose Integers, Reals, etc. in Value
    scope value_scope = class_<Value>("Value", init<>())
        .def(init<Value::Integers>())
        .def(init<Value::Reals>())
        .def(init<Value::Strings>())
        .def(init<Value::DataSets>())
        .def(init<Value::Binary>())
        .def("get_type", &Value::get_type)
        .def("empty", &Value::empty)
        .def(
            "as_integers", AsIntegers(&Value::as_integers), 
            return_value_policy<reference_existing_object>())
        .def(
            "as_reals", AsReals(&Value::as_reals), 
            return_value_policy<reference_existing_object>())
        .def(
            "as_strings", AsStrings(&Value::as_strings), 
            return_value_policy<reference_existing_object>())
        .def(
            "as_data_sets", AsDataSets(&Value::as_data_sets), 
            return_value_policy<reference_existing_object>())
        .def(
            "as_binary", AsBinary(&Value::as_binary), 
            return_value_policy<reference_existing_object>())
        .def(self == self)
        .def(self != self)
    ;

    class_<Value::Integers>("Integers")
        // TODO: constructor from Python Sequence
        .def(init<>())
        .def(vector_indexing_suite<Value::Integers>())
    ;
}

