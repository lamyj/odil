/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a9546367_fb58_452f_837b_69d26d0e6a43
#define _a9546367_fb58_452f_837b_69d26d0e6a43

#include <Python.h>

#include <string>

#include <pybind11/pybind11.h>

#include <odil/VR.h>

namespace pybind11
{

namespace detail
{

// Example taken from https://github.com/pybind/pybind11/issues/1176#issuecomment-343312352
template<>
struct type_caster<odil::VR>: public type_caster_base<odil::VR>
{
    using base = type_caster_base<odil::VR>;

    bool load(handle src, bool convert)
    {
        if(base::load(src, convert))
        {
            return true;
        }

        object utf8;
        if(PyUnicode_Check(src.ptr()))
        {
            utf8 = reinterpret_steal<object>(PyUnicode_AsUTF8String(src.ptr()));
        }
        else if(PYBIND11_BYTES_CHECK(src.ptr()))
        {
            utf8 = reinterpret_borrow<object>(src);
        }
        if(!utf8)
        {
            return false;
        }

        std::string const string{PYBIND11_BYTES_AS_STRING(utf8.ptr())};
        this->value = new odil::VR{odil::as_vr(string)};
        return true;
    }

    static handle cast(odil::VR src, return_value_policy policy, handle parent)
    {
        return base::cast(src, policy, parent);
    }
};

}

}

#endif // _a9546367_fb58_452f_837b_69d26d0e6a43
