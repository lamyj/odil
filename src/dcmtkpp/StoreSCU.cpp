/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "StoreSCU.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CStoreRequest.h"
#include "dcmtkpp/CStoreResponse.h"
#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

StoreSCU
::~StoreSCU()
{
    // Nothing to do.
}

void 
StoreSCU
::set_affected_sop_class(DcmDataset const * dataset)
{
    std::string const sop_class_uid =
        ElementAccessor<std::string>::get(*dataset, DCM_SOPClassUID);
    
    // From dcuid.h
    std::vector<std::string> const storage = {
        UID_RETIRED_StoredPrintStorage,
        UID_RETIRED_HardcopyGrayscaleImageStorage,
        UID_RETIRED_HardcopyColorImageStorage,
        UID_ComputedRadiographyImageStorage,
        UID_DigitalXRayImageStorageForPresentation,
        UID_DigitalXRayImageStorageForProcessing,
        UID_DigitalMammographyXRayImageStorageForPresentation,
        UID_DigitalMammographyXRayImageStorageForProcessing,
        UID_DigitalIntraOralXRayImageStorageForPresentation,
        UID_DigitalIntraOralXRayImageStorageForProcessing,
        UID_CTImageStorage,
        UID_EnhancedCTImageStorage,
        UID_RETIRED_UltrasoundMultiframeImageStorage,
        UID_UltrasoundMultiframeImageStorage,
        UID_MRImageStorage,
        UID_EnhancedMRImageStorage,
        UID_MRSpectroscopyStorage,
        UID_EnhancedMRColorImageStorage,
        UID_RETIRED_NuclearMedicineImageStorage,
        UID_RETIRED_UltrasoundImageStorage,
        UID_UltrasoundImageStorage,
        UID_EnhancedUSVolumeStorage,
        UID_SecondaryCaptureImageStorage,
        UID_MultiframeSingleBitSecondaryCaptureImageStorage,
        UID_MultiframeGrayscaleByteSecondaryCaptureImageStorage,
        UID_MultiframeGrayscaleWordSecondaryCaptureImageStorage,
        UID_MultiframeTrueColorSecondaryCaptureImageStorage,
        UID_RETIRED_StandaloneOverlayStorage,
        UID_RETIRED_StandaloneCurveStorage,
        UID_TwelveLeadECGWaveformStorage,
        UID_GeneralECGWaveformStorage,
        UID_AmbulatoryECGWaveformStorage,
        UID_HemodynamicWaveformStorage,
        UID_CardiacElectrophysiologyWaveformStorage,
        UID_BasicVoiceAudioWaveformStorage,
        UID_GeneralAudioWaveformStorage,
        UID_ArterialPulseWaveformStorage,
        UID_RespiratoryWaveformStorage,
        UID_RETIRED_StandaloneModalityLUTStorage,
        UID_RETIRED_StandaloneVOILUTStorage,
        UID_GrayscaleSoftcopyPresentationStateStorage,
        UID_ColorSoftcopyPresentationStateStorage,
        UID_PseudoColorSoftcopyPresentationStateStorage,
        UID_BlendingSoftcopyPresentationStateStorage,
        UID_XAXRFGrayscaleSoftcopyPresentationStateStorage,
        UID_XRayAngiographicImageStorage,
        UID_EnhancedXAImageStorage,
        UID_XRayRadiofluoroscopicImageStorage,
        UID_EnhancedXRFImageStorage,
        UID_XRay3DAngiographicImageStorage,
        UID_XRay3DCraniofacialImageStorage,
        UID_BreastTomosynthesisImageStorage,
        UID_RETIRED_XRayAngiographicBiPlaneImageStorage,
        UID_NuclearMedicineImageStorage,
        UID_RawDataStorage,
        UID_SpatialRegistrationStorage,
        UID_SpatialFiducialsStorage,
        UID_DeformableSpatialRegistrationStorage,
        UID_SegmentationStorage,
        UID_SurfaceSegmentationStorage,
        UID_RealWorldValueMappingStorage,
        UID_RETIRED_VLImageStorage,
        UID_VLEndoscopicImageStorage,
        UID_VideoEndoscopicImageStorage,
        UID_VLMicroscopicImageStorage,
        UID_VideoMicroscopicImageStorage,
        UID_VLSlideCoordinatesMicroscopicImageStorage,
        UID_VLPhotographicImageStorage,
        UID_VideoPhotographicImageStorage,
        UID_OphthalmicPhotography8BitImageStorage,
        UID_OphthalmicPhotography16BitImageStorage,
        UID_StereometricRelationshipStorage,
        UID_OphthalmicTomographyImageStorage,
        UID_VLWholeSlideMicroscopyImageStorage,
        UID_RETIRED_VLMultiFrameImageStorage,
        UID_LensometryMeasurementsStorage,
        UID_AutorefractionMeasurementsStorage,
        UID_KeratometryMeasurementsStorage,
        UID_SubjectiveRefractionMeasurementsStorage,
        UID_VisualAcuityMeasurementsStorage,
        UID_SpectaclePrescriptionReportStorage,
        UID_OphthalmicAxialMeasurementsStorage,
        UID_IntraocularLensCalculationsStorage,
        UID_MacularGridThicknessAndVolumeReportStorage,
        UID_OphthalmicVisualFieldStaticPerimetryMeasurementsStorage,
        UID_BasicTextSRStorage,
        UID_EnhancedSRStorage,
        UID_ComprehensiveSRStorage,
        UID_ProcedureLogStorage,
        UID_MammographyCADSRStorage,
        UID_KeyObjectSelectionDocumentStorage,
        UID_ChestCADSRStorage,
        UID_XRayRadiationDoseSRStorage,
        UID_ColonCADSRStorage,
        UID_ImplantationPlanSRDocumentStorage,
        UID_EncapsulatedPDFStorage,
        UID_EncapsulatedCDAStorage,
        UID_PositronEmissionTomographyImageStorage,
        UID_RETIRED_StandalonePETCurveStorage,
        UID_EnhancedPETImageStorage,
        UID_BasicStructuredDisplayStorage,
        UID_RTImageStorage,
        UID_RTDoseStorage,
        UID_RTStructureSetStorage,
        UID_RTBeamsTreatmentRecordStorage,
        UID_RTPlanStorage,
        UID_RTBrachyTreatmentRecordStorage,
        UID_RTTreatmentSummaryRecordStorage,
        UID_RTIonPlanStorage,
        UID_RTIonBeamsTreatmentRecordStorage,
        UID_GenericImplantTemplateStorage,
        UID_ImplantAssemblyTemplateStorage,
        UID_ImplantTemplateGroupStorage
    };

    if(std::find(storage.begin(), storage.end(), sop_class_uid) != storage.end())
    {
        this->SCU::set_affected_sop_class(sop_class_uid);
    }
    else
    {
        throw Exception("Could not guess affected SOP class from dataset");
    }
}

