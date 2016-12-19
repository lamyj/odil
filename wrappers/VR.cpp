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

void * convertible(PyObject* object)
{
    bool result;
    if(!PyString_Check(object))
    {
        result = false;
    }
    else
    {
        auto const data = PyString_AsString(object);
        try
        {
            odil::as_vr(data);
            result = true;
        }
        catch(odil::Exception const &)
        {
            result = false;
        }
    }

    return result?object:nullptr;
}

void construct(
    PyObject* object,
    boost::python::converter::rvalue_from_python_stage1_data* data)
{
    auto const vr_data = PyString_AsString(object);
    auto const vr = odil::as_vr(vr_data);

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
}

