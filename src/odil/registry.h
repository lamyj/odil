/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/ElementsDictionary.h"
#include "odil/Tag.h"
#include "odil/UIDsDictionary.h"

#include "odil/registry_0000.h"
#include "odil/registry_0002.h"
#include "odil/registry_0004.h"
#include "odil/registry_0008.h"
#include "odil/registry_0010.h"
#include "odil/registry_0012.h"
#include "odil/registry_0014.h"
#include "odil/registry_0016.h"
#include "odil/registry_0018.h"
#include "odil/registry_0020.h"
#include "odil/registry_misc.h"
#include "odil/registry_0022.h"
#include "odil/registry_0024.h"
#include "odil/registry_0028.h"
#include "odil/registry_0032.h"
#include "odil/registry_0034.h"
#include "odil/registry_0038.h"
#include "odil/registry_003a.h"
#include "odil/registry_0040.h"
#include "odil/registry_0042.h"
#include "odil/registry_0044.h"
#include "odil/registry_0046.h"
#include "odil/registry_0048.h"
#include "odil/registry_0050.h"
#include "odil/registry_0052.h"
#include "odil/registry_0054.h"
#include "odil/registry_0060.h"
#include "odil/registry_0062.h"
#include "odil/registry_0064.h"
#include "odil/registry_0066.h"
#include "odil/registry_0068.h"
#include "odil/registry_0070.h"
#include "odil/registry_0072.h"
#include "odil/registry_0074.h"
#include "odil/registry_0076.h"
#include "odil/registry_0078.h"
#include "odil/registry_0080.h"
#include "odil/registry_0082.h"
#include "odil/registry_0088.h"
#include "odil/registry_0100.h"
#include "odil/registry_0400.h"
#include "odil/registry_2000.h"
#include "odil/registry_2010.h"
#include "odil/registry_2020.h"
#include "odil/registry_2030.h"
#include "odil/registry_2040.h"
#include "odil/registry_2050.h"
#include "odil/registry_2100.h"
#include "odil/registry_2110.h"
#include "odil/registry_2120.h"
#include "odil/registry_2130.h"
#include "odil/registry_2200.h"
#include "odil/registry_3002.h"
#include "odil/registry_3004.h"
#include "odil/registry_3006.h"
#include "odil/registry_3008.h"
#include "odil/registry_300a.h"
#include "odil/registry_300c.h"
#include "odil/registry_300e.h"
#include "odil/registry_3010.h"
#include "odil/registry_4000.h"
#include "odil/registry_4008.h"
#include "odil/registry_4010.h"
#include "odil/registry_4ffe.h"
#include "odil/registry_5200.h"
#include "odil/registry_5400.h"
#include "odil/registry_5600.h"
#include "odil/registry_7fe0.h"
#include "odil/registry_fffa.h"
#include "odil/registry_fffc.h"
#include "odil/registry_fffe.h"

