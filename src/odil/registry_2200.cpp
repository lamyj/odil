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

void update_2200(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x2200, 0x0001), ElementsDictionaryEntry("Label Using Information Extracted From Instances", "LabelUsingInformationExtractedFromInstances",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2200, 0x0002), ElementsDictionaryEntry("Label Text", "LabelText",  "UT", "1"));
    public_dictionary.emplace(Tag(0x2200, 0x0003), ElementsDictionaryEntry("Label Style Selection", "LabelStyleSelection",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2200, 0x0004), ElementsDictionaryEntry("Media Disposition", "MediaDisposition",  "LT", "1"));
    public_dictionary.emplace(Tag(0x2200, 0x0005), ElementsDictionaryEntry("Barcode Value", "BarcodeValue",  "LT", "1"));
    public_dictionary.emplace(Tag(0x2200, 0x0006), ElementsDictionaryEntry("Barcode Symbology", "BarcodeSymbology",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2200, 0x0007), ElementsDictionaryEntry("Allow Media Splitting", "AllowMediaSplitting",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2200, 0x0008), ElementsDictionaryEntry("Include Non-DICOM Objects", "IncludeNonDICOMObjects",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2200, 0x0009), ElementsDictionaryEntry("Include Display Application", "IncludeDisplayApplication",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2200, 0x000a), ElementsDictionaryEntry("Preserve Composite Instances After Media Creation", "PreserveCompositeInstancesAfterMediaCreation",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2200, 0x000b), ElementsDictionaryEntry("Total Number of Pieces of Media Created", "TotalNumberOfPiecesOfMediaCreated",  "US", "1"));
    public_dictionary.emplace(Tag(0x2200, 0x000c), ElementsDictionaryEntry("Requested Media Application Profile", "RequestedMediaApplicationProfile",  "LO", "1"));
    public_dictionary.emplace(Tag(0x2200, 0x000d), ElementsDictionaryEntry("Referenced Storage Media Sequence", "ReferencedStorageMediaSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2200, 0x000e), ElementsDictionaryEntry("Failure Attributes", "FailureAttributes",  "AT", "1-n"));
    public_dictionary.emplace(Tag(0x2200, 0x000f), ElementsDictionaryEntry("Allow Lossy Compression", "AllowLossyCompression",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2200, 0x0020), ElementsDictionaryEntry("Request Priority", "RequestPriority",  "CS", "1"));

    public_tags.emplace("LabelUsingInformationExtractedFromInstances", Tag(0x2200, 0x0001));
    public_tags.emplace("LabelText", Tag(0x2200, 0x0002));
    public_tags.emplace("LabelStyleSelection", Tag(0x2200, 0x0003));
    public_tags.emplace("MediaDisposition", Tag(0x2200, 0x0004));
    public_tags.emplace("BarcodeValue", Tag(0x2200, 0x0005));
    public_tags.emplace("BarcodeSymbology", Tag(0x2200, 0x0006));
    public_tags.emplace("AllowMediaSplitting", Tag(0x2200, 0x0007));
    public_tags.emplace("IncludeNonDICOMObjects", Tag(0x2200, 0x0008));
    public_tags.emplace("IncludeDisplayApplication", Tag(0x2200, 0x0009));
    public_tags.emplace("PreserveCompositeInstancesAfterMediaCreation", Tag(0x2200, 0x000a));
    public_tags.emplace("TotalNumberOfPiecesOfMediaCreated", Tag(0x2200, 0x000b));
    public_tags.emplace("RequestedMediaApplicationProfile", Tag(0x2200, 0x000c));
    public_tags.emplace("ReferencedStorageMediaSequence", Tag(0x2200, 0x000d));
    public_tags.emplace("FailureAttributes", Tag(0x2200, 0x000e));
    public_tags.emplace("AllowLossyCompression", Tag(0x2200, 0x000f));
    public_tags.emplace("RequestPriority", Tag(0x2200, 0x0020));
}

}

}