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

void update_300e(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x300e, 0x0002), ElementsDictionaryEntry("Approval Status", "ApprovalStatus",  "CS", "1"));
    public_dictionary.emplace(Tag(0x300e, 0x0004), ElementsDictionaryEntry("Review Date", "ReviewDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x300e, 0x0005), ElementsDictionaryEntry("Review Time", "ReviewTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x300e, 0x0008), ElementsDictionaryEntry("Reviewer Name", "ReviewerName",  "PN", "1"));

    public_tags.emplace("ApprovalStatus", Tag(0x300e, 0x0002));
    public_tags.emplace("ReviewDate", Tag(0x300e, 0x0004));
    public_tags.emplace("ReviewTime", Tag(0x300e, 0x0005));
    public_tags.emplace("ReviewerName", Tag(0x300e, 0x0008));
}

}

}