namespace odil
{

namespace registry
{

std::string const Verification("1.2.840.10008.1.1");
std::string const VerificationSOPClass("1.2.840.10008.1.1");
std::string const ImplicitVRLittleEndian("1.2.840.10008.1.2");
std::string const ExplicitVRLittleEndian("1.2.840.10008.1.2.1");
std::string const DeflatedExplicitVRLittleEndian("1.2.840.10008.1.2.1.99");
std::string const ExplicitVRBigEndian("1.2.840.10008.1.2.2");
std::string const ExplicitVRBigEndian_Retired("1.2.840.10008.1.2.2");
std::string const JPEGBaseline8Bit("1.2.840.10008.1.2.4.50");
std::string const JPEGBaselineProcess1("1.2.840.10008.1.2.4.50");
std::string const JPEGExtended12Bit("1.2.840.10008.1.2.4.51");
std::string const JPEGExtendedProcess24("1.2.840.10008.1.2.4.51");
std::string const JPEGExtended35("1.2.840.10008.1.2.4.52");
std::string const JPEGExtendedProcess35_Retired("1.2.840.10008.1.2.4.52");
std::string const JPEGSpectralSelectionNonHierarchical68("1.2.840.10008.1.2.4.53");
std::string const JPEGSpectralSelectionNonHierarchicalProcess68_Retired("1.2.840.10008.1.2.4.53");
std::string const JPEGSpectralSelectionNonHierarchical79("1.2.840.10008.1.2.4.54");
std::string const JPEGSpectralSelectionNonHierarchicalProcess79_Retired("1.2.840.10008.1.2.4.54");
std::string const JPEGFullProgressionNonHierarchical1012("1.2.840.10008.1.2.4.55");
std::string const JPEGFullProgressionNonHierarchicalProcess1012_Retired("1.2.840.10008.1.2.4.55");
std::string const JPEGFullProgressionNonHierarchical1113("1.2.840.10008.1.2.4.56");
std::string const JPEGFullProgressionNonHierarchicalProcess1113_Retired("1.2.840.10008.1.2.4.56");
std::string const JPEGLossless("1.2.840.10008.1.2.4.57");
std::string const JPEGLosslessNonHierarchicalProcess14("1.2.840.10008.1.2.4.57");
std::string const JPEGLosslessNonHierarchical15("1.2.840.10008.1.2.4.58");
std::string const JPEGLosslessNonHierarchicalProcess15_Retired("1.2.840.10008.1.2.4.58");
std::string const JPEGExtendedHierarchical1618("1.2.840.10008.1.2.4.59");
std::string const JPEGExtendedHierarchicalProcess1618_Retired("1.2.840.10008.1.2.4.59");
std::string const JPEGExtendedHierarchical1719("1.2.840.10008.1.2.4.60");
std::string const JPEGExtendedHierarchicalProcess1719_Retired("1.2.840.10008.1.2.4.60");
std::string const JPEGSpectralSelectionHierarchical2022("1.2.840.10008.1.2.4.61");
std::string const JPEGSpectralSelectionHierarchicalProcess2022_Retired("1.2.840.10008.1.2.4.61");
std::string const JPEGSpectralSelectionHierarchical2123("1.2.840.10008.1.2.4.62");
std::string const JPEGSpectralSelectionHierarchicalProcess2123_Retired("1.2.840.10008.1.2.4.62");
std::string const JPEGFullProgressionHierarchical2426("1.2.840.10008.1.2.4.63");
std::string const JPEGFullProgressionHierarchicalProcess2426_Retired("1.2.840.10008.1.2.4.63");
std::string const JPEGFullProgressionHierarchical2527("1.2.840.10008.1.2.4.64");
std::string const JPEGFullProgressionHierarchicalProcess2527_Retired("1.2.840.10008.1.2.4.64");
std::string const JPEGLosslessHierarchical28("1.2.840.10008.1.2.4.65");
std::string const JPEGLosslessHierarchicalProcess28_Retired("1.2.840.10008.1.2.4.65");
std::string const JPEGLosslessHierarchical29("1.2.840.10008.1.2.4.66");
std::string const JPEGLosslessHierarchicalProcess29_Retired("1.2.840.10008.1.2.4.66");
std::string const JPEGLosslessSV1("1.2.840.10008.1.2.4.70");
std::string const JPEGLosslessNonHierarchicalFirstOrderPredictionProcess14SelectionValue1("1.2.840.10008.1.2.4.70");
std::string const JPEGLSLossless("1.2.840.10008.1.2.4.80");
std::string const JPEGLSLosslessImageCompression("1.2.840.10008.1.2.4.80");
std::string const JPEGLSNearLossless("1.2.840.10008.1.2.4.81");
std::string const JPEGLSLossyNearLosslessImageCompression("1.2.840.10008.1.2.4.81");
std::string const JPEG2000Lossless("1.2.840.10008.1.2.4.90");
std::string const JPEG2000ImageCompressionLosslessOnly("1.2.840.10008.1.2.4.90");
std::string const JPEG2000("1.2.840.10008.1.2.4.91");
std::string const JPEG2000ImageCompression("1.2.840.10008.1.2.4.91");
std::string const JPEG2000MCLossless("1.2.840.10008.1.2.4.92");
std::string const JPEG2000Part2MulticomponentImageCompressionLosslessOnly("1.2.840.10008.1.2.4.92");
std::string const JPEG2000MC("1.2.840.10008.1.2.4.93");
std::string const JPEG2000Part2MulticomponentImageCompression("1.2.840.10008.1.2.4.93");
std::string const JPIPReferenced("1.2.840.10008.1.2.4.94");
std::string const JPIPReferencedDeflate("1.2.840.10008.1.2.4.95");
std::string const MPEG2MPML("1.2.840.10008.1.2.4.100");
std::string const MPEG2MainProfileMainLevel("1.2.840.10008.1.2.4.100");
std::string const MPEG2MPHL("1.2.840.10008.1.2.4.101");
std::string const MPEG2MainProfileHighLevel("1.2.840.10008.1.2.4.101");
std::string const MPEG4HP41("1.2.840.10008.1.2.4.102");
std::string const MPEG4AVCH264HighProfileLevel41("1.2.840.10008.1.2.4.102");
std::string const MPEG4HP41BD("1.2.840.10008.1.2.4.103");
std::string const MPEG4AVCH264BDcompatibleHighProfileLevel41("1.2.840.10008.1.2.4.103");
std::string const MPEG4HP422D("1.2.840.10008.1.2.4.104");
std::string const MPEG4AVCH264HighProfileLevel42For2DVideo("1.2.840.10008.1.2.4.104");
std::string const MPEG4HP423D("1.2.840.10008.1.2.4.105");
std::string const MPEG4AVCH264HighProfileLevel42For3DVideo("1.2.840.10008.1.2.4.105");
std::string const MPEG4HP42STEREO("1.2.840.10008.1.2.4.106");
std::string const MPEG4AVCH264StereoHighProfileLevel42("1.2.840.10008.1.2.4.106");
std::string const HEVCMP51("1.2.840.10008.1.2.4.107");
std::string const HEVCH265MainProfileLevel51("1.2.840.10008.1.2.4.107");
std::string const HEVCM10P51("1.2.840.10008.1.2.4.108");
std::string const HEVCH265Main10ProfileLevel51("1.2.840.10008.1.2.4.108");
std::string const RLELossless("1.2.840.10008.1.2.5");
std::string const RFC2557MIMEEncapsulation("1.2.840.10008.1.2.6.1");
std::string const RFC2557MIMEencapsulation_Retired("1.2.840.10008.1.2.6.1");
std::string const XMLEncoding("1.2.840.10008.1.2.6.2");
std::string const XMLEncoding_Retired("1.2.840.10008.1.2.6.2");
std::string const SMPTEST211020UncompressedProgressiveActiveVideo("1.2.840.10008.1.2.7.1");
std::string const SMPTEST211020UncompressedInterlacedActiveVideo("1.2.840.10008.1.2.7.2");
std::string const SMPTEST211030PCMDigitalAudio("1.2.840.10008.1.2.7.3");
std::string const MediaStorageDirectoryStorage("1.2.840.10008.1.3.10");
std::string const TalairachBrainAtlas("1.2.840.10008.1.4.1.1");
std::string const TalairachBrainAtlasFrameofReference("1.2.840.10008.1.4.1.1");
std::string const SPM2T1("1.2.840.10008.1.4.1.2");
std::string const SPM2T1FrameofReference("1.2.840.10008.1.4.1.2");
std::string const SPM2T2("1.2.840.10008.1.4.1.3");
std::string const SPM2T2FrameofReference("1.2.840.10008.1.4.1.3");
std::string const SPM2PD("1.2.840.10008.1.4.1.4");
std::string const SPM2PDFrameofReference("1.2.840.10008.1.4.1.4");
std::string const SPM2EPI("1.2.840.10008.1.4.1.5");
std::string const SPM2EPIFrameofReference("1.2.840.10008.1.4.1.5");
std::string const SPM2FILT1("1.2.840.10008.1.4.1.6");
std::string const SPM2FILT1FrameofReference("1.2.840.10008.1.4.1.6");
std::string const SPM2PET("1.2.840.10008.1.4.1.7");
std::string const SPM2PETFrameofReference("1.2.840.10008.1.4.1.7");
std::string const SPM2TRANSM("1.2.840.10008.1.4.1.8");
std::string const SPM2TRANSMFrameofReference("1.2.840.10008.1.4.1.8");
std::string const SPM2SPECT("1.2.840.10008.1.4.1.9");
std::string const SPM2SPECTFrameofReference("1.2.840.10008.1.4.1.9");
std::string const SPM2GRAY("1.2.840.10008.1.4.1.10");
std::string const SPM2GRAYFrameofReference("1.2.840.10008.1.4.1.10");
std::string const SPM2WHITE("1.2.840.10008.1.4.1.11");
std::string const SPM2WHITEFrameofReference("1.2.840.10008.1.4.1.11");
std::string const SPM2CSF("1.2.840.10008.1.4.1.12");
std::string const SPM2CSFFrameofReference("1.2.840.10008.1.4.1.12");
std::string const SPM2BRAINMASK("1.2.840.10008.1.4.1.13");
std::string const SPM2BRAINMASKFrameofReference("1.2.840.10008.1.4.1.13");
std::string const SPM2AVG305T1("1.2.840.10008.1.4.1.14");
std::string const SPM2AVG305T1FrameofReference("1.2.840.10008.1.4.1.14");
std::string const SPM2AVG152T1("1.2.840.10008.1.4.1.15");
std::string const SPM2AVG152T1FrameofReference("1.2.840.10008.1.4.1.15");
std::string const SPM2AVG152T2("1.2.840.10008.1.4.1.16");
std::string const SPM2AVG152T2FrameofReference("1.2.840.10008.1.4.1.16");
std::string const SPM2AVG152PD("1.2.840.10008.1.4.1.17");
std::string const SPM2AVG152PDFrameofReference("1.2.840.10008.1.4.1.17");
std::string const SPM2SINGLESUBJT1("1.2.840.10008.1.4.1.18");
std::string const SPM2SINGLESUBJT1FrameofReference("1.2.840.10008.1.4.1.18");
std::string const ICBM452T1("1.2.840.10008.1.4.2.1");
std::string const ICBM452T1FrameofReference("1.2.840.10008.1.4.2.1");
std::string const ICBMSingleSubjectMRI("1.2.840.10008.1.4.2.2");
std::string const ICBMSingleSubjectMRIFrameofReference("1.2.840.10008.1.4.2.2");
std::string const IEC61217FixedCoordinateSystem("1.2.840.10008.1.4.3.1");
std::string const IEC61217FixedCoordinateSystemFrameofReference("1.2.840.10008.1.4.3.1");
std::string const StandardRoboticArmCoordinateSystem("1.2.840.10008.1.4.3.2");
std::string const StandardRoboticArmCoordinateSystemFrameofReference("1.2.840.10008.1.4.3.2");
std::string const SRI24("1.2.840.10008.1.4.4.1");
std::string const SRI24FrameofReference("1.2.840.10008.1.4.4.1");
std::string const Colin27("1.2.840.10008.1.4.5.1");
std::string const Colin27FrameofReference("1.2.840.10008.1.4.5.1");
std::string const LPBA40AIR("1.2.840.10008.1.4.6.1");
std::string const LPBA40AIRFrameofReference("1.2.840.10008.1.4.6.1");
std::string const LPBA40FLIRT("1.2.840.10008.1.4.6.2");
std::string const LPBA40FLIRTFrameofReference("1.2.840.10008.1.4.6.2");
std::string const LPBA40SPM5("1.2.840.10008.1.4.6.3");
std::string const LPBA40SPM5FrameofReference("1.2.840.10008.1.4.6.3");
std::string const HotIronPalette("1.2.840.10008.1.5.1");
std::string const HotIronColorPaletteSOPInstance("1.2.840.10008.1.5.1");
std::string const PETPalette("1.2.840.10008.1.5.2");
std::string const PETColorPaletteSOPInstance("1.2.840.10008.1.5.2");
std::string const HotMetalBluePalette("1.2.840.10008.1.5.3");
std::string const HotMetalBlueColorPaletteSOPInstance("1.2.840.10008.1.5.3");
std::string const PET20StepPalette("1.2.840.10008.1.5.4");
std::string const PET20StepColorPaletteSOPInstance("1.2.840.10008.1.5.4");
std::string const SpringPalette("1.2.840.10008.1.5.5");
std::string const SpringColorPaletteSOPInstance("1.2.840.10008.1.5.5");
std::string const SummerPalette("1.2.840.10008.1.5.6");
std::string const SummerColorPaletteSOPInstance("1.2.840.10008.1.5.6");
std::string const FallPalette("1.2.840.10008.1.5.7");
std::string const FallColorPaletteSOPInstance("1.2.840.10008.1.5.7");
std::string const WinterPalette("1.2.840.10008.1.5.8");
std::string const WinterColorPaletteSOPInstance("1.2.840.10008.1.5.8");
std::string const BasicStudyContentNotification("1.2.840.10008.1.9");
std::string const BasicStudyContentNotificationSOPClass_Retired("1.2.840.10008.1.9");
std::string const Papyrus3ImplicitVRLittleEndian("1.2.840.10008.1.20");
std::string const Papyrus3ImplicitVRLittleEndian_Retired("1.2.840.10008.1.20");
std::string const StorageCommitmentPushModel("1.2.840.10008.1.20.1");
std::string const StorageCommitmentPushModelSOPClass("1.2.840.10008.1.20.1");
std::string const StorageCommitmentPushModelInstance("1.2.840.10008.1.20.1.1");
std::string const StorageCommitmentPushModelSOPInstance("1.2.840.10008.1.20.1.1");
std::string const StorageCommitmentPullModel("1.2.840.10008.1.20.2");
std::string const StorageCommitmentPullModelSOPClass_Retired("1.2.840.10008.1.20.2");
std::string const StorageCommitmentPullModelInstance("1.2.840.10008.1.20.2.1");
std::string const StorageCommitmentPullModelSOPInstance_Retired("1.2.840.10008.1.20.2.1");
std::string const ProceduralEventLogging("1.2.840.10008.1.40");
std::string const ProceduralEventLoggingSOPClass("1.2.840.10008.1.40");
std::string const ProceduralEventLoggingInstance("1.2.840.10008.1.40.1");
std::string const ProceduralEventLoggingSOPInstance("1.2.840.10008.1.40.1");
std::string const SubstanceAdministrationLogging("1.2.840.10008.1.42");
std::string const SubstanceAdministrationLoggingSOPClass("1.2.840.10008.1.42");
std::string const SubstanceAdministrationLoggingInstance("1.2.840.10008.1.42.1");
std::string const SubstanceAdministrationLoggingSOPInstance("1.2.840.10008.1.42.1");
std::string const DCMUID("1.2.840.10008.2.6.1");
std::string const DICOMUIDRegistry("1.2.840.10008.2.6.1");
std::string const DCM("1.2.840.10008.2.16.4");
std::string const DICOMControlledTerminology("1.2.840.10008.2.16.4");
std::string const MA("1.2.840.10008.2.16.5");
std::string const AdultMouseAnatomyOntology("1.2.840.10008.2.16.5");
std::string const UBERON("1.2.840.10008.2.16.6");
std::string const UberonOntology("1.2.840.10008.2.16.6");
std::string const ITIS_TSN("1.2.840.10008.2.16.7");
std::string const IntegratedTaxonomicInformationSystemITISTaxonomicSerialNumberTSN("1.2.840.10008.2.16.7");
std::string const MGI("1.2.840.10008.2.16.8");
std::string const MouseGenomeInitiativeMGI("1.2.840.10008.2.16.8");
std::string const PUBCHEM_CID("1.2.840.10008.2.16.9");
std::string const PubChemCompoundCID("1.2.840.10008.2.16.9");
std::string const DC("1.2.840.10008.2.16.10");
std::string const DublinCore("1.2.840.10008.2.16.10");
std::string const NYUMCCG("1.2.840.10008.2.16.11");
std::string const NewYorkUniversityMelanomaClinicalCooperativeGroup("1.2.840.10008.2.16.11");
std::string const MAYONRISBSASRG("1.2.840.10008.2.16.12");
std::string const MayoClinicNonradiologicalImagesSpecificBodyStructureAnatomicalSurfaceRegionGuide("1.2.840.10008.2.16.12");
std::string const IBSI("1.2.840.10008.2.16.13");
std::string const ImageBiomarkerStandardisationInitiative("1.2.840.10008.2.16.13");
std::string const RO("1.2.840.10008.2.16.14");
std::string const RadiomicsOntology("1.2.840.10008.2.16.14");
std::string const RADELEMENT("1.2.840.10008.2.16.15");
std::string const RadElement("1.2.840.10008.2.16.15");
std::string const I11("1.2.840.10008.2.16.16");
std::string const ICD11("1.2.840.10008.2.16.16");
std::string const DICOMApplicationContext("1.2.840.10008.3.1.1.1");
std::string const DICOMApplicationContextName("1.2.840.10008.3.1.1.1");
std::string const DetachedPatientManagement("1.2.840.10008.3.1.2.1.1");
std::string const DetachedPatientManagementSOPClass_Retired("1.2.840.10008.3.1.2.1.1");
std::string const DetachedPatientManagementMeta("1.2.840.10008.3.1.2.1.4");
std::string const DetachedPatientManagementMetaSOPClass_Retired("1.2.840.10008.3.1.2.1.4");
std::string const DetachedVisitManagement("1.2.840.10008.3.1.2.2.1");
std::string const DetachedVisitManagementSOPClass_Retired("1.2.840.10008.3.1.2.2.1");
std::string const DetachedStudyManagement("1.2.840.10008.3.1.2.3.1");
std::string const DetachedStudyManagementSOPClass_Retired("1.2.840.10008.3.1.2.3.1");
std::string const StudyComponentManagement("1.2.840.10008.3.1.2.3.2");
std::string const StudyComponentManagementSOPClass_Retired("1.2.840.10008.3.1.2.3.2");
std::string const ModalityPerformedProcedureStep("1.2.840.10008.3.1.2.3.3");
std::string const ModalityPerformedProcedureStepSOPClass("1.2.840.10008.3.1.2.3.3");
std::string const ModalityPerformedProcedureStepRetrieve("1.2.840.10008.3.1.2.3.4");
std::string const ModalityPerformedProcedureStepRetrieveSOPClass("1.2.840.10008.3.1.2.3.4");
std::string const ModalityPerformedProcedureStepNotification("1.2.840.10008.3.1.2.3.5");
std::string const ModalityPerformedProcedureStepNotificationSOPClass("1.2.840.10008.3.1.2.3.5");
std::string const DetachedResultsManagement("1.2.840.10008.3.1.2.5.1");
std::string const DetachedResultsManagementSOPClass_Retired("1.2.840.10008.3.1.2.5.1");
std::string const DetachedResultsManagementMeta("1.2.840.10008.3.1.2.5.4");
std::string const DetachedResultsManagementMetaSOPClass_Retired("1.2.840.10008.3.1.2.5.4");
std::string const DetachedStudyManagementMeta("1.2.840.10008.3.1.2.5.5");
std::string const DetachedStudyManagementMetaSOPClass_Retired("1.2.840.10008.3.1.2.5.5");
std::string const DetachedInterpretationManagement("1.2.840.10008.3.1.2.6.1");
std::string const DetachedInterpretationManagementSOPClass_Retired("1.2.840.10008.3.1.2.6.1");
std::string const Storage("1.2.840.10008.4.2");
std::string const StorageServiceClass("1.2.840.10008.4.2");
std::string const BasicFilmSession("1.2.840.10008.5.1.1.1");
std::string const BasicFilmSessionSOPClass("1.2.840.10008.5.1.1.1");
std::string const BasicFilmBox("1.2.840.10008.5.1.1.2");
std::string const BasicFilmBoxSOPClass("1.2.840.10008.5.1.1.2");
std::string const BasicGrayscaleImageBox("1.2.840.10008.5.1.1.4");
std::string const BasicGrayscaleImageBoxSOPClass("1.2.840.10008.5.1.1.4");
std::string const BasicColorImageBox("1.2.840.10008.5.1.1.4.1");
std::string const BasicColorImageBoxSOPClass("1.2.840.10008.5.1.1.4.1");
std::string const ReferencedImageBox("1.2.840.10008.5.1.1.4.2");
std::string const ReferencedImageBoxSOPClass_Retired("1.2.840.10008.5.1.1.4.2");
std::string const BasicGrayscalePrintManagementMeta("1.2.840.10008.5.1.1.9");
std::string const BasicGrayscalePrintManagementMetaSOPClass("1.2.840.10008.5.1.1.9");
std::string const ReferencedGrayscalePrintManagementMeta("1.2.840.10008.5.1.1.9.1");
std::string const ReferencedGrayscalePrintManagementMetaSOPClass_Retired("1.2.840.10008.5.1.1.9.1");
std::string const PrintJob("1.2.840.10008.5.1.1.14");
std::string const PrintJobSOPClass("1.2.840.10008.5.1.1.14");
std::string const BasicAnnotationBox("1.2.840.10008.5.1.1.15");
std::string const BasicAnnotationBoxSOPClass("1.2.840.10008.5.1.1.15");
std::string const Printer("1.2.840.10008.5.1.1.16");
std::string const PrinterSOPClass("1.2.840.10008.5.1.1.16");
std::string const PrinterConfigurationRetrieval("1.2.840.10008.5.1.1.16.376");
std::string const PrinterConfigurationRetrievalSOPClass("1.2.840.10008.5.1.1.16.376");
std::string const PrinterInstance("1.2.840.10008.5.1.1.17");
std::string const PrinterSOPInstance("1.2.840.10008.5.1.1.17");
std::string const PrinterConfigurationRetrievalInstance("1.2.840.10008.5.1.1.17.376");
std::string const PrinterConfigurationRetrievalSOPInstance("1.2.840.10008.5.1.1.17.376");
std::string const BasicColorPrintManagementMeta("1.2.840.10008.5.1.1.18");
std::string const BasicColorPrintManagementMetaSOPClass("1.2.840.10008.5.1.1.18");
std::string const ReferencedColorPrintManagementMeta("1.2.840.10008.5.1.1.18.1");
std::string const ReferencedColorPrintManagementMetaSOPClass_Retired("1.2.840.10008.5.1.1.18.1");
std::string const VOILUTBox("1.2.840.10008.5.1.1.22");
std::string const VOILUTBoxSOPClass("1.2.840.10008.5.1.1.22");
std::string const PresentationLUT("1.2.840.10008.5.1.1.23");
std::string const PresentationLUTSOPClass("1.2.840.10008.5.1.1.23");
std::string const ImageOverlayBox("1.2.840.10008.5.1.1.24");
std::string const ImageOverlayBoxSOPClass_Retired("1.2.840.10008.5.1.1.24");
std::string const BasicPrintImageOverlayBox("1.2.840.10008.5.1.1.24.1");
std::string const BasicPrintImageOverlayBoxSOPClass_Retired("1.2.840.10008.5.1.1.24.1");
std::string const PrintQueue("1.2.840.10008.5.1.1.25");
std::string const PrintQueueSOPInstance_Retired("1.2.840.10008.5.1.1.25");
std::string const PrintQueueManagement("1.2.840.10008.5.1.1.26");
std::string const PrintQueueManagementSOPClass_Retired("1.2.840.10008.5.1.1.26");
std::string const StoredPrintStorage("1.2.840.10008.5.1.1.27");
std::string const StoredPrintStorageSOPClass_Retired("1.2.840.10008.5.1.1.27");
std::string const HardcopyGrayscaleImageStorage("1.2.840.10008.5.1.1.29");
std::string const HardcopyGrayscaleImageStorageSOPClass_Retired("1.2.840.10008.5.1.1.29");
std::string const HardcopyColorImageStorage("1.2.840.10008.5.1.1.30");
std::string const HardcopyColorImageStorageSOPClass_Retired("1.2.840.10008.5.1.1.30");
std::string const PullPrintRequest("1.2.840.10008.5.1.1.31");
std::string const PullPrintRequestSOPClass_Retired("1.2.840.10008.5.1.1.31");
std::string const PullStoredPrintManagementMeta("1.2.840.10008.5.1.1.32");
std::string const PullStoredPrintManagementMetaSOPClass_Retired("1.2.840.10008.5.1.1.32");
std::string const MediaCreationManagement("1.2.840.10008.5.1.1.33");
std::string const MediaCreationManagementSOPClassUID("1.2.840.10008.5.1.1.33");
std::string const DisplaySystem("1.2.840.10008.5.1.1.40");
std::string const DisplaySystemSOPClass("1.2.840.10008.5.1.1.40");
std::string const DisplaySystemInstance("1.2.840.10008.5.1.1.40.1");
std::string const DisplaySystemSOPInstance("1.2.840.10008.5.1.1.40.1");
std::string const ComputedRadiographyImageStorage("1.2.840.10008.5.1.4.1.1.1");
std::string const DigitalXRayImageStorageForPresentation("1.2.840.10008.5.1.4.1.1.1.1");
std::string const DigitalXRayImageStorageForProcessing("1.2.840.10008.5.1.4.1.1.1.1.1");
std::string const DigitalMammographyXRayImageStorageForPresentation("1.2.840.10008.5.1.4.1.1.1.2");
std::string const DigitalMammographyXRayImageStorageForProcessing("1.2.840.10008.5.1.4.1.1.1.2.1");
std::string const DigitalIntraOralXRayImageStorageForPresentation("1.2.840.10008.5.1.4.1.1.1.3");
std::string const DigitalIntraOralXRayImageStorageForProcessing("1.2.840.10008.5.1.4.1.1.1.3.1");
std::string const CTImageStorage("1.2.840.10008.5.1.4.1.1.2");
std::string const EnhancedCTImageStorage("1.2.840.10008.5.1.4.1.1.2.1");
std::string const LegacyConvertedEnhancedCTImageStorage("1.2.840.10008.5.1.4.1.1.2.2");
std::string const UltrasoundMultiFrameImageStorageRetired("1.2.840.10008.5.1.4.1.1.3");
std::string const UltrasoundMultiframeImageStorage_Retired("1.2.840.10008.5.1.4.1.1.3");
std::string const UltrasoundMultiFrameImageStorage("1.2.840.10008.5.1.4.1.1.3.1");
std::string const UltrasoundMultiframeImageStorage("1.2.840.10008.5.1.4.1.1.3.1");
std::string const MRImageStorage("1.2.840.10008.5.1.4.1.1.4");
std::string const EnhancedMRImageStorage("1.2.840.10008.5.1.4.1.1.4.1");
std::string const MRSpectroscopyStorage("1.2.840.10008.5.1.4.1.1.4.2");
std::string const EnhancedMRColorImageStorage("1.2.840.10008.5.1.4.1.1.4.3");
std::string const LegacyConvertedEnhancedMRImageStorage("1.2.840.10008.5.1.4.1.1.4.4");
std::string const NuclearMedicineImageStorageRetired("1.2.840.10008.5.1.4.1.1.5");
std::string const NuclearMedicineImageStorage_Retired("1.2.840.10008.5.1.4.1.1.5");
std::string const UltrasoundImageStorageRetired("1.2.840.10008.5.1.4.1.1.6");
std::string const UltrasoundImageStorage_Retired("1.2.840.10008.5.1.4.1.1.6");
std::string const UltrasoundImageStorage("1.2.840.10008.5.1.4.1.1.6.1");
std::string const EnhancedUSVolumeStorage("1.2.840.10008.5.1.4.1.1.6.2");
std::string const SecondaryCaptureImageStorage("1.2.840.10008.5.1.4.1.1.7");
std::string const MultiFrameSingleBitSecondaryCaptureImageStorage("1.2.840.10008.5.1.4.1.1.7.1");
std::string const MultiframeSingleBitSecondaryCaptureImageStorage("1.2.840.10008.5.1.4.1.1.7.1");
std::string const MultiFrameGrayscaleByteSecondaryCaptureImageStorage("1.2.840.10008.5.1.4.1.1.7.2");
std::string const MultiframeGrayscaleByteSecondaryCaptureImageStorage("1.2.840.10008.5.1.4.1.1.7.2");
std::string const MultiFrameGrayscaleWordSecondaryCaptureImageStorage("1.2.840.10008.5.1.4.1.1.7.3");
std::string const MultiframeGrayscaleWordSecondaryCaptureImageStorage("1.2.840.10008.5.1.4.1.1.7.3");
std::string const MultiFrameTrueColorSecondaryCaptureImageStorage("1.2.840.10008.5.1.4.1.1.7.4");
std::string const MultiframeTrueColorSecondaryCaptureImageStorage("1.2.840.10008.5.1.4.1.1.7.4");
std::string const StandaloneOverlayStorage("1.2.840.10008.5.1.4.1.1.8");
std::string const StandaloneOverlayStorage_Retired("1.2.840.10008.5.1.4.1.1.8");
std::string const StandaloneCurveStorage("1.2.840.10008.5.1.4.1.1.9");
std::string const StandaloneCurveStorage_Retired("1.2.840.10008.5.1.4.1.1.9");
std::string const WaveformStorageTrial("1.2.840.10008.5.1.4.1.1.9.1");
std::string const WaveformStorageTrial_Retired("1.2.840.10008.5.1.4.1.1.9.1");
std::string const TwelveLeadECGWaveformStorage("1.2.840.10008.5.1.4.1.1.9.1.1");
std::string const GeneralECGWaveformStorage("1.2.840.10008.5.1.4.1.1.9.1.2");
std::string const AmbulatoryECGWaveformStorage("1.2.840.10008.5.1.4.1.1.9.1.3");
std::string const HemodynamicWaveformStorage("1.2.840.10008.5.1.4.1.1.9.2.1");
std::string const CardiacElectrophysiologyWaveformStorage("1.2.840.10008.5.1.4.1.1.9.3.1");
std::string const BasicVoiceAudioWaveformStorage("1.2.840.10008.5.1.4.1.1.9.4.1");
std::string const GeneralAudioWaveformStorage("1.2.840.10008.5.1.4.1.1.9.4.2");
std::string const ArterialPulseWaveformStorage("1.2.840.10008.5.1.4.1.1.9.5.1");
std::string const RespiratoryWaveformStorage("1.2.840.10008.5.1.4.1.1.9.6.1");
std::string const MultichannelRespiratoryWaveformStorage("1.2.840.10008.5.1.4.1.1.9.6.2");
std::string const RoutineScalpElectroencephalogramWaveformStorage("1.2.840.10008.5.1.4.1.1.9.7.1");
std::string const ElectromyogramWaveformStorage("1.2.840.10008.5.1.4.1.1.9.7.2");
std::string const ElectrooculogramWaveformStorage("1.2.840.10008.5.1.4.1.1.9.7.3");
std::string const SleepElectroencephalogramWaveformStorage("1.2.840.10008.5.1.4.1.1.9.7.4");
std::string const BodyPositionWaveformStorage("1.2.840.10008.5.1.4.1.1.9.8.1");
std::string const StandaloneModalityLUTStorage("1.2.840.10008.5.1.4.1.1.10");
std::string const StandaloneModalityLUTStorage_Retired("1.2.840.10008.5.1.4.1.1.10");
std::string const StandaloneVOILUTStorage("1.2.840.10008.5.1.4.1.1.11");
std::string const StandaloneVOILUTStorage_Retired("1.2.840.10008.5.1.4.1.1.11");
std::string const GrayscaleSoftcopyPresentationStateStorage("1.2.840.10008.5.1.4.1.1.11.1");
std::string const ColorSoftcopyPresentationStateStorage("1.2.840.10008.5.1.4.1.1.11.2");
std::string const PseudoColorSoftcopyPresentationStateStorage("1.2.840.10008.5.1.4.1.1.11.3");
std::string const BlendingSoftcopyPresentationStateStorage("1.2.840.10008.5.1.4.1.1.11.4");
std::string const XAXRFGrayscaleSoftcopyPresentationStateStorage("1.2.840.10008.5.1.4.1.1.11.5");
std::string const GrayscalePlanarMPRVolumetricPresentationStateStorage("1.2.840.10008.5.1.4.1.1.11.6");
std::string const CompositingPlanarMPRVolumetricPresentationStateStorage("1.2.840.10008.5.1.4.1.1.11.7");
std::string const AdvancedBlendingPresentationStateStorage("1.2.840.10008.5.1.4.1.1.11.8");
std::string const VolumeRenderingVolumetricPresentationStateStorage("1.2.840.10008.5.1.4.1.1.11.9");
std::string const SegmentedVolumeRenderingVolumetricPresentationStateStorage("1.2.840.10008.5.1.4.1.1.11.10");
std::string const MultipleVolumeRenderingVolumetricPresentationStateStorage("1.2.840.10008.5.1.4.1.1.11.11");
std::string const XRayAngiographicImageStorage("1.2.840.10008.5.1.4.1.1.12.1");
std::string const EnhancedXAImageStorage("1.2.840.10008.5.1.4.1.1.12.1.1");
std::string const XRayRadiofluoroscopicImageStorage("1.2.840.10008.5.1.4.1.1.12.2");
std::string const EnhancedXRFImageStorage("1.2.840.10008.5.1.4.1.1.12.2.1");
std::string const XRayAngiographicBiPlaneImageStorage("1.2.840.10008.5.1.4.1.1.12.3");
std::string const XRayAngiographicBiPlaneImageStorage_Retired("1.2.840.10008.5.1.4.1.1.12.3");
std::string const XRay3DAngiographicImageStorage("1.2.840.10008.5.1.4.1.1.13.1.1");
std::string const XRay3DCraniofacialImageStorage("1.2.840.10008.5.1.4.1.1.13.1.2");
std::string const BreastTomosynthesisImageStorage("1.2.840.10008.5.1.4.1.1.13.1.3");
std::string const BreastProjectionXRayImageStorageForPresentation("1.2.840.10008.5.1.4.1.1.13.1.4");
std::string const BreastProjectionXRayImageStorageForProcessing("1.2.840.10008.5.1.4.1.1.13.1.5");
std::string const IntravascularOpticalCoherenceTomographyImageStorageForPresentation("1.2.840.10008.5.1.4.1.1.14.1");
std::string const IntravascularOpticalCoherenceTomographyImageStorageForProcessing("1.2.840.10008.5.1.4.1.1.14.2");
std::string const NuclearMedicineImageStorage("1.2.840.10008.5.1.4.1.1.20");
std::string const ParametricMapStorage("1.2.840.10008.5.1.4.1.1.30");
std::string const RawDataStorage("1.2.840.10008.5.1.4.1.1.66");
std::string const SpatialRegistrationStorage("1.2.840.10008.5.1.4.1.1.66.1");
std::string const SpatialFiducialsStorage("1.2.840.10008.5.1.4.1.1.66.2");
std::string const DeformableSpatialRegistrationStorage("1.2.840.10008.5.1.4.1.1.66.3");
std::string const SegmentationStorage("1.2.840.10008.5.1.4.1.1.66.4");
std::string const SurfaceSegmentationStorage("1.2.840.10008.5.1.4.1.1.66.5");
std::string const TractographyResultsStorage("1.2.840.10008.5.1.4.1.1.66.6");
std::string const RealWorldValueMappingStorage("1.2.840.10008.5.1.4.1.1.67");
std::string const SurfaceScanMeshStorage("1.2.840.10008.5.1.4.1.1.68.1");
std::string const SurfaceScanPointCloudStorage("1.2.840.10008.5.1.4.1.1.68.2");
std::string const VLImageStorageTrial("1.2.840.10008.5.1.4.1.1.77.1");
std::string const VLImageStorageTrial_Retired("1.2.840.10008.5.1.4.1.1.77.1");
std::string const VLMultiFrameImageStorageTrial("1.2.840.10008.5.1.4.1.1.77.2");
std::string const VLMultiframeImageStorageTrial_Retired("1.2.840.10008.5.1.4.1.1.77.2");
std::string const VLEndoscopicImageStorage("1.2.840.10008.5.1.4.1.1.77.1.1");
std::string const VideoEndoscopicImageStorage("1.2.840.10008.5.1.4.1.1.77.1.1.1");
std::string const VLMicroscopicImageStorage("1.2.840.10008.5.1.4.1.1.77.1.2");
std::string const VideoMicroscopicImageStorage("1.2.840.10008.5.1.4.1.1.77.1.2.1");
std::string const VLSlideCoordinatesMicroscopicImageStorage("1.2.840.10008.5.1.4.1.1.77.1.3");
std::string const VLPhotographicImageStorage("1.2.840.10008.5.1.4.1.1.77.1.4");
std::string const VideoPhotographicImageStorage("1.2.840.10008.5.1.4.1.1.77.1.4.1");
std::string const OphthalmicPhotography8BitImageStorage("1.2.840.10008.5.1.4.1.1.77.1.5.1");
std::string const OphthalmicPhotography16BitImageStorage("1.2.840.10008.5.1.4.1.1.77.1.5.2");
std::string const StereometricRelationshipStorage("1.2.840.10008.5.1.4.1.1.77.1.5.3");
std::string const OphthalmicTomographyImageStorage("1.2.840.10008.5.1.4.1.1.77.1.5.4");
std::string const WideFieldOphthalmicPhotographyStereographicProjectionImageStorage("1.2.840.10008.5.1.4.1.1.77.1.5.5");
std::string const WideFieldOphthalmicPhotography3DCoordinatesImageStorage("1.2.840.10008.5.1.4.1.1.77.1.5.6");
std::string const OphthalmicOpticalCoherenceTomographyEnFaceImageStorage("1.2.840.10008.5.1.4.1.1.77.1.5.7");
std::string const OphthalmicOpticalCoherenceTomographyBscanVolumeAnalysisStorage("1.2.840.10008.5.1.4.1.1.77.1.5.8");
std::string const VLWholeSlideMicroscopyImageStorage("1.2.840.10008.5.1.4.1.1.77.1.6");
std::string const DermoscopicPhotographyImageStorage("1.2.840.10008.5.1.4.1.1.77.1.7");
std::string const LensometryMeasurementsStorage("1.2.840.10008.5.1.4.1.1.78.1");
std::string const AutorefractionMeasurementsStorage("1.2.840.10008.5.1.4.1.1.78.2");
std::string const KeratometryMeasurementsStorage("1.2.840.10008.5.1.4.1.1.78.3");
std::string const SubjectiveRefractionMeasurementsStorage("1.2.840.10008.5.1.4.1.1.78.4");
std::string const VisualAcuityMeasurementsStorage("1.2.840.10008.5.1.4.1.1.78.5");
std::string const SpectaclePrescriptionReportStorage("1.2.840.10008.5.1.4.1.1.78.6");
std::string const OphthalmicAxialMeasurementsStorage("1.2.840.10008.5.1.4.1.1.78.7");
std::string const IntraocularLensCalculationsStorage("1.2.840.10008.5.1.4.1.1.78.8");
std::string const MacularGridThicknessAndVolumeReportStorage("1.2.840.10008.5.1.4.1.1.79.1");
std::string const MacularGridThicknessandVolumeReportStorage("1.2.840.10008.5.1.4.1.1.79.1");
std::string const OphthalmicVisualFieldStaticPerimetryMeasurementsStorage("1.2.840.10008.5.1.4.1.1.80.1");
std::string const OphthalmicThicknessMapStorage("1.2.840.10008.5.1.4.1.1.81.1");
std::string const CornealTopographyMapStorage("1.2.840.10008.5.1.4.1.1.82.1");
std::string const TextSRStorageTrial("1.2.840.10008.5.1.4.1.1.88.1");
std::string const TextSRStorageTrial_Retired("1.2.840.10008.5.1.4.1.1.88.1");
std::string const AudioSRStorageTrial("1.2.840.10008.5.1.4.1.1.88.2");
std::string const AudioSRStorageTrial_Retired("1.2.840.10008.5.1.4.1.1.88.2");
std::string const DetailSRStorageTrial("1.2.840.10008.5.1.4.1.1.88.3");
std::string const DetailSRStorageTrial_Retired("1.2.840.10008.5.1.4.1.1.88.3");
std::string const ComprehensiveSRStorageTrial("1.2.840.10008.5.1.4.1.1.88.4");
std::string const ComprehensiveSRStorageTrial_Retired("1.2.840.10008.5.1.4.1.1.88.4");
std::string const BasicTextSRStorage("1.2.840.10008.5.1.4.1.1.88.11");
std::string const EnhancedSRStorage("1.2.840.10008.5.1.4.1.1.88.22");
std::string const ComprehensiveSRStorage("1.2.840.10008.5.1.4.1.1.88.33");
std::string const Comprehensive3DSRStorage("1.2.840.10008.5.1.4.1.1.88.34");
std::string const ExtensibleSRStorage("1.2.840.10008.5.1.4.1.1.88.35");
std::string const ProcedureLogStorage("1.2.840.10008.5.1.4.1.1.88.40");
std::string const MammographyCADSRStorage("1.2.840.10008.5.1.4.1.1.88.50");
std::string const KeyObjectSelectionDocumentStorage("1.2.840.10008.5.1.4.1.1.88.59");
std::string const ChestCADSRStorage("1.2.840.10008.5.1.4.1.1.88.65");
std::string const XRayRadiationDoseSRStorage("1.2.840.10008.5.1.4.1.1.88.67");
std::string const RadiopharmaceuticalRadiationDoseSRStorage("1.2.840.10008.5.1.4.1.1.88.68");
std::string const ColonCADSRStorage("1.2.840.10008.5.1.4.1.1.88.69");
std::string const ImplantationPlanSRStorage("1.2.840.10008.5.1.4.1.1.88.70");
std::string const AcquisitionContextSRStorage("1.2.840.10008.5.1.4.1.1.88.71");
std::string const SimplifiedAdultEchoSRStorage("1.2.840.10008.5.1.4.1.1.88.72");
std::string const PatientRadiationDoseSRStorage("1.2.840.10008.5.1.4.1.1.88.73");
std::string const PlannedImagingAgentAdministrationSRStorage("1.2.840.10008.5.1.4.1.1.88.74");
std::string const PerformedImagingAgentAdministrationSRStorage("1.2.840.10008.5.1.4.1.1.88.75");
std::string const ContentAssessmentResultsStorage("1.2.840.10008.5.1.4.1.1.90.1");
std::string const EncapsulatedPDFStorage("1.2.840.10008.5.1.4.1.1.104.1");
std::string const EncapsulatedCDAStorage("1.2.840.10008.5.1.4.1.1.104.2");
std::string const EncapsulatedSTLStorage("1.2.840.10008.5.1.4.1.1.104.3");
std::string const EncapsulatedOBJStorage("1.2.840.10008.5.1.4.1.1.104.4");
std::string const EncapsulatedMTLStorage("1.2.840.10008.5.1.4.1.1.104.5");
std::string const PositronEmissionTomographyImageStorage("1.2.840.10008.5.1.4.1.1.128");
std::string const LegacyConvertedEnhancedPETImageStorage("1.2.840.10008.5.1.4.1.1.128.1");
std::string const StandalonePETCurveStorage("1.2.840.10008.5.1.4.1.1.129");
std::string const StandalonePETCurveStorage_Retired("1.2.840.10008.5.1.4.1.1.129");
std::string const EnhancedPETImageStorage("1.2.840.10008.5.1.4.1.1.130");
std::string const BasicStructuredDisplayStorage("1.2.840.10008.5.1.4.1.1.131");
std::string const CTDefinedProcedureProtocolStorage("1.2.840.10008.5.1.4.1.1.200.1");
std::string const CTPerformedProcedureProtocolStorage("1.2.840.10008.5.1.4.1.1.200.2");
std::string const ProtocolApprovalStorage("1.2.840.10008.5.1.4.1.1.200.3");
std::string const ProtocolApprovalInformationModelFind("1.2.840.10008.5.1.4.1.1.200.4");
std::string const ProtocolApprovalInformationModelFIND("1.2.840.10008.5.1.4.1.1.200.4");
std::string const ProtocolApprovalInformationModelMove("1.2.840.10008.5.1.4.1.1.200.5");
std::string const ProtocolApprovalInformationModelMOVE("1.2.840.10008.5.1.4.1.1.200.5");
std::string const ProtocolApprovalInformationModelGet("1.2.840.10008.5.1.4.1.1.200.6");
std::string const ProtocolApprovalInformationModelGET("1.2.840.10008.5.1.4.1.1.200.6");
std::string const RTImageStorage("1.2.840.10008.5.1.4.1.1.481.1");
std::string const RTDoseStorage("1.2.840.10008.5.1.4.1.1.481.2");
std::string const RTStructureSetStorage("1.2.840.10008.5.1.4.1.1.481.3");
std::string const RTBeamsTreatmentRecordStorage("1.2.840.10008.5.1.4.1.1.481.4");
std::string const RTPlanStorage("1.2.840.10008.5.1.4.1.1.481.5");
std::string const RTBrachyTreatmentRecordStorage("1.2.840.10008.5.1.4.1.1.481.6");
std::string const RTTreatmentSummaryRecordStorage("1.2.840.10008.5.1.4.1.1.481.7");
std::string const RTIonPlanStorage("1.2.840.10008.5.1.4.1.1.481.8");
std::string const RTIonBeamsTreatmentRecordStorage("1.2.840.10008.5.1.4.1.1.481.9");
std::string const RTPhysicianIntentStorage("1.2.840.10008.5.1.4.1.1.481.10");
std::string const RTSegmentAnnotationStorage("1.2.840.10008.5.1.4.1.1.481.11");
std::string const RTRadiationSetStorage("1.2.840.10008.5.1.4.1.1.481.12");
std::string const CArmPhotonElectronRadiationStorage("1.2.840.10008.5.1.4.1.1.481.13");
std::string const TomotherapeuticRadiationStorage("1.2.840.10008.5.1.4.1.1.481.14");
std::string const RoboticArmRadiationStorage("1.2.840.10008.5.1.4.1.1.481.15");
std::string const RTRadiationRecordSetStorage("1.2.840.10008.5.1.4.1.1.481.16");
std::string const RTRadiationSalvageRecordStorage("1.2.840.10008.5.1.4.1.1.481.17");
std::string const TomotherapeuticRadiationRecordStorage("1.2.840.10008.5.1.4.1.1.481.18");
std::string const CArmPhotonElectronRadiationRecordStorage("1.2.840.10008.5.1.4.1.1.481.19");
std::string const RoboticRadiationRecordStorage("1.2.840.10008.5.1.4.1.1.481.20");
std::string const DICOSCTImageStorage("1.2.840.10008.5.1.4.1.1.501.1");
std::string const DICOSDigitalXRayImageStorageForPresentation("1.2.840.10008.5.1.4.1.1.501.2.1");
std::string const DICOSDigitalXRayImageStorageForProcessing("1.2.840.10008.5.1.4.1.1.501.2.2");
std::string const DICOSThreatDetectionReportStorage("1.2.840.10008.5.1.4.1.1.501.3");
std::string const DICOS2DAITStorage("1.2.840.10008.5.1.4.1.1.501.4");
std::string const DICOS3DAITStorage("1.2.840.10008.5.1.4.1.1.501.5");
std::string const DICOSQuadrupoleResonanceStorage("1.2.840.10008.5.1.4.1.1.501.6");
std::string const DICOSQuadrupoleResonanceQRStorage("1.2.840.10008.5.1.4.1.1.501.6");
std::string const EddyCurrentImageStorage("1.2.840.10008.5.1.4.1.1.601.1");
std::string const EddyCurrentMultiFrameImageStorage("1.2.840.10008.5.1.4.1.1.601.2");
std::string const EddyCurrentMultiframeImageStorage("1.2.840.10008.5.1.4.1.1.601.2");
std::string const PatientRootQueryRetrieveInformationModelFind("1.2.840.10008.5.1.4.1.2.1.1");
std::string const PatientRootQueryRetrieveInformationModelFIND("1.2.840.10008.5.1.4.1.2.1.1");
std::string const PatientRootQueryRetrieveInformationModelMove("1.2.840.10008.5.1.4.1.2.1.2");
std::string const PatientRootQueryRetrieveInformationModelMOVE("1.2.840.10008.5.1.4.1.2.1.2");
std::string const PatientRootQueryRetrieveInformationModelGet("1.2.840.10008.5.1.4.1.2.1.3");
std::string const PatientRootQueryRetrieveInformationModelGET("1.2.840.10008.5.1.4.1.2.1.3");
std::string const StudyRootQueryRetrieveInformationModelFind("1.2.840.10008.5.1.4.1.2.2.1");
std::string const StudyRootQueryRetrieveInformationModelFIND("1.2.840.10008.5.1.4.1.2.2.1");
std::string const StudyRootQueryRetrieveInformationModelMove("1.2.840.10008.5.1.4.1.2.2.2");
std::string const StudyRootQueryRetrieveInformationModelMOVE("1.2.840.10008.5.1.4.1.2.2.2");
std::string const StudyRootQueryRetrieveInformationModelGet("1.2.840.10008.5.1.4.1.2.2.3");
std::string const StudyRootQueryRetrieveInformationModelGET("1.2.840.10008.5.1.4.1.2.2.3");
std::string const PatientStudyOnlyQueryRetrieveInformationModelFind("1.2.840.10008.5.1.4.1.2.3.1");
std::string const PatientStudyOnlyQueryRetrieveInformationModelFIND_Retired("1.2.840.10008.5.1.4.1.2.3.1");
std::string const PatientStudyOnlyQueryRetrieveInformationModelMove("1.2.840.10008.5.1.4.1.2.3.2");
std::string const PatientStudyOnlyQueryRetrieveInformationModelMOVE_Retired("1.2.840.10008.5.1.4.1.2.3.2");
std::string const PatientStudyOnlyQueryRetrieveInformationModelGet("1.2.840.10008.5.1.4.1.2.3.3");
std::string const PatientStudyOnlyQueryRetrieveInformationModelGET_Retired("1.2.840.10008.5.1.4.1.2.3.3");
std::string const CompositeInstanceRootRetrieveMove("1.2.840.10008.5.1.4.1.2.4.2");
std::string const CompositeInstanceRootRetrieveMOVE("1.2.840.10008.5.1.4.1.2.4.2");
std::string const CompositeInstanceRootRetrieveGet("1.2.840.10008.5.1.4.1.2.4.3");
std::string const CompositeInstanceRootRetrieveGET("1.2.840.10008.5.1.4.1.2.4.3");
std::string const CompositeInstanceRetrieveWithoutBulkDataGet("1.2.840.10008.5.1.4.1.2.5.3");
std::string const CompositeInstanceRetrieveWithoutBulkDataGET("1.2.840.10008.5.1.4.1.2.5.3");
std::string const DefinedProcedureProtocolInformationModelFind("1.2.840.10008.5.1.4.20.1");
std::string const DefinedProcedureProtocolInformationModelFIND("1.2.840.10008.5.1.4.20.1");
std::string const DefinedProcedureProtocolInformationModelMove("1.2.840.10008.5.1.4.20.2");
std::string const DefinedProcedureProtocolInformationModelMOVE("1.2.840.10008.5.1.4.20.2");
std::string const DefinedProcedureProtocolInformationModelGet("1.2.840.10008.5.1.4.20.3");
std::string const DefinedProcedureProtocolInformationModelGET("1.2.840.10008.5.1.4.20.3");
std::string const ModalityWorklistInformationModelFind("1.2.840.10008.5.1.4.31");
std::string const ModalityWorklistInformationModelFIND("1.2.840.10008.5.1.4.31");
std::string const GeneralPurposeWorklistManagementMeta("1.2.840.10008.5.1.4.32");
std::string const GeneralPurposeWorklistManagementMetaSOPClass_Retired("1.2.840.10008.5.1.4.32");
std::string const GeneralPurposeWorklistInformationModelFIND("1.2.840.10008.5.1.4.32.1");
std::string const GeneralPurposeWorklistInformationModelFIND_Retired("1.2.840.10008.5.1.4.32.1");
std::string const GeneralPurposeScheduledProcedureStep("1.2.840.10008.5.1.4.32.2");
std::string const GeneralPurposeScheduledProcedureStepSOPClass_Retired("1.2.840.10008.5.1.4.32.2");
std::string const GeneralPurposePerformedProcedureStep("1.2.840.10008.5.1.4.32.3");
std::string const GeneralPurposePerformedProcedureStepSOPClass_Retired("1.2.840.10008.5.1.4.32.3");
std::string const InstanceAvailabilityNotification("1.2.840.10008.5.1.4.33");
std::string const InstanceAvailabilityNotificationSOPClass("1.2.840.10008.5.1.4.33");
std::string const RTBeamsDeliveryInstructionStorageTrial("1.2.840.10008.5.1.4.34.1");
std::string const RTBeamsDeliveryInstructionStorageTrial_Retired("1.2.840.10008.5.1.4.34.1");
std::string const RTConventionalMachineVerificationTrial("1.2.840.10008.5.1.4.34.2");
std::string const RTConventionalMachineVerificationTrial_Retired("1.2.840.10008.5.1.4.34.2");
std::string const RTIonMachineVerificationTrial("1.2.840.10008.5.1.4.34.3");
std::string const RTIonMachineVerificationTrial_Retired("1.2.840.10008.5.1.4.34.3");
std::string const UnifiedWorklistAndProcedureStepTrial("1.2.840.10008.5.1.4.34.4");
std::string const UnifiedWorklistandProcedureStepServiceClassTrial_Retired("1.2.840.10008.5.1.4.34.4");
std::string const UnifiedProcedureStepPushTrial("1.2.840.10008.5.1.4.34.4.1");
std::string const UnifiedProcedureStepPushSOPClassTrial_Retired("1.2.840.10008.5.1.4.34.4.1");
std::string const UnifiedProcedureStepWatchTrial("1.2.840.10008.5.1.4.34.4.2");
std::string const UnifiedProcedureStepWatchSOPClassTrial_Retired("1.2.840.10008.5.1.4.34.4.2");
std::string const UnifiedProcedureStepPullTrial("1.2.840.10008.5.1.4.34.4.3");
std::string const UnifiedProcedureStepPullSOPClassTrial_Retired("1.2.840.10008.5.1.4.34.4.3");
std::string const UnifiedProcedureStepEventTrial("1.2.840.10008.5.1.4.34.4.4");
std::string const UnifiedProcedureStepEventSOPClassTrial_Retired("1.2.840.10008.5.1.4.34.4.4");
std::string const UPSGlobalSubscriptionInstance("1.2.840.10008.5.1.4.34.5");
std::string const UPSGlobalSubscriptionSOPInstance("1.2.840.10008.5.1.4.34.5");
std::string const UPSFilteredGlobalSubscriptionInstance("1.2.840.10008.5.1.4.34.5.1");
std::string const UPSFilteredGlobalSubscriptionSOPInstance("1.2.840.10008.5.1.4.34.5.1");
std::string const UnifiedWorklistAndProcedureStep("1.2.840.10008.5.1.4.34.6");
std::string const UnifiedWorklistandProcedureStepServiceClass("1.2.840.10008.5.1.4.34.6");
std::string const UnifiedProcedureStepPush("1.2.840.10008.5.1.4.34.6.1");
std::string const UnifiedProcedureStepPushSOPClass("1.2.840.10008.5.1.4.34.6.1");
std::string const UnifiedProcedureStepWatch("1.2.840.10008.5.1.4.34.6.2");
std::string const UnifiedProcedureStepWatchSOPClass("1.2.840.10008.5.1.4.34.6.2");
std::string const UnifiedProcedureStepPull("1.2.840.10008.5.1.4.34.6.3");
std::string const UnifiedProcedureStepPullSOPClass("1.2.840.10008.5.1.4.34.6.3");
std::string const UnifiedProcedureStepEvent("1.2.840.10008.5.1.4.34.6.4");
std::string const UnifiedProcedureStepEventSOPClass("1.2.840.10008.5.1.4.34.6.4");
std::string const UnifiedProcedureStepQuery("1.2.840.10008.5.1.4.34.6.5");
std::string const UnifiedProcedureStepQuerySOPClass("1.2.840.10008.5.1.4.34.6.5");
std::string const RTBeamsDeliveryInstructionStorage("1.2.840.10008.5.1.4.34.7");
std::string const RTConventionalMachineVerification("1.2.840.10008.5.1.4.34.8");
std::string const RTIonMachineVerification("1.2.840.10008.5.1.4.34.9");
std::string const RTBrachyApplicationSetupDeliveryInstructionStorage("1.2.840.10008.5.1.4.34.10");
std::string const GeneralRelevantPatientInformationQuery("1.2.840.10008.5.1.4.37.1");
std::string const BreastImagingRelevantPatientInformationQuery("1.2.840.10008.5.1.4.37.2");
std::string const CardiacRelevantPatientInformationQuery("1.2.840.10008.5.1.4.37.3");
std::string const HangingProtocolStorage("1.2.840.10008.5.1.4.38.1");
std::string const HangingProtocolInformationModelFind("1.2.840.10008.5.1.4.38.2");
std::string const HangingProtocolInformationModelFIND("1.2.840.10008.5.1.4.38.2");
std::string const HangingProtocolInformationModelMove("1.2.840.10008.5.1.4.38.3");
std::string const HangingProtocolInformationModelMOVE("1.2.840.10008.5.1.4.38.3");
std::string const HangingProtocolInformationModelGet("1.2.840.10008.5.1.4.38.4");
std::string const HangingProtocolInformationModelGET("1.2.840.10008.5.1.4.38.4");
std::string const ColorPaletteStorage("1.2.840.10008.5.1.4.39.1");
std::string const ColorPaletteQueryRetrieveInformationModelFind("1.2.840.10008.5.1.4.39.2");
std::string const ColorPaletteQueryRetrieveInformationModelFIND("1.2.840.10008.5.1.4.39.2");
std::string const ColorPaletteQueryRetrieveInformationModelMove("1.2.840.10008.5.1.4.39.3");
std::string const ColorPaletteQueryRetrieveInformationModelMOVE("1.2.840.10008.5.1.4.39.3");
std::string const ColorPaletteQueryRetrieveInformationModelGet("1.2.840.10008.5.1.4.39.4");
std::string const ColorPaletteQueryRetrieveInformationModelGET("1.2.840.10008.5.1.4.39.4");
std::string const ProductCharacteristicsQuery("1.2.840.10008.5.1.4.41");
std::string const ProductCharacteristicsQuerySOPClass("1.2.840.10008.5.1.4.41");
std::string const SubstanceApprovalQuery("1.2.840.10008.5.1.4.42");
std::string const SubstanceApprovalQuerySOPClass("1.2.840.10008.5.1.4.42");
std::string const GenericImplantTemplateStorage("1.2.840.10008.5.1.4.43.1");
std::string const GenericImplantTemplateInformationModelFind("1.2.840.10008.5.1.4.43.2");
std::string const GenericImplantTemplateInformationModelFIND("1.2.840.10008.5.1.4.43.2");
std::string const GenericImplantTemplateInformationModelMove("1.2.840.10008.5.1.4.43.3");
std::string const GenericImplantTemplateInformationModelMOVE("1.2.840.10008.5.1.4.43.3");
std::string const GenericImplantTemplateInformationModelGet("1.2.840.10008.5.1.4.43.4");
std::string const GenericImplantTemplateInformationModelGET("1.2.840.10008.5.1.4.43.4");
std::string const ImplantAssemblyTemplateStorage("1.2.840.10008.5.1.4.44.1");
std::string const ImplantAssemblyTemplateInformationModelFind("1.2.840.10008.5.1.4.44.2");
std::string const ImplantAssemblyTemplateInformationModelFIND("1.2.840.10008.5.1.4.44.2");
std::string const ImplantAssemblyTemplateInformationModelMove("1.2.840.10008.5.1.4.44.3");
std::string const ImplantAssemblyTemplateInformationModelMOVE("1.2.840.10008.5.1.4.44.3");
std::string const ImplantAssemblyTemplateInformationModelGet("1.2.840.10008.5.1.4.44.4");
std::string const ImplantAssemblyTemplateInformationModelGET("1.2.840.10008.5.1.4.44.4");
std::string const ImplantTemplateGroupStorage("1.2.840.10008.5.1.4.45.1");
std::string const ImplantTemplateGroupInformationModelFind("1.2.840.10008.5.1.4.45.2");
std::string const ImplantTemplateGroupInformationModelFIND("1.2.840.10008.5.1.4.45.2");
std::string const ImplantTemplateGroupInformationModelMove("1.2.840.10008.5.1.4.45.3");
std::string const ImplantTemplateGroupInformationModelMOVE("1.2.840.10008.5.1.4.45.3");
std::string const ImplantTemplateGroupInformationModelGet("1.2.840.10008.5.1.4.45.4");
std::string const ImplantTemplateGroupInformationModelGET("1.2.840.10008.5.1.4.45.4");
std::string const NativeDICOMModel("1.2.840.10008.7.1.1");
std::string const AbstractMultiDimensionalImageModel("1.2.840.10008.7.1.2");
std::string const DICOMContentMappingResource("1.2.840.10008.8.1.1");
std::string const VideoEndoscopicImageRealTimeCommunication("1.2.840.10008.10.1");
std::string const VideoPhotographicImageRealTimeCommunication("1.2.840.10008.10.2");
std::string const AudioWaveformRealTimeCommunication("1.2.840.10008.10.3");
std::string const RenditionSelectionDocumentRealTimeCommunication("1.2.840.10008.10.4");
std::string const dicomDeviceName("1.2.840.10008.15.0.3.1");
std::string const dicomDescription("1.2.840.10008.15.0.3.2");
std::string const dicomManufacturer("1.2.840.10008.15.0.3.3");
std::string const dicomManufacturerModelName("1.2.840.10008.15.0.3.4");
std::string const dicomSoftwareVersion("1.2.840.10008.15.0.3.5");
std::string const dicomVendorData("1.2.840.10008.15.0.3.6");
std::string const dicomAETitle("1.2.840.10008.15.0.3.7");
std::string const dicomNetworkConnectionReference("1.2.840.10008.15.0.3.8");
std::string const dicomApplicationCluster("1.2.840.10008.15.0.3.9");
std::string const dicomAssociationInitiator("1.2.840.10008.15.0.3.10");
std::string const dicomAssociationAcceptor("1.2.840.10008.15.0.3.11");
std::string const dicomHostname("1.2.840.10008.15.0.3.12");
std::string const dicomPort("1.2.840.10008.15.0.3.13");
std::string const dicomSOPClass("1.2.840.10008.15.0.3.14");
std::string const dicomTransferRole("1.2.840.10008.15.0.3.15");
std::string const dicomTransferSyntax("1.2.840.10008.15.0.3.16");
std::string const dicomPrimaryDeviceType("1.2.840.10008.15.0.3.17");
std::string const dicomRelatedDeviceReference("1.2.840.10008.15.0.3.18");
std::string const dicomPreferredCalledAETitle("1.2.840.10008.15.0.3.19");
std::string const dicomTLSCyphersuite("1.2.840.10008.15.0.3.20");
std::string const dicomAuthorizedNodeCertificateReference("1.2.840.10008.15.0.3.21");
std::string const dicomThisNodeCertificateReference("1.2.840.10008.15.0.3.22");
std::string const dicomInstalled("1.2.840.10008.15.0.3.23");
std::string const dicomStationName("1.2.840.10008.15.0.3.24");
std::string const dicomDeviceSerialNumber("1.2.840.10008.15.0.3.25");
std::string const dicomInstitutionName("1.2.840.10008.15.0.3.26");
std::string const dicomInstitutionAddress("1.2.840.10008.15.0.3.27");
std::string const dicomInstitutionDepartmentName("1.2.840.10008.15.0.3.28");
std::string const dicomIssuerOfPatientID("1.2.840.10008.15.0.3.29");
std::string const dicomPreferredCallingAETitle("1.2.840.10008.15.0.3.30");
std::string const dicomSupportedCharacterSet("1.2.840.10008.15.0.3.31");
std::string const dicomConfigurationRoot("1.2.840.10008.15.0.4.1");
std::string const dicomDevicesRoot("1.2.840.10008.15.0.4.2");
std::string const dicomUniqueAETitlesRegistryRoot("1.2.840.10008.15.0.4.3");
std::string const dicomDevice("1.2.840.10008.15.0.4.4");
std::string const dicomNetworkAE("1.2.840.10008.15.0.4.5");
std::string const dicomNetworkConnection("1.2.840.10008.15.0.4.6");
std::string const dicomUniqueAETitle("1.2.840.10008.15.0.4.7");
std::string const dicomTransferCapability("1.2.840.10008.15.0.4.8");
std::string const UTC("1.2.840.10008.15.1.1");
std::string const UniversalCoordinatedTime("1.2.840.10008.15.1.1");

extern ODIL_API ElementsDictionary public_dictionary;
extern ODIL_API std::map<std::string, Tag> public_tags;
extern ODIL_API UIDsDictionary uids_dictionary;
extern ODIL_API bool const dummy;
}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9