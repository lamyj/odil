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

void update_4000(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x4000, 0x0010), ElementsDictionaryEntry("Arbitrary", "Arbitrary",  "LT", "1"));
    public_dictionary.emplace(Tag(0x4000, 0x4000), ElementsDictionaryEntry("Text Comments", "TextComments",  "LT", "1"));

    public_tags.emplace("Arbitrary", Tag(0x4000, 0x0010));
    public_tags.emplace("TextComments", Tag(0x4000, 0x4000));
}

}

}