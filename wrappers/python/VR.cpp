/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/Exception.h"
#include "odil/VR.h"

#if PY_MAJOR_VERSION >= 3
    #define AsString(x) PyBytes_AsString(x)
#else
    #define IS_PY2
    #define AsString(x) PyString_AsString(x)
#endif

odil::VR as_vr(PyObject * object)
{
    PyObject * utf8 = nullptr;
    if(PyUnicode_Check(object))
    {
        // New reference
        utf8 = PyUnicode_AsUTF8String(object);
    }
#ifdef IS_PY2
    else if(PyString_Check(object))
    {
        utf8 = object;
        // Increase reference count to match PyUnicode_AsUTF8String
        Py_INCREF(utf8);
    }
#endif

    if(utf8 == nullptr)
    {
        throw odil::Exception("Object is not string-like");
    }

    std::string const vr_name(AsString(utf8));
    Py_DECREF(utf8);

    return odil::as_vr(vr_name);
}

void * convertible(PyObject* object)
{
    bool result=true;
    try
    {
        as_vr(object);
    }
    catch(...)
    {
        result = false;
    }

    return result?object:nullptr;
}

void construct(
    PyObject* object,
    boost::python::converter::rvalue_from_python_stage1_data* data)
{
    auto const vr = as_vr(object);

    void * storage = reinterpret_cast<
            boost::python::converter::rvalue_from_python_storage<odil::VR>*
        >(data)->storage.bytes;
    new (storage) odil::VR(vr);
    data->convertible = storage;
}

void wrap_VR()
{
    using namespace boost::python;
    using namespace odil;

    enum_<VR>("VR")
        .value("UNKNOWN", VR::UNKNOWN)
        .value("AE", VR::AE)
        .value("AS", VR::AS)
        .value("AT", VR::AT)
        .value("CS", VR::CS)
        .value("DA", VR::DA)
        .value("DS", VR::DS)
        .value("DT", VR::DT)
        .value("FD", VR::FD)
        .value("FL", VR::FL)
        .value("IS", VR::IS)
        .value("LO", VR::LO)
        .value("LT", VR::LT)
        .value("PN", VR::PN)
        .value("OB", VR::OB)
        .value("OF", VR::OF)
        .value("OW", VR::OW)
        .value("SH", VR::SH)
        .value("SL", VR::SL)
        .value("SQ", VR::SQ)
        .value("SS", VR::SS)
        .value("ST", VR::ST)
        .value("TM", VR::TM)
        .value("UC", VR::UC)
        .value("UI", VR::UI)
        .value("UL", VR::UL)
        .value("UN", VR::UN)
        .value("UR", VR::UR)
        .value("US", VR::US)
        .value("UT", VR::UT)
        .value("INVALID", VR::INVALID)
    ;
    converter::registry::push_back(
        &convertible, &construct, type_id<VR>());
    def("is_int", odil::is_int);
    def("is_real", odil::is_real);
    def("is_string", odil::is_string);
    def("is_binary", odil::is_binary);
}

