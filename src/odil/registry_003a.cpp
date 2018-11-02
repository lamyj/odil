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

void update_003a(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x003a, 0x0004), ElementsDictionaryEntry("Waveform Originality", "WaveformOriginality",  "CS", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0005), ElementsDictionaryEntry("Number of Waveform Channels", "NumberOfWaveformChannels",  "US", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0010), ElementsDictionaryEntry("Number of Waveform Samples", "NumberOfWaveformSamples",  "UL", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x001a), ElementsDictionaryEntry("Sampling Frequency", "SamplingFrequency",  "DS", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0020), ElementsDictionaryEntry("Multiplex Group Label", "MultiplexGroupLabel",  "SH", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0200), ElementsDictionaryEntry("Channel Definition Sequence", "ChannelDefinitionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0202), ElementsDictionaryEntry("Waveform Channel Number", "WaveformChannelNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0203), ElementsDictionaryEntry("Channel Label", "ChannelLabel",  "SH", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0205), ElementsDictionaryEntry("Channel Status", "ChannelStatus",  "CS", "1-n"));
    public_dictionary.emplace(Tag(0x003a, 0x0208), ElementsDictionaryEntry("Channel Source Sequence", "ChannelSourceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0209), ElementsDictionaryEntry("Channel Source Modifiers Sequence", "ChannelSourceModifiersSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x020a), ElementsDictionaryEntry("Source Waveform Sequence", "SourceWaveformSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x020c), ElementsDictionaryEntry("Channel Derivation Description", "ChannelDerivationDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0210), ElementsDictionaryEntry("Channel Sensitivity", "ChannelSensitivity",  "DS", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0211), ElementsDictionaryEntry("Channel Sensitivity Units Sequence", "ChannelSensitivityUnitsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0212), ElementsDictionaryEntry("Channel Sensitivity Correction Factor", "ChannelSensitivityCorrectionFactor",  "DS", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0213), ElementsDictionaryEntry("Channel Baseline", "ChannelBaseline",  "DS", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0214), ElementsDictionaryEntry("Channel Time Skew", "ChannelTimeSkew",  "DS", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0215), ElementsDictionaryEntry("Channel Sample Skew", "ChannelSampleSkew",  "DS", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0218), ElementsDictionaryEntry("Channel Offset", "ChannelOffset",  "DS", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x021a), ElementsDictionaryEntry("Waveform Bits Stored", "WaveformBitsStored",  "US", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0220), ElementsDictionaryEntry("Filter Low Frequency", "FilterLowFrequency",  "DS", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0221), ElementsDictionaryEntry("Filter High Frequency", "FilterHighFrequency",  "DS", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0222), ElementsDictionaryEntry("Notch Filter Frequency", "NotchFilterFrequency",  "DS", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0223), ElementsDictionaryEntry("Notch Filter Bandwidth", "NotchFilterBandwidth",  "DS", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0230), ElementsDictionaryEntry("Waveform Data Display Scale", "WaveformDataDisplayScale",  "FL", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0231), ElementsDictionaryEntry("Waveform Display Background CIELab Value", "WaveformDisplayBackgroundCIELabValue",  "US", "3"));
    public_dictionary.emplace(Tag(0x003a, 0x0240), ElementsDictionaryEntry("Waveform Presentation Group Sequence", "WaveformPresentationGroupSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0241), ElementsDictionaryEntry("Presentation Group Number", "PresentationGroupNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0242), ElementsDictionaryEntry("Channel Display Sequence", "ChannelDisplaySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0244), ElementsDictionaryEntry("Channel Recommended Display CIELab Value", "ChannelRecommendedDisplayCIELabValue",  "US", "3"));
    public_dictionary.emplace(Tag(0x003a, 0x0245), ElementsDictionaryEntry("Channel Position", "ChannelPosition",  "FL", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0246), ElementsDictionaryEntry("Display Shading Flag", "DisplayShadingFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0247), ElementsDictionaryEntry("Fractional Channel Display Scale", "FractionalChannelDisplayScale",  "FL", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0248), ElementsDictionaryEntry("Absolute Channel Display Scale", "AbsoluteChannelDisplayScale",  "FL", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0300), ElementsDictionaryEntry("Multiplexed Audio Channels Description Code Sequence", "MultiplexedAudioChannelsDescriptionCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0301), ElementsDictionaryEntry("Channel Identification Code", "ChannelIdentificationCode",  "IS", "1"));
    public_dictionary.emplace(Tag(0x003a, 0x0302), ElementsDictionaryEntry("Channel Mode", "ChannelMode",  "CS", "1"));

    public_tags.emplace("WaveformOriginality", Tag(0x003a, 0x0004));
    public_tags.emplace("NumberOfWaveformChannels", Tag(0x003a, 0x0005));
    public_tags.emplace("NumberOfWaveformSamples", Tag(0x003a, 0x0010));
    public_tags.emplace("SamplingFrequency", Tag(0x003a, 0x001a));
    public_tags.emplace("MultiplexGroupLabel", Tag(0x003a, 0x0020));
    public_tags.emplace("ChannelDefinitionSequence", Tag(0x003a, 0x0200));
    public_tags.emplace("WaveformChannelNumber", Tag(0x003a, 0x0202));
    public_tags.emplace("ChannelLabel", Tag(0x003a, 0x0203));
    public_tags.emplace("ChannelStatus", Tag(0x003a, 0x0205));
    public_tags.emplace("ChannelSourceSequence", Tag(0x003a, 0x0208));
    public_tags.emplace("ChannelSourceModifiersSequence", Tag(0x003a, 0x0209));
    public_tags.emplace("SourceWaveformSequence", Tag(0x003a, 0x020a));
    public_tags.emplace("ChannelDerivationDescription", Tag(0x003a, 0x020c));
    public_tags.emplace("ChannelSensitivity", Tag(0x003a, 0x0210));
    public_tags.emplace("ChannelSensitivityUnitsSequence", Tag(0x003a, 0x0211));
    public_tags.emplace("ChannelSensitivityCorrectionFactor", Tag(0x003a, 0x0212));
    public_tags.emplace("ChannelBaseline", Tag(0x003a, 0x0213));
    public_tags.emplace("ChannelTimeSkew", Tag(0x003a, 0x0214));
    public_tags.emplace("ChannelSampleSkew", Tag(0x003a, 0x0215));
    public_tags.emplace("ChannelOffset", Tag(0x003a, 0x0218));
    public_tags.emplace("WaveformBitsStored", Tag(0x003a, 0x021a));
    public_tags.emplace("FilterLowFrequency", Tag(0x003a, 0x0220));
    public_tags.emplace("FilterHighFrequency", Tag(0x003a, 0x0221));
    public_tags.emplace("NotchFilterFrequency", Tag(0x003a, 0x0222));
    public_tags.emplace("NotchFilterBandwidth", Tag(0x003a, 0x0223));
    public_tags.emplace("WaveformDataDisplayScale", Tag(0x003a, 0x0230));
    public_tags.emplace("WaveformDisplayBackgroundCIELabValue", Tag(0x003a, 0x0231));
    public_tags.emplace("WaveformPresentationGroupSequence", Tag(0x003a, 0x0240));
    public_tags.emplace("PresentationGroupNumber", Tag(0x003a, 0x0241));
    public_tags.emplace("ChannelDisplaySequence", Tag(0x003a, 0x0242));
    public_tags.emplace("ChannelRecommendedDisplayCIELabValue", Tag(0x003a, 0x0244));
    public_tags.emplace("ChannelPosition", Tag(0x003a, 0x0245));
    public_tags.emplace("DisplayShadingFlag", Tag(0x003a, 0x0246));
    public_tags.emplace("FractionalChannelDisplayScale", Tag(0x003a, 0x0247));
    public_tags.emplace("AbsoluteChannelDisplayScale", Tag(0x003a, 0x0248));
    public_tags.emplace("MultiplexedAudioChannelsDescriptionCodeSequence", Tag(0x003a, 0x0300));
    public_tags.emplace("ChannelIdentificationCode", Tag(0x003a, 0x0301));
    public_tags.emplace("ChannelMode", Tag(0x003a, 0x0302));
}

}

}