/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include <odil/registry.h>

namespace
{

class Dummy 
{
};

}

void wrap_registry()
{
    using namespace boost::python;
    using namespace odil;

    scope registry_scope = class_<Dummy>("registry");

    for(auto const & entry: registry::public_dictionary)
    {
        registry_scope.attr(entry.second.keyword.c_str()) = entry.first;
    }

    registry_scope.attr("public_dictionary") = registry::public_dictionary;
}
