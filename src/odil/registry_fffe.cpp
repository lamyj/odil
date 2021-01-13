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

void update_fffe(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0xfffe, 0xe000), ElementsDictionaryEntry("Item", "Item",  "See Note", "1"));
    public_dictionary.emplace(Tag(0xfffe, 0xe00d), ElementsDictionaryEntry("Item Delimitation Item", "ItemDelimitationItem",  "See Note", "1"));
    public_dictionary.emplace(Tag(0xfffe, 0xe0dd), ElementsDictionaryEntry("Sequence Delimitation Item", "SequenceDelimitationItem",  "See Note", "1"));

    public_tags.emplace("Item", Tag(0xfffe, 0xe000));
    public_tags.emplace("ItemDelimitationItem", Tag(0xfffe, 0xe00d));
    public_tags.emplace("SequenceDelimitationItem", Tag(0xfffe, 0xe0dd));
}

}

}