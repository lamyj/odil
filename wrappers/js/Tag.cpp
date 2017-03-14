/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <emscripten/bind.h>

#include "odil/Tag.h"

void wrap_Tag()
{
    using namespace emscripten;
    using namespace odil;
    
    class_<Tag>("Tag")
        .constructor<int, int>()
        .property("group", &Tag::group)
        .property("element", &Tag::element)
        .function("is_private", &Tag::is_private)
        .function("get_name", &Tag::get_name)
        .function("equal", &Tag::operator==)
        .function("notEqual", &Tag::operator!=)
        .function("less", &Tag::operator<)
        .function("greater", &Tag::operator>)
        .function("lessEqual", &Tag::operator<=)
        .function("greaterEqual", &Tag::operator>=)
        .function("toString", &Tag::operator std::string)
    ;
}
