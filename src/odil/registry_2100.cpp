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

void update_2100(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x2100, 0x0010), ElementsDictionaryEntry("Print Job ID", "PrintJobID",  "SH", "1"));
    public_dictionary.emplace(Tag(0x2100, 0x0020), ElementsDictionaryEntry("Execution Status", "ExecutionStatus",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2100, 0x0030), ElementsDictionaryEntry("Execution Status Info", "ExecutionStatusInfo",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2100, 0x0040), ElementsDictionaryEntry("Creation Date", "CreationDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x2100, 0x0050), ElementsDictionaryEntry("Creation Time", "CreationTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x2100, 0x0070), ElementsDictionaryEntry("Originator", "Originator",  "AE", "1"));
    public_dictionary.emplace(Tag(0x2100, 0x0140), ElementsDictionaryEntry("Destination AE", "DestinationAE",  "AE", "1"));
    public_dictionary.emplace(Tag(0x2100, 0x0160), ElementsDictionaryEntry("Owner ID", "OwnerID",  "SH", "1"));
    public_dictionary.emplace(Tag(0x2100, 0x0170), ElementsDictionaryEntry("Number of Films", "NumberOfFilms",  "IS", "1"));
    public_dictionary.emplace(Tag(0x2100, 0x0500), ElementsDictionaryEntry("Referenced Print Job Sequence (Pull Stored Print)", "ReferencedPrintJobSequencePullStoredPrint",  "SQ", "1"));

    public_tags.emplace("PrintJobID", Tag(0x2100, 0x0010));
    public_tags.emplace("ExecutionStatus", Tag(0x2100, 0x0020));
    public_tags.emplace("ExecutionStatusInfo", Tag(0x2100, 0x0030));
    public_tags.emplace("CreationDate", Tag(0x2100, 0x0040));
    public_tags.emplace("CreationTime", Tag(0x2100, 0x0050));
    public_tags.emplace("Originator", Tag(0x2100, 0x0070));
    public_tags.emplace("DestinationAE", Tag(0x2100, 0x0140));
    public_tags.emplace("OwnerID", Tag(0x2100, 0x0160));
    public_tags.emplace("NumberOfFilms", Tag(0x2100, 0x0170));
    public_tags.emplace("ReferencedPrintJobSequencePullStoredPrint", Tag(0x2100, 0x0500));
}

}

}