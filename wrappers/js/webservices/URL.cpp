/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <emscripten.h>
#include <emscripten/bind.h>

#include "odil/webservices/URL.h"

void wrap_webservices_URL()
{
    using namespace emscripten;
    using namespace odil::webservices;
    
    class_<URL>("webservices_URL")
        .constructor<>()
        .property("scheme", &URL::scheme)
        .property("authority", &URL::authority)
        .property("path", &URL::path)
        .property("query", &URL::query)
        .property("fragment", &URL::fragment)
        .function("equal", &URL::operator==)
        .function("notEqual", &URL::operator!=)
        .function("toString", &URL::operator std::string)
        .class_function("parse", &URL::parse)
    ;
    
    EM_ASM(
        Module['webservices']['URL'] = Module['webservices_URL'];
        delete Module['webservices_URL'];
    );
}
