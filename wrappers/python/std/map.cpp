/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <string>
#include <map>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

template<typename Key, typename Value>
struct map_converter
{
    typedef map_converter<Key, Value> Self;
    typedef std::map<Key, Value> cpp_type;

    map_converter(std::string const & suffix)
    {
        using namespace boost::python;
        converter::registry::push_back(
            &Self::convertible, &Self::converter, type_id<cpp_type>());

        class_<cpp_type>(("map_"+suffix).c_str())
            .def(init<>())
            .def("__init__", make_constructor(&Self::constructor))
            .def(map_indexing_suite<cpp_type>())
            .def("keys", &Self::keys)
            .def("values", &Self::values)
            .def("items", &Self::items)
        ;
    }

    static boost::python::object keys(cpp_type const & map)
    {
        using namespace boost::python;

        list result;
        for(auto const & item: map)
        {
            result.append(item.first);
        }
        return result;
    }

    static boost::python::object values(cpp_type const & map)
    {
        using namespace boost::python;

        list result;
        for(auto const & item: map)
        {
            result.append(item.second);
        }
        return result;
    }

    static boost::python::object items(cpp_type const & map)
    {
        using namespace boost::python;

        list result;
        for(auto const & item: map)
        {
            result.append(make_tuple(item.first, item.second));
        }
        return result;
    }

    static void * convertible(PyObject * obj_ptr)
    {
        if(PyMapping_Check(obj_ptr))
        {
            return obj_ptr;
        }
        else
        {
            return NULL;
        }
    }

    static void converter(
        PyObject * obj_ptr,
        boost::python::converter::rvalue_from_python_stage1_data * data)
    {
        using namespace boost::python;

        dict obj(handle<>(borrowed(obj_ptr)));

        typedef converter::rvalue_from_python_storage<cpp_type> storage_t;
        void * storage = reinterpret_cast<
                converter::rvalue_from_python_storage<cpp_type>*
            >(data)->storage.bytes;
        cpp_type * output = new (storage) cpp_type();

        auto items = obj.items();
        for(long i=0; i<len(items); ++i)
        {
            object item = items[i];

            Key const key_cpp = extract<Key>(item[0]);
            Value const value_cpp = extract<Value>(item[1]);

            output->insert(std::make_pair(key_cpp, value_cpp));
        }

        data->convertible = storage;
    }

    boost::shared_ptr<cpp_type>
    constructor(boost::python::dict const & mapping)
    {
        using namespace boost::python;

        // Old versions of Boost.Python (Debian 7, Ubuntu 12.04) do not like
        // std::shared_ptr
        boost::shared_ptr<cpp_type> result;

        auto items = mapping.items();
        for(long i=0; i<len(items); ++i)
        {
            object item = items[i];

            Key const key_cpp = extract<Key>(item[0]);
            Value const value_cpp = extract<Value>(item[1]);

            result->insert(std::make_pair(key_cpp, value_cpp));
        }

        return result;
    }
};

void wrap_std_map()
{
    map_converter<std::string, std::string>("string_string");
}
