/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/UIDsDictionary.h"

#include <map>
#include <string>

namespace dcmtkpp
{

UIDsDictionaryEntry
::UIDsDictionaryEntry(
        std::string const & name, std::string const & keyword,
        std::string const & type)
: name(name), keyword(keyword), type(type)
{
    // Nothing else.
}

}
