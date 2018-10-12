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

void update_0088(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0088, 0x0130), ElementsDictionaryEntry("Storage Media File-set ID", "StorageMediaFileSetID",  "SH", "1"));
    public_dictionary.emplace(Tag(0x0088, 0x0140), ElementsDictionaryEntry("Storage Media File-set UID", "StorageMediaFileSetUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0088, 0x0200), ElementsDictionaryEntry("Icon Image Sequence", "IconImageSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0088, 0x0904), ElementsDictionaryEntry("Topic Title", "TopicTitle",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0088, 0x0906), ElementsDictionaryEntry("Topic Subject", "TopicSubject",  "ST", "1"));
    public_dictionary.emplace(Tag(0x0088, 0x0910), ElementsDictionaryEntry("Topic Author", "TopicAuthor",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0088, 0x0912), ElementsDictionaryEntry("Topic Keywords", "TopicKeywords",  "LO", "1-32"));

    public_tags.emplace("StorageMediaFileSetID", Tag(0x0088, 0x0130));
    public_tags.emplace("StorageMediaFileSetUID", Tag(0x0088, 0x0140));
    public_tags.emplace("IconImageSequence", Tag(0x0088, 0x0200));
    public_tags.emplace("TopicTitle", Tag(0x0088, 0x0904));
    public_tags.emplace("TopicSubject", Tag(0x0088, 0x0906));
    public_tags.emplace("TopicAuthor", Tag(0x0088, 0x0910));
    public_tags.emplace("TopicKeywords", Tag(0x0088, 0x0912));
}

}

}