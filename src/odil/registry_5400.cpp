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

void update_5400(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x5400, 0x0100), ElementsDictionaryEntry("Waveform Sequence", "WaveformSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x5400, 0x0110), ElementsDictionaryEntry("Channel Minimum Value", "ChannelMinimumValue",  "OB or OW", "1"));
    public_dictionary.emplace(Tag(0x5400, 0x0112), ElementsDictionaryEntry("Channel Maximum Value", "ChannelMaximumValue",  "OB or OW", "1"));
    public_dictionary.emplace(Tag(0x5400, 0x1004), ElementsDictionaryEntry("Waveform Bits Allocated", "WaveformBitsAllocated",  "US", "1"));
    public_dictionary.emplace(Tag(0x5400, 0x1006), ElementsDictionaryEntry("Waveform Sample Interpretation", "WaveformSampleInterpretation",  "CS", "1"));
    public_dictionary.emplace(Tag(0x5400, 0x100a), ElementsDictionaryEntry("Waveform Padding Value", "WaveformPaddingValue",  "OB or OW", "1"));
    public_dictionary.emplace(Tag(0x5400, 0x1010), ElementsDictionaryEntry("Waveform Data", "WaveformData",  "OB or OW", "1"));

    public_tags.emplace("WaveformSequence", Tag(0x5400, 0x0100));
    public_tags.emplace("ChannelMinimumValue", Tag(0x5400, 0x0110));
    public_tags.emplace("ChannelMaximumValue", Tag(0x5400, 0x0112));
    public_tags.emplace("WaveformBitsAllocated", Tag(0x5400, 0x1004));
    public_tags.emplace("WaveformSampleInterpretation", Tag(0x5400, 0x1006));
    public_tags.emplace("WaveformPaddingValue", Tag(0x5400, 0x100a));
    public_tags.emplace("WaveformData", Tag(0x5400, 0x1010));
}

}

}