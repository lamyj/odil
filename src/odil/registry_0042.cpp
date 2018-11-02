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

void update_0042(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0042, 0x0010), ElementsDictionaryEntry("Document Title", "DocumentTitle",  "ST", "1"));
    public_dictionary.emplace(Tag(0x0042, 0x0011), ElementsDictionaryEntry("Encapsulated Document", "EncapsulatedDocument",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0042, 0x0012), ElementsDictionaryEntry("MIME Type of Encapsulated Document", "MIMETypeOfEncapsulatedDocument",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0042, 0x0013), ElementsDictionaryEntry("Source Instance Sequence", "SourceInstanceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0042, 0x0014), ElementsDictionaryEntry("List of MIME Types", "ListOfMIMETypes",  "LO", "1-n"));

    public_tags.emplace("DocumentTitle", Tag(0x0042, 0x0010));
    public_tags.emplace("EncapsulatedDocument", Tag(0x0042, 0x0011));
    public_tags.emplace("MIMETypeOfEncapsulatedDocument", Tag(0x0042, 0x0012));
    public_tags.emplace("SourceInstanceSequence", Tag(0x0042, 0x0013));
    public_tags.emplace("ListOfMIMETypes", Tag(0x0042, 0x0014));
}

}

}