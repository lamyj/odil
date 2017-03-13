/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <string>
#include <vector>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

template<typename T>
struct vector_converter
{
    typedef vector_converter<T> Self;
    typedef std::vector<T> cpp_type;

    vector_converter(std::string const & suffix)
    {
        using namespace boost::python;
        converter::registry::push_back(
            &Self::convertible, &Self::converter, type_id<cpp_type>());

        class_<cpp_type>(("vector_"+suffix).c_str())
            .def(init<>())
            .def("__init__", make_constructor(&Self::constructor))
            .def(vector_indexing_suite<cpp_type>())
        ;
    }

    static void * convertible(PyObject * obj_ptr)
    {
        if(PySequence_Check(obj_ptr))
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

        object obj(handle<>(borrowed(obj_ptr)));

        typedef converter::rvalue_from_python_storage<cpp_type> storage_t;
        void * storage = reinterpret_cast<
                converter::rvalue_from_python_storage<cpp_type>*
            >(data)->storage.bytes;
        cpp_type * output = new (storage) cpp_type();
        output->reserve(len(obj));

        for(auto i=0; i<len(obj); ++i)
        {
            T const value = extract<T>(obj[i]);
            output->push_back(value);
        }

        data->convertible = storage;
    }

    boost::shared_ptr<cpp_type>
    constructor(boost::python::object const & sequence)
    {
        // Old versions of Boost.Python (Debian 7, Ubuntu 12.04) do not like
        // std::shared_ptr
        boost::shared_ptr<cpp_type> result;
        result->reserve(boost::python::len(sequence));
        for(long i=0; i<boost::python::len(sequence); ++i)
        {
            boost::python::object item = sequence[i];
            (*result)[i] = boost::python::extract<T>(item);
        }

        return result;
    }
};

void wrap_std_vector()
{
    vector_converter<int>("i");
}
