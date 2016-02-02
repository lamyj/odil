/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/shared_ptr.hpp>

#include "odil/DataSet.h"
#include "odil/Value.h"

template<typename T, typename python_type=typename T::value_type>
boost::shared_ptr<T> create_value(boost::python::object const & sequence)
{
    typedef typename T::value_type value_type;

    std::vector<value_type> values(boost::python::len(sequence));
    for(long i=0; i<boost::python::len(sequence); ++i)
    {
        boost::python::object item = sequence[i];
        values[i] = boost::python::extract<python_type>(item);
    }

    // Old versions of Boost.Python (Debian 7, Ubuntu 12.04) do not like 
    // std::shared_ptr
    return boost::shared_ptr<T>(new T(values));
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
        .def(init<>())
        .def("__init__", make_constructor(create_value<Value::Integers>))
        .def(vector_indexing_suite<Value::Integers>())
    ;

    class_<Value::Reals>("Reals")
        .def(init<>())
        .def("__init__", make_constructor(create_value<Value::Reals>))
        .def(vector_indexing_suite<Value::Reals>())
    ;

    class_<Value::Strings>("Strings")
        .def(init<>())
        .def("__init__", make_constructor(create_value<Value::Strings>))
        .def(vector_indexing_suite<Value::Strings>())
    ;

    class_<Value::DataSets>("DataSets")
        .def(init<>())
        .def("__init__", make_constructor(create_value<Value::DataSets>))
        .def(vector_indexing_suite<Value::DataSets>())
    ;

    class_<Value::Binary>("Binary")
        .def(init<>())
        .def("__init__", make_constructor(create_value<Value::Binary, char>))
        .def(vector_indexing_suite<Value::Binary>())
    ;
}

