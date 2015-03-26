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
        ElementAccessor<EVR_UI>::get(*dataset, DCM_SOPClassUID);
    
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
::store(DcmDataset const * dataset, ProgressCallback callback, void * data) const
{
    // Send the request
    DIC_US const message_id = this->_association->get_association()->nextMsgID++;
    
    T_DIMSE_C_StoreRQ request;
    memset(&request, 0, sizeof(request));
    
    request.MessageID = message_id;
    strcpy(request.AffectedSOPClassUID, this->_affected_sop_class.c_str());
    
    std::string const sop_instance_uid =
        ElementAccessor<EVR_UI>::get(*dataset, DCM_SOPInstanceUID);
    strcpy(request.AffectedSOPInstanceUID, sop_instance_uid.c_str());
    
    request.DataSetType = DIMSE_DATASET_PRESENT;
    request.Priority = DIMSE_PRIORITY_MEDIUM;
    
    this->_send<DIMSE_C_STORE_RQ>(
        request, this->_affected_sop_class, 
        const_cast<DcmDataset*>(dataset), callback, data);
    
    // Receive the response
    std::pair<T_ASC_PresentationContextID, T_DIMSE_Message> const command =
        this->_receive_command(DIMSE_BLOCKING);
    
    if(command.second.CommandField != DIMSE_C_STORE_RSP)
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response Command Field: 0x" 
                << std::hex << command.second.CommandField;
        throw Exception(message.str());
    }

    T_DIMSE_C_StoreRSP const response = command.second.msg.CStoreRSP;

    if(response.MessageIDBeingRespondedTo != message_id)
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response MsgId: "
                << response.MessageIDBeingRespondedTo 
                << "(expected: " << message_id << ")";
        throw Exception(message.str());
    }
}

}
