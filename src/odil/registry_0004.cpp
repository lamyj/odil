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

void update_0004(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0004, 0x1130), ElementsDictionaryEntry("File-set ID", "FileSetID",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0004, 0x1141), ElementsDictionaryEntry("File-set Descriptor File ID", "FileSetDescriptorFileID",  "CS", "1-8"));
    public_dictionary.emplace(Tag(0x0004, 0x1142), ElementsDictionaryEntry("Specific Character Set of File-set Descriptor File", "SpecificCharacterSetOfFileSetDescriptorFile",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0004, 0x1200), ElementsDictionaryEntry("Offset of the First Directory Record of the Root Directory Entity", "OffsetOfTheFirstDirectoryRecordOfTheRootDirectoryEntity",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0004, 0x1202), ElementsDictionaryEntry("Offset of the Last Directory Record of the Root Directory Entity", "OffsetOfTheLastDirectoryRecordOfTheRootDirectoryEntity",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0004, 0x1212), ElementsDictionaryEntry("File-set Consistency Flag", "FileSetConsistencyFlag",  "US", "1"));
    public_dictionary.emplace(Tag(0x0004, 0x1220), ElementsDictionaryEntry("Directory Record Sequence", "DirectoryRecordSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0004, 0x1400), ElementsDictionaryEntry("Offset of the Next Directory Record", "OffsetOfTheNextDirectoryRecord",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0004, 0x1410), ElementsDictionaryEntry("Record In-use Flag", "RecordInUseFlag",  "US", "1"));
    public_dictionary.emplace(Tag(0x0004, 0x1420), ElementsDictionaryEntry("Offset of Referenced Lower-Level Directory Entity", "OffsetOfReferencedLowerLevelDirectoryEntity",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0004, 0x1430), ElementsDictionaryEntry("Directory Record Type", "DirectoryRecordType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0004, 0x1432), ElementsDictionaryEntry("Private Record UID", "PrivateRecordUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0004, 0x1500), ElementsDictionaryEntry("Referenced File ID", "ReferencedFileID",  "CS", "1-8"));
    public_dictionary.emplace(Tag(0x0004, 0x1504), ElementsDictionaryEntry("MRDR Directory Record Offset", "MRDRDirectoryRecordOffset",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0004, 0x1510), ElementsDictionaryEntry("Referenced SOP Class UID in File", "ReferencedSOPClassUIDInFile",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0004, 0x1511), ElementsDictionaryEntry("Referenced SOP Instance UID in File", "ReferencedSOPInstanceUIDInFile",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0004, 0x1512), ElementsDictionaryEntry("Referenced Transfer Syntax UID in File", "ReferencedTransferSyntaxUIDInFile",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0004, 0x151a), ElementsDictionaryEntry("Referenced Related General SOP Class UID in File", "ReferencedRelatedGeneralSOPClassUIDInFile",  "UI", "1-n"));
    public_dictionary.emplace(Tag(0x0004, 0x1600), ElementsDictionaryEntry("Number of References", "NumberOfReferences",  "UL", "1"));

    public_tags.emplace("FileSetID", Tag(0x0004, 0x1130));
    public_tags.emplace("FileSetDescriptorFileID", Tag(0x0004, 0x1141));
    public_tags.emplace("SpecificCharacterSetOfFileSetDescriptorFile", Tag(0x0004, 0x1142));
    public_tags.emplace("OffsetOfTheFirstDirectoryRecordOfTheRootDirectoryEntity", Tag(0x0004, 0x1200));
    public_tags.emplace("OffsetOfTheLastDirectoryRecordOfTheRootDirectoryEntity", Tag(0x0004, 0x1202));
    public_tags.emplace("FileSetConsistencyFlag", Tag(0x0004, 0x1212));
    public_tags.emplace("DirectoryRecordSequence", Tag(0x0004, 0x1220));
    public_tags.emplace("OffsetOfTheNextDirectoryRecord", Tag(0x0004, 0x1400));
    public_tags.emplace("RecordInUseFlag", Tag(0x0004, 0x1410));
    public_tags.emplace("OffsetOfReferencedLowerLevelDirectoryEntity", Tag(0x0004, 0x1420));
    public_tags.emplace("DirectoryRecordType", Tag(0x0004, 0x1430));
    public_tags.emplace("PrivateRecordUID", Tag(0x0004, 0x1432));
    public_tags.emplace("ReferencedFileID", Tag(0x0004, 0x1500));
    public_tags.emplace("MRDRDirectoryRecordOffset", Tag(0x0004, 0x1504));
    public_tags.emplace("ReferencedSOPClassUIDInFile", Tag(0x0004, 0x1510));
    public_tags.emplace("ReferencedSOPInstanceUIDInFile", Tag(0x0004, 0x1511));
    public_tags.emplace("ReferencedTransferSyntaxUIDInFile", Tag(0x0004, 0x1512));
    public_tags.emplace("ReferencedRelatedGeneralSOPClassUIDInFile", Tag(0x0004, 0x151a));
    public_tags.emplace("NumberOfReferences", Tag(0x0004, 0x1600));
}

}

}