/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <emscripten/bind.h>

#include "odil/VR.h"

void wrap_VR()
{
    using namespace emscripten;
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
        .value("FL", VR::FL)
        .value("FD", VR::FD)
        .value("IS", VR::IS)
        .value("LO", VR::LO)
        .value("LT", VR::LT)
        .value("OB", VR::OB)
        .value("OD", VR::OD)
        .value("OF", VR::OF)
        .value("OL", VR::OL)
        .value("OW", VR::OW)
        .value("PN", VR::PN)
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
    
    function("VRtoString", select_overload<std::string(VR)>(&as_string));
}
