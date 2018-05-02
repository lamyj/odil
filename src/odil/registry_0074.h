/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0074
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0074

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const ContinuationStartMeterset(0x0074, 0x0120);
Tag const ContinuationEndMeterset(0x0074, 0x0121);
Tag const ProcedureStepState(0x0074, 0x1000);
Tag const ProcedureStepProgressInformationSequence(0x0074, 0x1002);
Tag const ProcedureStepProgress(0x0074, 0x1004);
Tag const ProcedureStepProgressDescription(0x0074, 0x1006);
Tag const ProcedureStepProgressParametersSequence(0x0074, 0x1007);
Tag const ProcedureStepCommunicationsURISequence(0x0074, 0x1008);
Tag const ContactURI(0x0074, 0x100a);
Tag const ContactDisplayName(0x0074, 0x100c);
Tag const ProcedureStepDiscontinuationReasonCodeSequence(0x0074, 0x100e);
Tag const BeamTaskSequence(0x0074, 0x1020);
Tag const BeamTaskType(0x0074, 0x1022);
Tag const BeamOrderIndexTrial(0x0074, 0x1024);
Tag const AutosequenceFlag(0x0074, 0x1025);
Tag const TableTopVerticalAdjustedPosition(0x0074, 0x1026);
Tag const TableTopLongitudinalAdjustedPosition(0x0074, 0x1027);
Tag const TableTopLateralAdjustedPosition(0x0074, 0x1028);
Tag const PatientSupportAdjustedAngle(0x0074, 0x102a);
Tag const TableTopEccentricAdjustedAngle(0x0074, 0x102b);
Tag const TableTopPitchAdjustedAngle(0x0074, 0x102c);
Tag const TableTopRollAdjustedAngle(0x0074, 0x102d);
Tag const DeliveryVerificationImageSequence(0x0074, 0x1030);
Tag const VerificationImageTiming(0x0074, 0x1032);
Tag const DoubleExposureFlag(0x0074, 0x1034);
Tag const DoubleExposureOrdering(0x0074, 0x1036);
Tag const DoubleExposureMetersetTrial(0x0074, 0x1038);
Tag const DoubleExposureFieldDeltaTrial(0x0074, 0x103a);
Tag const RelatedReferenceRTImageSequence(0x0074, 0x1040);
Tag const GeneralMachineVerificationSequence(0x0074, 0x1042);
Tag const ConventionalMachineVerificationSequence(0x0074, 0x1044);
Tag const IonMachineVerificationSequence(0x0074, 0x1046);
Tag const FailedAttributesSequence(0x0074, 0x1048);
Tag const OverriddenAttributesSequence(0x0074, 0x104a);
Tag const ConventionalControlPointVerificationSequence(0x0074, 0x104c);
Tag const IonControlPointVerificationSequence(0x0074, 0x104e);
Tag const AttributeOccurrenceSequence(0x0074, 0x1050);
Tag const AttributeOccurrencePointer(0x0074, 0x1052);
Tag const AttributeItemSelector(0x0074, 0x1054);
Tag const AttributeOccurrencePrivateCreator(0x0074, 0x1056);
Tag const SelectorSequencePointerItems(0x0074, 0x1057);
Tag const ScheduledProcedureStepPriority(0x0074, 0x1200);
Tag const WorklistLabel(0x0074, 0x1202);
Tag const ProcedureStepLabel(0x0074, 0x1204);
Tag const ScheduledProcessingParametersSequence(0x0074, 0x1210);
Tag const PerformedProcessingParametersSequence(0x0074, 0x1212);
Tag const UnifiedProcedureStepPerformedProcedureSequence(0x0074, 0x1216);
Tag const RelatedProcedureStepSequence(0x0074, 0x1220);
Tag const ProcedureStepRelationshipType(0x0074, 0x1222);
Tag const ReplacedProcedureStepSequence(0x0074, 0x1224);
Tag const DeletionLock(0x0074, 0x1230);
Tag const ReceivingAE(0x0074, 0x1234);
Tag const RequestingAE(0x0074, 0x1236);
Tag const ReasonForCancellation(0x0074, 0x1238);
Tag const SCPStatus(0x0074, 0x1242);
Tag const SubscriptionListStatus(0x0074, 0x1244);
Tag const UnifiedProcedureStepListStatus(0x0074, 0x1246);
Tag const BeamOrderIndex(0x0074, 0x1324);
Tag const DoubleExposureMeterset(0x0074, 0x1338);
Tag const DoubleExposureFieldDelta(0x0074, 0x133a);
Tag const BrachyTaskSequence(0x0074, 0x1401);
Tag const ContinuationStartTotalReferenceAirKerma(0x0074, 0x1402);
Tag const ContinuationEndTotalReferenceAirKerma(0x0074, 0x1403);
Tag const ContinuationPulseNumber(0x0074, 0x1404);
Tag const ChannelDeliveryOrderSequence(0x0074, 0x1405);
Tag const ReferencedChannelNumber(0x0074, 0x1406);
Tag const StartCumulativeTimeWeight(0x0074, 0x1407);
Tag const EndCumulativeTimeWeight(0x0074, 0x1408);
Tag const OmittedChannelSequence(0x0074, 0x1409);
Tag const ReasonForChannelOmission(0x0074, 0x140a);
Tag const ReasonForChannelOmissionDescription(0x0074, 0x140b);
Tag const ChannelDeliveryOrderIndex(0x0074, 0x140c);
Tag const ChannelDeliveryContinuationSequence(0x0074, 0x140d);
Tag const OmittedApplicationSetupSequence(0x0074, 0x140e);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0074