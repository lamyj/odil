/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

#include <odil/UIDsDictionary.h>

#include "opaque_types.h"
#include "type_casters.h"

void wrap_UIDsDictionary(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    class_<UIDsDictionaryEntry>(m, "UIDsDictionaryEntry")
        .def(init<std::string, std::string, std::string>())
        .def_readwrite("name", &UIDsDictionaryEntry::name)
        .def_readwrite("keyword", &UIDsDictionaryEntry::keyword)
        .def_readwrite("type", &UIDsDictionaryEntry::type)
    ;

    bind_map<UIDsDictionary>(m, "UIDsDictionary");
}

