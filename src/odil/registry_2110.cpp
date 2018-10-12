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

void update_2110(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x2110, 0x0010), ElementsDictionaryEntry("Printer Status", "PrinterStatus",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2110, 0x0020), ElementsDictionaryEntry("Printer Status Info", "PrinterStatusInfo",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2110, 0x0030), ElementsDictionaryEntry("Printer Name", "PrinterName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x2110, 0x0099), ElementsDictionaryEntry("Print Queue ID", "PrintQueueID",  "SH", "1"));

    public_tags.emplace("PrinterStatus", Tag(0x2110, 0x0010));
    public_tags.emplace("PrinterStatusInfo", Tag(0x2110, 0x0020));
    public_tags.emplace("PrinterName", Tag(0x2110, 0x0030));
    public_tags.emplace("PrintQueueID", Tag(0x2110, 0x0099));
}

}

}