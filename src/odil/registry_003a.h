/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_003a
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_003a

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const WaveformOriginality(0x003a, 0x0004);
Tag const NumberOfWaveformChannels(0x003a, 0x0005);
Tag const NumberOfWaveformSamples(0x003a, 0x0010);
Tag const SamplingFrequency(0x003a, 0x001a);
Tag const MultiplexGroupLabel(0x003a, 0x0020);
Tag const ChannelDefinitionSequence(0x003a, 0x0200);
Tag const WaveformChannelNumber(0x003a, 0x0202);
Tag const ChannelLabel(0x003a, 0x0203);
Tag const ChannelStatus(0x003a, 0x0205);
Tag const ChannelSourceSequence(0x003a, 0x0208);
Tag const ChannelSourceModifiersSequence(0x003a, 0x0209);
Tag const SourceWaveformSequence(0x003a, 0x020a);
Tag const ChannelDerivationDescription(0x003a, 0x020c);
Tag const ChannelSensitivity(0x003a, 0x0210);
Tag const ChannelSensitivityUnitsSequence(0x003a, 0x0211);
Tag const ChannelSensitivityCorrectionFactor(0x003a, 0x0212);
Tag const ChannelBaseline(0x003a, 0x0213);
Tag const ChannelTimeSkew(0x003a, 0x0214);
Tag const ChannelSampleSkew(0x003a, 0x0215);
Tag const ChannelOffset(0x003a, 0x0218);
Tag const WaveformBitsStored(0x003a, 0x021a);
Tag const FilterLowFrequency(0x003a, 0x0220);
Tag const FilterHighFrequency(0x003a, 0x0221);
Tag const NotchFilterFrequency(0x003a, 0x0222);
Tag const NotchFilterBandwidth(0x003a, 0x0223);
Tag const WaveformDataDisplayScale(0x003a, 0x0230);
Tag const WaveformDisplayBackgroundCIELabValue(0x003a, 0x0231);
Tag const WaveformPresentationGroupSequence(0x003a, 0x0240);
Tag const PresentationGroupNumber(0x003a, 0x0241);
Tag const ChannelDisplaySequence(0x003a, 0x0242);
Tag const ChannelRecommendedDisplayCIELabValue(0x003a, 0x0244);
Tag const ChannelPosition(0x003a, 0x0245);
Tag const DisplayShadingFlag(0x003a, 0x0246);
Tag const FractionalChannelDisplayScale(0x003a, 0x0247);
Tag const AbsoluteChannelDisplayScale(0x003a, 0x0248);
Tag const MultiplexedAudioChannelsDescriptionCodeSequence(0x003a, 0x0300);
Tag const ChannelIdentificationCode(0x003a, 0x0301);
Tag const ChannelMode(0x003a, 0x0302);
Tag const MultiplexGroupUID(0x003a, 0x0310);
Tag const PowerlineFrequency(0x003a, 0x0311);
Tag const ChannelImpedanceSequence(0x003a, 0x0312);
Tag const ImpedanceValue(0x003a, 0x0313);
Tag const ImpedanceMeasurementDateTime(0x003a, 0x0314);
Tag const ImpedanceMeasurementFrequency(0x003a, 0x0315);
Tag const ImpedanceMeasurementCurrentType(0x003a, 0x0316);
Tag const WaveformAmplifierType(0x003a, 0x0317);
Tag const FilterLowFrequencyCharacteristicsSequence(0x003a, 0x0318);
Tag const FilterHighFrequencyCharacteristicsSequence(0x003a, 0x0319);
Tag const SummarizedFilterLookupTable(0x003a, 0x0320);
Tag const NotchFilterCharacteristicsSequence(0x003a, 0x0321);
Tag const WaveformFilterType(0x003a, 0x0322);
Tag const AnalogFilterCharacteristicsSequence(0x003a, 0x0323);
Tag const AnalogFilterRollOff(0x003a, 0x0324);
Tag const AnalogFilterType(0x003a, 0x0325);
Tag const DigitalFilterCharacteristicsSequence(0x003a, 0x0326);
Tag const DigitalFilterOrder(0x003a, 0x0327);
Tag const DigitalFilterTypeCodeSequence(0x003a, 0x0328);
Tag const WaveformFilterDescription(0x003a, 0x0329);
Tag const FilterLookupTableSequence(0x003a, 0x032a);
Tag const FilterLookupTableDescription(0x003a, 0x032b);
Tag const FrequencyEncodingCodeSequence(0x003a, 0x032c);
Tag const MagnitudeEncodingCodeSequence(0x003a, 0x032d);
Tag const FilterLookupTableData(0x003a, 0x032e);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_003a