/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include "value_constructor.h"

#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>

#include "odil/DataSet.h"
#include "odil/Value.h"

#if PY_MAJOR_VERSION >= 3
#define IS_PY3K
#endif

boost::shared_ptr<odil::Value>
value_constructor(boost::python::object const & source)
{
    odil::Value * result = nullptr;
    if(boost::python::len(source) == 0)
    {
        if(boost::python::extract<odil::Value::Integers>(source).check())
        {
            result = new odil::Value(odil::Value::Integers());
        }
        else if(boost::python::extract<odil::Value::Reals>(source).check())
        {
            result = new odil::Value(odil::Value::Reals());
        }
        else if(boost::python::extract<odil::Value::Strings>(source).check())
        {
            result = new odil::Value(odil::Value::Strings());
        }
        else if(boost::python::extract<odil::Value::DataSets>(source).check())
        {
            result = new odil::Value(odil::Value::DataSets());
        }
        else if(boost::python::extract<odil::Value::Binary>(source).check())
        {
            result = new odil::Value(odil::Value::Binary());
        }
        else
        {
            throw odil::Exception("Unknown empty type");
        }
    }
    else
    {
        boost::python::object first = source[0];
        PyObject * first_ptr = first.ptr();
        
#ifdef IS_PY3K
        if(PyLong_Check(first_ptr))
#else
        if(PyInt_Check(first_ptr))
#endif
        {
            boost::python::stl_input_iterator<odil::Value::Integer> 
                begin(source), end;
            result = new odil::Value(odil::Value::Integers(begin, end));
        }
        else if(PyFloat_Check(first_ptr))
        {
            boost::python::stl_input_iterator<odil::Value::Real> 
                begin(source), end;
            result = new odil::Value(odil::Value::Reals(begin, end));
        }
#ifdef IS_PY3K
        else if(PyUnicode_Check(first_ptr))
#else
        else if(PyString_Check(first_ptr))
#endif
        {
            boost::python::stl_input_iterator<odil::Value::String> 
                begin(source), end;
            result = new odil::Value(odil::Value::Strings(begin, end));
        }
        else if(PyByteArray_Check(first_ptr))
        {
            boost::python::stl_input_iterator<PyObject*> it(source), end;
            odil::Value::Binary binary;
            for(int i=0; i<boost::python::len(source); ++i)
            {
                boost::python::object python_item = source[i];
                PyObject * python_ptr = python_item.ptr();
                
                auto buffer = PyByteArray_AsString(python_ptr);
                auto const length = PyObject_Length(python_ptr);
                
                odil::Value::Binary::value_type const item(buffer, buffer+length);
                binary.push_back(item);
            }
            result = new odil::Value(binary);
        }
        else
        {
            auto odil_module = boost::python::import("odil");
            boost::python::object DataSetType = odil_module.attr("DataSet");
            if(PyObject_IsInstance(first_ptr, DataSetType.ptr()))
            {
                boost::python::stl_input_iterator<std::shared_ptr<odil::DataSet>>
                    begin(source), end;
                result = new odil::Value(odil::Value::DataSets(begin, end));
            }
            else
            {
                throw odil::Exception("Unknown value type");
            }
        }
    }
    
    // Old versions of Boost.Python (Debian 7, Ubuntu 12.04) do not like 
    // std::shared_ptr
    return boost::shared_ptr<odil::Value>(result);
}
