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
    CStoreRequest const request(
        this->_association->get_association()->nextMsgID++,
        this->_affected_sop_class,
        ElementAccessor<EVR_UI>::get(*dataset, DCM_SOPInstanceUID),
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
