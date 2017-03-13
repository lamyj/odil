#include <emscripten/bind.h>

#include "odil/Tag.h"

void wrap_Tag()
{
    emscripten::class_<odil::Tag>("Tag")
        .constructor<int, int>()
        .property("group", &odil::Tag::group)
        .property("element", &odil::Tag::element)
        .function("is_private", &odil::Tag::is_private)
        .function("get_name", &odil::Tag::get_name)
        .function("equal", &odil::Tag::operator==)
        .function("notEqual", &odil::Tag::operator!=)
        .function("less", &odil::Tag::operator<)
        .function("greater", &odil::Tag::operator>)
        .function("lessEqual", &odil::Tag::operator<=)
        .function("greaterEqual", &odil::Tag::operator>=)
        .function("toString", &odil::Tag::operator std::string)
    ;
}
