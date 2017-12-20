/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>
#include "odil/unicode.h"
#include "odil/Value.h"

namespace 
{

boost::python::object as_unicode(
    std::string const & input, 
    odil::Value::Strings const & specific_character_set,
    bool is_pn=false)
{
    auto const utf8_input = odil::as_utf8(input, specific_character_set, is_pn);
    PyObject * unicode = PyUnicode_FromStringAndSize(
        &utf8_input[0], utf8_input.size());

    return boost::python::object(boost::python::handle<>(unicode));
}

}

void wrap_unicode()
{
    using namespace boost::python;
    using namespace odil;

    def(
        "as_utf8", &as_utf8, 
        (arg("input"), arg("specific_character_set"), arg("is_pn")=false));
    def(
        "as_specific_character_set", &as_specific_character_set,
        (arg("input"), arg("specific_character_set"), arg("is_pn")=false));
    def(
        "as_unicode", &as_unicode, 
        (arg("input"), arg("specific_character_set"), arg("is_pn")=false));
}
