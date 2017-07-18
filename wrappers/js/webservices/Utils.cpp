/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <emscripten.h>
#include <emscripten/bind.h>

#include "odil/webservices/Utils.h"

void wrap_webservices_Utils()
{
    using namespace emscripten;
    using namespace odil::webservices;

    enum_<Type>("webservices_Utils_Type")
        .value("None", Type::None)
        .value("DICOM", Type::DICOM)
        .value("BulkData", Type::BulkData)
        .value("PixelData", Type::PixelData)
    ;

    enum_<Representation>("webservices_Utils_Representation")
        .value("DICOM", Representation::DICOM)
        .value("DICOM_XML", Representation::DICOM_XML)
        .value("DICOM_JSON", Representation::DICOM_JSON)
    ;

    EM_ASM(
        Module['webservices']['Utils'] = {};

        Module['webservices']['Utils']['Type'] =
            Module['webservices_Utils_Type'];
        delete Module['webservices_Utils_Type'];

        Module['webservices']['Utils']['Representation'] =
            Module['webservices_Utils_Representation'];
        delete Module['webservices_Utils_Representation'];
    );
}
