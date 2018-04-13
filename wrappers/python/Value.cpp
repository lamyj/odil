/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/shared_ptr.hpp>

#include "odil/DataSet.h"
#include "odil/Value.h"

#include "value_constructor.h"

namespace
{

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

boost::python::object
as_memory_view(odil::Value::Binary::value_type const & binary_item)
{
    Py_buffer buffer;
    PyBuffer_FillInfo(
        &buffer, nullptr,
        const_cast<odil::Value::Binary::value_type::value_type*>(&binary_item[0]),
        binary_item.size(), 1, PyBUF_SIMPLE);
    PyObject * memory_view = PyMemoryView_FromBuffer(&buffer);

    return boost::python::object(boost::python::handle<>(memory_view));
}

}

/// @brief Convert to a byte string (str for Python 2, bytes for Python 3).
boost::python::object
as_bytes(odil::Value::Strings::value_type const & string)
{
    auto bytes =
#if PY_VERSION_HEX >= 0x03000000
        PyBytes_FromStringAndSize(&string[0], string.size());
#else
        PyString_FromStringAndSize(&string[0], string.size());
#endif

    return boost::python::object(boost::python::handle<>(bytes));
}

/// @brief Access Value::Strings items as byte strings
class StringsIndexingSuite:
    public boost::python::vector_indexing_suite<odil::Value::Strings>
{
public:
    typedef odil::Value::Strings Container;

    static boost::python::object
    get_item(Container const & container, Container::size_type i)
    {
        auto const & item = container[i];
        return as_bytes(item);
    }
};

/// @brief Iterate over Value::Strings as byte strings
class StringsIterator
{
public:
    StringsIterator(odil::Value::Strings const & strings)
    : strings(strings), iterator(strings.begin())
    {
        // Nothing else
    }

    boost::python::object next()
    {
        if(this->iterator != this->strings.end())
        {
            auto const & item = *this->iterator;
            ++this->iterator;
            return as_bytes(item);
        }
        else
        {
            boost::python::objects::stop_iteration_error();
        }
    }
private:
    odil::Value::Strings const & strings;
    odil::Value::Strings::const_iterator iterator;
};

/// @brief Return an iterator to the Value::Strings object.
StringsIterator Strings__iter__(odil::Value::Strings const & strings)
{
    return StringsIterator(strings);
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
    scope value_scope = class_<Value>("Value", no_init)
        .def("__init__", make_constructor(value_constructor))
        .add_property("type", &Value::get_type)
        .def("empty", &Value::empty)
        .def("size", &Value::size)
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
        .def("clear", &Value::clear)
        .def("__len__", &Value::size)
    ;
    
    enum_<Value::Type>("Type")
        .value("Integers", Value::Type::Integers)
        .value("Reals", Value::Type::Reals)
        .value("Strings", Value::Type::Strings)
        .value("DataSets", Value::Type::DataSets)
        .value("Binary", Value::Type::Binary)
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

    {
        scope strings_scope = class_<Value::Strings>("Strings")
            .def(init<>())
            .def("__init__", make_constructor(create_value<Value::Strings>))
            .def(
                vector_indexing_suite<
                    Value::Strings, false, StringsIndexingSuite>())
            .def("__iter__", Strings__iter__)
        ;

        class_<StringsIterator>("Iterator", init<Value::Strings>())
            .def(
#if PY_VERSION_HEX >= 0x03000000
                "__next__",
#else
                "next",
#endif
                &StringsIterator::next)
        ;
    }

    class_<Value::DataSets>("DataSets")
        .def(init<>())
        .def("__init__", make_constructor(create_value<Value::DataSets>))
        .def(vector_indexing_suite<Value::DataSets>())
    ;

    class_<Value::Binary::value_type>("BinaryItem")
        .def(init<>())
        .def(
            "__init__",
            make_constructor(create_value<Value::Binary::value_type, char>))
        .def(vector_indexing_suite<Value::Binary::value_type>())
        .def("get_memory_view", as_memory_view)
    ;

    class_<Value::Binary>("Binary")
        .def(init<>())
        .def("__init__", make_constructor(create_value<Value::Binary>))
        .def(vector_indexing_suite<Value::Binary>())
    ;
}
