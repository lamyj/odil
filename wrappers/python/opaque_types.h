/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _0dcf136c_4136_40c3_a036_2a74ca0c54d1
#define _0dcf136c_4136_40c3_a036_2a74ca0c54d1

#include <algorithm>

#include "pybind11/pybind11.h"

#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/Value.h"

// The following must be in every translation unit.
PYBIND11_MAKE_OPAQUE(odil::Value::Integers);
PYBIND11_MAKE_OPAQUE(odil::Value::Reals);
PYBIND11_MAKE_OPAQUE(odil::Value::Strings);
PYBIND11_MAKE_OPAQUE(odil::Value::DataSets);
PYBIND11_MAKE_OPAQUE(odil::Value::Binary);
PYBIND11_MAKE_OPAQUE(odil::Value::Binary::value_type);

template<typename T, typename ... Args>
T convert_sequence(pybind11::sequence & source, Args && ... args)
{
    if(pybind11::len(source) == 0)
    {
        throw odil::Exception("Empty sequence has no type");
    }

#define try_convert(Items) \
    try \
    { \
        Items items(len(source)); \
        std::transform( \
            source.begin(), source.end(), items.begin(), \
            [](pybind11::handle const h) { \
                return h.cast<typename Items::value_type>(); \
            } \
        ); \
        return T{items, std::forward<Args>(args)...}; \
    } \
    catch(pybind11::cast_error const &) \
    { \
        /* Ignore */ \
    }

    try_convert(odil::Value::Integers);
    try_convert(odil::Value::Reals);
    try_convert(odil::Value::Strings);
    try_convert(odil::Value::DataSets);
    try_convert(odil::Value::Binary);

#undef try_convert

    try
    {
        odil::Value::Binary items(len(source));
        std::transform(
            source.begin(), source.end(), items.begin(),
            [](pybind11::handle const h)
            {
                auto pyobject = h.ptr();
                if(PyByteArray_Check(pyobject))
                {
                    auto const begin = PyByteArray_AsString(pyobject);
                    auto const length = PyObject_Length(pyobject);
                    return odil::Value::Binary::value_type{begin, begin+length};
                }
                else
                {
                    throw pybind11::cast_error();
                }
            }
        );
        return T{items, std::forward<Args>(args)...};
    }
    catch(pybind11::cast_error const &)
    {
        /* ignore */
    }

    throw odil::Exception("Unknown value type");
}

#endif // _0dcf136c_4136_40c3_a036_2a74ca0c54d1
