/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <emscripten.h>
#include <emscripten/bind.h>

#include "odil/webservices/Message.h"

void wrap_webservices_Message()
{
    using namespace emscripten;
    using namespace odil::webservices;
    
    class_<Message>("webservices_Message")
        .constructor<std::map<std::string, std::string>, std::string>()
        .function("get_headers", &Message::get_headers)
        .function("set_headers", &Message::set_headers)
        .function("has_header", &Message::has_header)
        .function("get_header", &Message::get_header)
        .function("set_header", &Message::set_header)
        .function("get_body", &Message::get_body)
        .function("set_body", &Message::set_body)
    ;
    
    EM_ASM(
        Module['webservices']['Message'] = Module['webservices_Message'];
        delete Module['webservices_Message'];
    );
}
