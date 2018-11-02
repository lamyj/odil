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

void update_2120(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x2120, 0x0010), ElementsDictionaryEntry("Queue Status", "QueueStatus",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2120, 0x0050), ElementsDictionaryEntry("Print Job Description Sequence", "PrintJobDescriptionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2120, 0x0070), ElementsDictionaryEntry("Referenced Print Job Sequence", "ReferencedPrintJobSequence",  "SQ", "1"));

    public_tags.emplace("QueueStatus", Tag(0x2120, 0x0010));
    public_tags.emplace("PrintJobDescriptionSequence", Tag(0x2120, 0x0050));
    public_tags.emplace("ReferencedPrintJobSequence", Tag(0x2120, 0x0070));
}

}

}