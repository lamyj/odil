/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/unicode.h"
#include "odil/Value.h"

#include "opaque_types.h"
#include "type_casters.h"

void wrap_unicode(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    m.def(
        "as_utf8", as_utf8,
        "input"_a, "specific_character_set"_a, "is_pn"_a=false);
    m.def(
        "as_specific_character_set", as_specific_character_set,
        "input"_a, "specific_character_set"_a, "is_pn"_a=false);
    m.def(
        "as_unicode",
        [](
            std::string const & input,
            Value::Strings const & specific_character_set,
            bool is_pn=false)
        {
            auto const utf8_input = as_utf8(input, specific_character_set, is_pn);
            return utf8_input;
        },
        "input"_a, "specific_character_set"_a, "is_pn"_a=false);
}
