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

void update_7fe0(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x7fe0, 0x0001), ElementsDictionaryEntry("Extended Offset Table", "ExtendedOffsetTable",  "OV", "1"));
    public_dictionary.emplace(Tag(0x7fe0, 0x0002), ElementsDictionaryEntry("Extended Offset Table Lengths", "ExtendedOffsetTableLengths",  "OV", "1"));
    public_dictionary.emplace(Tag(0x7fe0, 0x0008), ElementsDictionaryEntry("Float Pixel Data", "FloatPixelData",  "OF", "1"));
    public_dictionary.emplace(Tag(0x7fe0, 0x0009), ElementsDictionaryEntry("Double Float Pixel Data", "DoubleFloatPixelData",  "OD", "1"));
    public_dictionary.emplace(Tag(0x7fe0, 0x0010), ElementsDictionaryEntry("Pixel Data", "PixelData",  "OB or OW", "1"));
    public_dictionary.emplace(Tag(0x7fe0, 0x0020), ElementsDictionaryEntry("Coefficients SDVN", "CoefficientsSDVN",  "OW", "1"));
    public_dictionary.emplace(Tag(0x7fe0, 0x0030), ElementsDictionaryEntry("Coefficients SDHN", "CoefficientsSDHN",  "OW", "1"));
    public_dictionary.emplace(Tag(0x7fe0, 0x0040), ElementsDictionaryEntry("Coefficients SDDN", "CoefficientsSDDN",  "OW", "1"));

    public_tags.emplace("ExtendedOffsetTable", Tag(0x7fe0, 0x0001));
    public_tags.emplace("ExtendedOffsetTableLengths", Tag(0x7fe0, 0x0002));
    public_tags.emplace("FloatPixelData", Tag(0x7fe0, 0x0008));
    public_tags.emplace("DoubleFloatPixelData", Tag(0x7fe0, 0x0009));
    public_tags.emplace("PixelData", Tag(0x7fe0, 0x0010));
    public_tags.emplace("CoefficientsSDVN", Tag(0x7fe0, 0x0020));
    public_tags.emplace("CoefficientsSDHN", Tag(0x7fe0, 0x0030));
    public_tags.emplace("CoefficientsSDDN", Tag(0x7fe0, 0x0040));
}

}

}