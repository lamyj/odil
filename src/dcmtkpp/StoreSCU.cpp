/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "StoreSCU.h"

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmnet/dimse.h>

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
    OFString value;
    OFCondition const condition = 
        const_cast<DcmDataset*>(dataset)->findAndGetOFString(
            DCM_SOPClassUID, value);
    if(condition.bad())
    {
        throw Exception(condition);
    }
    
    std::string const sop_class_uid(value.c_str());
    
    std::vector<std::string> known_uids = {
        UID_ComputedRadiographyImageStorage,
        UID_CTImageStorage,
        UID_EnhancedCTImageStorage,
        UID_UltrasoundMultiframeImageStorage,
        UID_MRImageStorage,
        UID_EnhancedMRImageStorage,
        UID_EnhancedMRColorImageStorage,
        UID_UltrasoundImageStorage,
        UID_SecondaryCaptureImageStorage,
        UID_MultiframeSingleBitSecondaryCaptureImageStorage,
        UID_MultiframeGrayscaleByteSecondaryCaptureImageStorage,
        UID_MultiframeGrayscaleWordSecondaryCaptureImageStorage,
        UID_MultiframeTrueColorSecondaryCaptureImageStorage,
        UID_XRayAngiographicImageStorage,
        UID_EnhancedXAImageStorage,
        UID_XRayRadiofluoroscopicImageStorage,
        UID_EnhancedXRFImageStorage,
        UID_BreastTomosynthesisImageStorage,
        UID_NuclearMedicineImageStorage,
        UID_VLEndoscopicImageStorage,
        UID_VideoEndoscopicImageStorage,
        UID_VLMicroscopicImageStorage,
        UID_VideoMicroscopicImageStorage,
        UID_VLSlideCoordinatesMicroscopicImageStorage,
        UID_VLPhotographicImageStorage,
        UID_VideoPhotographicImageStorage,
        UID_OphthalmicTomographyImageStorage,
        UID_VLWholeSlideMicroscopyImageStorage,
        UID_PositronEmissionTomographyImageStorage,
        UID_EnhancedPETImageStorage,
        UID_RTImageStorage,
    };

    
    if(std::find(known_uids.begin(), known_uids.end(), sop_class_uid.c_str()) != known_uids.end())
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
::store(DcmDataset const * dataset, Callback callback, void * data,
    long bytes_count) const
{
    // Encapsulate the callback and its data
    CallbackData encapsulated;
    encapsulated.callback = callback;
    encapsulated.data = data;
    
    this->_store(dataset, StoreSCU::_callback_wrapper, &encapsulated, bytes_count);
}

void
StoreSCU
::store(DcmDataset const * dataset, long bytes_count) const
{
    this->_store(dataset, NULL, NULL, bytes_count);
}

void
StoreSCU
::_callback_wrapper(void * data, 
    T_DIMSE_StoreProgress * progress, T_DIMSE_C_StoreRQ * request)
{
    CallbackData * encapsulated = reinterpret_cast<CallbackData*>(data);
    encapsulated->callback(encapsulated->data, progress, request);
}

void 
StoreSCU
::_store(DcmDataset const * dataset, 
    DIMSE_StoreUserCallback callback, void * data, 
    long bytes_count) const
{
    T_ASC_PresentationContextID const presentation_id = 
        ASC_findAcceptedPresentationContextID(
            this->_association->get_association(), 
            this->_affected_sop_class.c_str());
    if(presentation_id == 0) 
    {
        throw Exception("No Presentation Context for Find Operation");
    }
    
    DIC_US const message_id = this->_association->get_association()->nextMsgID++;
    
    T_DIMSE_C_StoreRQ request;
    memset(&request, 0, sizeof(request));
    
    request.MessageID = message_id;
    strcpy(request.AffectedSOPClassUID, this->_affected_sop_class.c_str());
    
    OFString sop_instance_uid;
    const_cast<DcmDataset*>(dataset)->findAndGetOFString(DCM_SOPInstanceUID, sop_instance_uid);
    strcpy(request.AffectedSOPInstanceUID, sop_instance_uid.c_str());
    
    request.DataSetType = DIMSE_DATASET_PRESENT;
    request.Priority = DIMSE_PRIORITY_MEDIUM;
    
    T_DIMSE_C_StoreRSP response;
    DcmDataset * status_detail = NULL;
    
    OFCondition const condition = DIMSE_storeUser(
        this->_association->get_association(), 
        presentation_id, &request, NULL, const_cast<DcmDataset*>(dataset),
        callback, data,
        DIMSE_BLOCKING, this->_network->get_timeout(), &response, &status_detail,
        NULL, bytes_count);
    
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

}
