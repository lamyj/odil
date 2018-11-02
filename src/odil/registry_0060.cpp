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

void update_0060(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0060, 0x3000), ElementsDictionaryEntry("Histogram Sequence", "HistogramSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0060, 0x3002), ElementsDictionaryEntry("Histogram Number of Bins", "HistogramNumberOfBins",  "US", "1"));
    public_dictionary.emplace(Tag(0x0060, 0x3004), ElementsDictionaryEntry("Histogram First Bin Value", "HistogramFirstBinValue",  "US or SS", "1"));
    public_dictionary.emplace(Tag(0x0060, 0x3006), ElementsDictionaryEntry("Histogram Last Bin Value", "HistogramLastBinValue",  "US or SS", "1"));
    public_dictionary.emplace(Tag(0x0060, 0x3008), ElementsDictionaryEntry("Histogram Bin Width", "HistogramBinWidth",  "US", "1"));
    public_dictionary.emplace(Tag(0x0060, 0x3010), ElementsDictionaryEntry("Histogram Explanation", "HistogramExplanation",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0060, 0x3020), ElementsDictionaryEntry("Histogram Data", "HistogramData",  "UL", "1-n"));

    public_tags.emplace("HistogramSequence", Tag(0x0060, 0x3000));
    public_tags.emplace("HistogramNumberOfBins", Tag(0x0060, 0x3002));
    public_tags.emplace("HistogramFirstBinValue", Tag(0x0060, 0x3004));
    public_tags.emplace("HistogramLastBinValue", Tag(0x0060, 0x3006));
    public_tags.emplace("HistogramBinWidth", Tag(0x0060, 0x3008));
    public_tags.emplace("HistogramExplanation", Tag(0x0060, 0x3010));
    public_tags.emplace("HistogramData", Tag(0x0060, 0x3020));
}

}

}