void 
StoreSCU
::store(DcmDataset const * dataset, ProgressCallback callback, void * data) const
{
    CStoreRequest const request(
        this->_association->get_association()->nextMsgID++,
        this->_affected_sop_class,
        ElementAccessor<std::string>::get(*dataset, DCM_SOPInstanceUID),
        DIMSE_PRIORITY_MEDIUM,
        dataset);
    this->_send(request, this->_affected_sop_class, callback, data);
    
    CStoreResponse const response = this->_receive<CStoreResponse>();

    if(response.get_message_id_being_responded_to() != request.get_message_id())
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response MsgId: "
                << response.get_message_id_being_responded_to()
                << "(expected: " << request.get_message_id() << ")";
        throw Exception(message.str());
    }

    if(response.has_affected_sop_class_uid() &&
       response.get_affected_sop_class_uid() != request.get_affected_sop_class_uid())
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response Affected SOP Class UID: "
                << response.get_affected_sop_class_uid()
                << " (expected: " << request.get_affected_sop_class_uid() << ")";
        throw Exception(message.str());
    }
    if(response.has_affected_sop_instance_uid() &&
       response.get_affected_sop_instance_uid() != request.get_affected_sop_instance_uid())
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response Affected SOP Instance UID: "
                << response.get_affected_sop_instance_uid()
                << " (expected: " << request.get_affected_sop_instance_uid() << ")";
        throw Exception(message.str());
    }
}

}
