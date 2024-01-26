/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <map>
#include <string>
#include <tuple>

#include "odil/ElementsDictionary.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{

void update_5200(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x5200, 0x9229), ElementsDictionaryEntry("Shared Functional Groups Sequence", "SharedFunctionalGroupsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x5200, 0x9230), ElementsDictionaryEntry("Per-Frame Functional Groups Sequence", "PerFrameFunctionalGroupsSequence",  "SQ", "1"));

    public_tags.emplace("SharedFunctionalGroupsSequence", Tag(0x5200, 0x9229));
    public_tags.emplace("PerFrameFunctionalGroupsSequence", Tag(0x5200, 0x9230));
}

}

}