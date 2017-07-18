/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <emscripten.h>
#include <emscripten/bind.h>

#include "odil/webservices/Selector.h"


void wrap_webservices_Selector()
{
    using namespace emscripten;
    using namespace odil::webservices;

    class_<Selector>("webservices_Selector")
        .constructor<>()
        .constructor<std::map<std::string, std::string>, std::vector<int>>()
        .function("get_study", &Selector::get_study)
        .function("get_series", &Selector::get_series)
        .function("get_instance", &Selector::get_instance)
        .function("get_frames", &Selector::get_frames)
        .function("set_study", &Selector::set_study)
        .function("set_series", &Selector::set_series)
        .function("set_instance", &Selector::set_instance)
        .function("set_frames", &Selector::set_frames)
        .function("is_study_present", &Selector::is_study_present)
        .function("is_series_present", &Selector::is_series_present)
        .function("is_instance_present", &Selector::is_instance_present)
        .function("equal", &Selector::operator==)
        .function("notEqual", &Selector::operator!=)
        .function("get_path", &Selector::get_path)
    ;

    EM_ASM(
        Module['webservices']['Selector'] =
            Module['webservices_Selector'];
        delete Module['webservices_Selector'];
    );

}
