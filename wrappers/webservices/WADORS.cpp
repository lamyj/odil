/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/webservices/WADORS.h"

namespace
{
class wadors_namespace {};
}

void wrap_webservices_WADORS()
{
    using namespace boost::python;
    using namespace odil::webservices::WADORS;

    scope wadors_scope = class_<wadors_namespace>("WADORS");

    enum_<Type>("Type")
        .value("None", Type::None)
        .value("DICOM", Type::DICOM)
        .value("BulkData", Type::BulkData)
        .value("PixelData", Type::PixelData)
    ;

    enum_<Representation>("Representation")
        .value("DICOM", Representation::DICOM)
        .value("DICOM_XML", Representation::DICOM_XML)
        .value("DICOM_JSON", Representation::DICOM_JSON)
    ;
}
