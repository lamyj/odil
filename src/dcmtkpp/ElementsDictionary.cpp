/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/ElementsDictionary.h"

#include <string>

namespace odil
{

ElementsDictionaryEntry
::ElementsDictionaryEntry(
    std::string const & name, std::string const & keyword,
    std::string const & vr, std::string const & vm)
: name(name), keyword(keyword), vr(vr), vm(vm)
{
    // Nothing else
}

}
