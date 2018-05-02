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

void update_2030(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x2030, 0x0010), ElementsDictionaryEntry("Annotation Position", "AnnotationPosition",  "US", "1"));
    public_dictionary.emplace(Tag(0x2030, 0x0020), ElementsDictionaryEntry("Text String", "TextString",  "LO", "1"));

    public_tags.emplace("AnnotationPosition", Tag(0x2030, 0x0010));
    public_tags.emplace("TextString", Tag(0x2030, 0x0020));
}

}

}