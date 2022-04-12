/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0008
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0008

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const LengthToEnd(0x0008, 0x0001);
Tag const SpecificCharacterSet(0x0008, 0x0005);
Tag const LanguageCodeSequence(0x0008, 0x0006);
Tag const ImageType(0x0008, 0x0008);
Tag const RecognitionCode(0x0008, 0x0010);
Tag const InstanceCreationDate(0x0008, 0x0012);
Tag const InstanceCreationTime(0x0008, 0x0013);
Tag const InstanceCreatorUID(0x0008, 0x0014);
Tag const InstanceCoercionDateTime(0x0008, 0x0015);
Tag const SOPClassUID(0x0008, 0x0016);
Tag const AcquisitionUID(0x0008, 0x0017);
Tag const SOPInstanceUID(0x0008, 0x0018);
Tag const PyramidUID(0x0008, 0x0019);
Tag const RelatedGeneralSOPClassUID(0x0008, 0x001a);
Tag const OriginalSpecializedSOPClassUID(0x0008, 0x001b);
Tag const StudyDate(0x0008, 0x0020);
Tag const SeriesDate(0x0008, 0x0021);
Tag const AcquisitionDate(0x0008, 0x0022);
Tag const ContentDate(0x0008, 0x0023);
Tag const OverlayDate(0x0008, 0x0024);
Tag const CurveDate(0x0008, 0x0025);
Tag const AcquisitionDateTime(0x0008, 0x002a);
Tag const StudyTime(0x0008, 0x0030);
Tag const SeriesTime(0x0008, 0x0031);
Tag const AcquisitionTime(0x0008, 0x0032);
Tag const ContentTime(0x0008, 0x0033);
Tag const OverlayTime(0x0008, 0x0034);
Tag const CurveTime(0x0008, 0x0035);
Tag const DataSetType(0x0008, 0x0040);
Tag const DataSetSubtype(0x0008, 0x0041);
Tag const NuclearMedicineSeriesType(0x0008, 0x0042);
Tag const AccessionNumber(0x0008, 0x0050);
Tag const IssuerOfAccessionNumberSequence(0x0008, 0x0051);
Tag const QueryRetrieveLevel(0x0008, 0x0052);
Tag const QueryRetrieveView(0x0008, 0x0053);
Tag const RetrieveAETitle(0x0008, 0x0054);
Tag const StationAETitle(0x0008, 0x0055);
Tag const InstanceAvailability(0x0008, 0x0056);
Tag const FailedSOPInstanceUIDList(0x0008, 0x0058);
Tag const Modality(0x0008, 0x0060);
Tag const ModalitiesInStudy(0x0008, 0x0061);
Tag const SOPClassesInStudy(0x0008, 0x0062);
Tag const AnatomicRegionsInStudyCodeSequence(0x0008, 0x0063);
Tag const ConversionType(0x0008, 0x0064);
Tag const PresentationIntentType(0x0008, 0x0068);
Tag const Manufacturer(0x0008, 0x0070);
Tag const InstitutionName(0x0008, 0x0080);
Tag const InstitutionAddress(0x0008, 0x0081);
Tag const InstitutionCodeSequence(0x0008, 0x0082);
Tag const ReferringPhysicianName(0x0008, 0x0090);
Tag const ReferringPhysicianAddress(0x0008, 0x0092);
Tag const ReferringPhysicianTelephoneNumbers(0x0008, 0x0094);
Tag const ReferringPhysicianIdentificationSequence(0x0008, 0x0096);
Tag const ConsultingPhysicianName(0x0008, 0x009c);
Tag const ConsultingPhysicianIdentificationSequence(0x0008, 0x009d);
Tag const CodeValue(0x0008, 0x0100);
Tag const ExtendedCodeValue(0x0008, 0x0101);
Tag const CodingSchemeDesignator(0x0008, 0x0102);
Tag const CodingSchemeVersion(0x0008, 0x0103);
Tag const CodeMeaning(0x0008, 0x0104);
Tag const MappingResource(0x0008, 0x0105);
Tag const ContextGroupVersion(0x0008, 0x0106);
Tag const ContextGroupLocalVersion(0x0008, 0x0107);
Tag const ExtendedCodeMeaning(0x0008, 0x0108);
Tag const CodingSchemeResourcesSequence(0x0008, 0x0109);
Tag const CodingSchemeURLType(0x0008, 0x010a);
Tag const ContextGroupExtensionFlag(0x0008, 0x010b);
Tag const CodingSchemeUID(0x0008, 0x010c);
Tag const ContextGroupExtensionCreatorUID(0x0008, 0x010d);
Tag const CodingSchemeURL(0x0008, 0x010e);
Tag const ContextIdentifier(0x0008, 0x010f);
Tag const CodingSchemeIdentificationSequence(0x0008, 0x0110);
Tag const CodingSchemeRegistry(0x0008, 0x0112);
Tag const CodingSchemeExternalID(0x0008, 0x0114);
Tag const CodingSchemeName(0x0008, 0x0115);
Tag const CodingSchemeResponsibleOrganization(0x0008, 0x0116);
Tag const ContextUID(0x0008, 0x0117);
Tag const MappingResourceUID(0x0008, 0x0118);
Tag const LongCodeValue(0x0008, 0x0119);
Tag const URNCodeValue(0x0008, 0x0120);
Tag const EquivalentCodeSequence(0x0008, 0x0121);
Tag const MappingResourceName(0x0008, 0x0122);
Tag const ContextGroupIdentificationSequence(0x0008, 0x0123);
Tag const MappingResourceIdentificationSequence(0x0008, 0x0124);
Tag const TimezoneOffsetFromUTC(0x0008, 0x0201);
Tag const ResponsibleGroupCodeSequence(0x0008, 0x0220);
Tag const EquipmentModality(0x0008, 0x0221);
Tag const ManufacturerRelatedModelGroup(0x0008, 0x0222);
Tag const PrivateDataElementCharacteristicsSequence(0x0008, 0x0300);
Tag const PrivateGroupReference(0x0008, 0x0301);
Tag const PrivateCreatorReference(0x0008, 0x0302);
Tag const BlockIdentifyingInformationStatus(0x0008, 0x0303);
Tag const NonidentifyingPrivateElements(0x0008, 0x0304);
Tag const IdentifyingPrivateElements(0x0008, 0x0306);
Tag const DeidentificationActionSequence(0x0008, 0x0305);
Tag const DeidentificationAction(0x0008, 0x0307);
Tag const PrivateDataElement(0x0008, 0x0308);
Tag const PrivateDataElementValueMultiplicity(0x0008, 0x0309);
Tag const PrivateDataElementValueRepresentation(0x0008, 0x030a);
Tag const PrivateDataElementNumberOfItems(0x0008, 0x030b);
Tag const PrivateDataElementName(0x0008, 0x030c);
Tag const PrivateDataElementKeyword(0x0008, 0x030d);
Tag const PrivateDataElementDescription(0x0008, 0x030e);
Tag const PrivateDataElementEncoding(0x0008, 0x030f);
Tag const PrivateDataElementDefinitionSequence(0x0008, 0x0310);
Tag const NetworkID(0x0008, 0x1000);
Tag const StationName(0x0008, 0x1010);
Tag const StudyDescription(0x0008, 0x1030);
Tag const ProcedureCodeSequence(0x0008, 0x1032);
Tag const SeriesDescription(0x0008, 0x103e);
Tag const SeriesDescriptionCodeSequence(0x0008, 0x103f);
Tag const InstitutionalDepartmentName(0x0008, 0x1040);
Tag const InstitutionalDepartmentTypeCodeSequence(0x0008, 0x1041);
Tag const PhysiciansOfRecord(0x0008, 0x1048);
Tag const PhysiciansOfRecordIdentificationSequence(0x0008, 0x1049);
Tag const PerformingPhysicianName(0x0008, 0x1050);
Tag const PerformingPhysicianIdentificationSequence(0x0008, 0x1052);
Tag const NameOfPhysiciansReadingStudy(0x0008, 0x1060);
Tag const PhysiciansReadingStudyIdentificationSequence(0x0008, 0x1062);
Tag const OperatorsName(0x0008, 0x1070);
Tag const OperatorIdentificationSequence(0x0008, 0x1072);
Tag const AdmittingDiagnosesDescription(0x0008, 0x1080);
Tag const AdmittingDiagnosesCodeSequence(0x0008, 0x1084);
Tag const PyramidDescription(0x0008, 0x1088);
Tag const ManufacturerModelName(0x0008, 0x1090);
Tag const ReferencedResultsSequence(0x0008, 0x1100);
Tag const ReferencedStudySequence(0x0008, 0x1110);
Tag const ReferencedPerformedProcedureStepSequence(0x0008, 0x1111);
Tag const ReferencedSeriesSequence(0x0008, 0x1115);
Tag const ReferencedPatientSequence(0x0008, 0x1120);
Tag const ReferencedVisitSequence(0x0008, 0x1125);
Tag const ReferencedOverlaySequence(0x0008, 0x1130);
Tag const ReferencedStereometricInstanceSequence(0x0008, 0x1134);
Tag const ReferencedWaveformSequence(0x0008, 0x113a);
Tag const ReferencedImageSequence(0x0008, 0x1140);
Tag const ReferencedCurveSequence(0x0008, 0x1145);
Tag const ReferencedInstanceSequence(0x0008, 0x114a);
Tag const ReferencedRealWorldValueMappingInstanceSequence(0x0008, 0x114b);
Tag const ReferencedSOPClassUID(0x0008, 0x1150);
Tag const ReferencedSOPInstanceUID(0x0008, 0x1155);
Tag const DefinitionSourceSequence(0x0008, 0x1156);
Tag const SOPClassesSupported(0x0008, 0x115a);
Tag const ReferencedFrameNumber(0x0008, 0x1160);
Tag const SimpleFrameList(0x0008, 0x1161);
Tag const CalculatedFrameList(0x0008, 0x1162);
Tag const TimeRange(0x0008, 0x1163);
Tag const FrameExtractionSequence(0x0008, 0x1164);
Tag const MultiFrameSourceSOPInstanceUID(0x0008, 0x1167);
Tag const RetrieveURL(0x0008, 0x1190);
Tag const TransactionUID(0x0008, 0x1195);
Tag const WarningReason(0x0008, 0x1196);
Tag const FailureReason(0x0008, 0x1197);
Tag const FailedSOPSequence(0x0008, 0x1198);
Tag const ReferencedSOPSequence(0x0008, 0x1199);
Tag const OtherFailuresSequence(0x0008, 0x119a);
Tag const StudiesContainingOtherReferencedInstancesSequence(0x0008, 0x1200);
Tag const RelatedSeriesSequence(0x0008, 0x1250);
Tag const LossyImageCompressionRetired(0x0008, 0x2110);
Tag const DerivationDescription(0x0008, 0x2111);
Tag const SourceImageSequence(0x0008, 0x2112);
Tag const StageName(0x0008, 0x2120);
Tag const StageNumber(0x0008, 0x2122);
Tag const NumberOfStages(0x0008, 0x2124);
Tag const ViewName(0x0008, 0x2127);
Tag const ViewNumber(0x0008, 0x2128);
Tag const NumberOfEventTimers(0x0008, 0x2129);
Tag const NumberOfViewsInStage(0x0008, 0x212a);
Tag const EventElapsedTimes(0x0008, 0x2130);
Tag const EventTimerNames(0x0008, 0x2132);
Tag const EventTimerSequence(0x0008, 0x2133);
Tag const EventTimeOffset(0x0008, 0x2134);
Tag const EventCodeSequence(0x0008, 0x2135);
Tag const StartTrim(0x0008, 0x2142);
Tag const StopTrim(0x0008, 0x2143);
Tag const RecommendedDisplayFrameRate(0x0008, 0x2144);
Tag const TransducerPosition(0x0008, 0x2200);
Tag const TransducerOrientation(0x0008, 0x2204);
Tag const AnatomicStructure(0x0008, 0x2208);
Tag const AnatomicRegionSequence(0x0008, 0x2218);
Tag const AnatomicRegionModifierSequence(0x0008, 0x2220);
Tag const PrimaryAnatomicStructureSequence(0x0008, 0x2228);
Tag const AnatomicStructureSpaceOrRegionSequence(0x0008, 0x2229);
Tag const PrimaryAnatomicStructureModifierSequence(0x0008, 0x2230);
Tag const TransducerPositionSequence(0x0008, 0x2240);
Tag const TransducerPositionModifierSequence(0x0008, 0x2242);
Tag const TransducerOrientationSequence(0x0008, 0x2244);
Tag const TransducerOrientationModifierSequence(0x0008, 0x2246);
Tag const AnatomicStructureSpaceOrRegionCodeSequenceTrial(0x0008, 0x2251);
Tag const AnatomicPortalOfEntranceCodeSequenceTrial(0x0008, 0x2253);
Tag const AnatomicApproachDirectionCodeSequenceTrial(0x0008, 0x2255);
Tag const AnatomicPerspectiveDescriptionTrial(0x0008, 0x2256);
Tag const AnatomicPerspectiveCodeSequenceTrial(0x0008, 0x2257);
Tag const AnatomicLocationOfExaminingInstrumentDescriptionTrial(0x0008, 0x2258);
Tag const AnatomicLocationOfExaminingInstrumentCodeSequenceTrial(0x0008, 0x2259);
Tag const AnatomicStructureSpaceOrRegionModifierCodeSequenceTrial(0x0008, 0x225a);
Tag const OnAxisBackgroundAnatomicStructureCodeSequenceTrial(0x0008, 0x225c);
Tag const AlternateRepresentationSequence(0x0008, 0x3001);
Tag const AvailableTransferSyntaxUID(0x0008, 0x3002);
Tag const IrradiationEventUID(0x0008, 0x3010);
Tag const SourceIrradiationEventSequence(0x0008, 0x3011);
Tag const RadiopharmaceuticalAdministrationEventUID(0x0008, 0x3012);
Tag const IdentifyingComments(0x0008, 0x4000);
Tag const FrameType(0x0008, 0x9007);
Tag const ReferencedImageEvidenceSequence(0x0008, 0x9092);
Tag const ReferencedRawDataSequence(0x0008, 0x9121);
Tag const CreatorVersionUID(0x0008, 0x9123);
Tag const DerivationImageSequence(0x0008, 0x9124);
Tag const SourceImageEvidenceSequence(0x0008, 0x9154);
Tag const PixelPresentation(0x0008, 0x9205);
Tag const VolumetricProperties(0x0008, 0x9206);
Tag const VolumeBasedCalculationTechnique(0x0008, 0x9207);
Tag const ComplexImageComponent(0x0008, 0x9208);
Tag const AcquisitionContrast(0x0008, 0x9209);
Tag const DerivationCodeSequence(0x0008, 0x9215);
Tag const ReferencedPresentationStateSequence(0x0008, 0x9237);
Tag const ReferencedOtherPlaneSequence(0x0008, 0x9410);
Tag const FrameDisplaySequence(0x0008, 0x9458);
Tag const RecommendedDisplayFrameRateInFloat(0x0008, 0x9459);
Tag const SkipFrameRangeFlag(0x0008, 0x9460);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0008