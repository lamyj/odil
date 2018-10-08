/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/webservices/Utils.h"

void wrap_webservices_Utils(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil::webservices;

    auto utils = m.def_submodule("Utils");

    enum_<Type>(utils, "Type")
        .value("None_", Type::None)
        .value("DICOM", Type::DICOM)
        .value("BulkData", Type::BulkData)
        .value("PixelData", Type::PixelData)
    ;

    enum_<Representation>(utils, "Representation")
        .value("DICOM", Representation::DICOM)
        .value("DICOM_XML", Representation::DICOM_XML)
        .value("DICOM_JSON", Representation::DICOM_JSON)
    ;
}
