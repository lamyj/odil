/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/registry.h"

#include "opaque_types.h"
#include "type_casters.h"

void wrap_registry(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    auto registry_ = m.def_submodule("registry");

    for(auto const & entry: registry::public_dictionary)
    {
        if(entry.first.get_type() == ElementsDictionaryKey::Type::Tag)
        {
            registry_.attr(entry.second.keyword.c_str()) = entry.first.get_tag();
        }
    }

    for(auto const & entry: registry::uids_dictionary)
    {
        registry_.attr(entry.second.keyword.c_str()) = entry.first;
    }

    registry_.attr("public_dictionary") = registry::public_dictionary;
    registry_.attr("uids_dictionary") = registry::uids_dictionary;
}
