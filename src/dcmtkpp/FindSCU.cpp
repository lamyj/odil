/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/FindSCU.h"

#include <functional>
#include <sstream>
#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

FindSCU
::~FindSCU()
{
    // Nothing to do
}

void 
FindSCU
::find(DcmDataset const * query, Callback callback) const
{
    // Send the request
    DIC_US const message_id = this->_association->get_association()->nextMsgID++;
    T_DIMSE_C_FindRQ request;
    memset(&request, 0, sizeof(request));
    
    request.MessageID = message_id;
    strcpy(request.AffectedSOPClassUID, this->_affected_sop_class.c_str());
    
    request.DataSetType = DIMSE_DATASET_PRESENT;
    request.Priority = DIMSE_PRIORITY_MEDIUM;
    
    // FIXME: include progress callback
    this->_send<DIMSE_C_FIND_RQ>(
        request, this->_affected_sop_class.c_str(), 
        const_cast<DcmDataset*>(query));
    
    // Receive the responses
    DIC_US status = STATUS_Pending;
    int response_count = 0;
    while(DICOM_PENDING_STATUS(status))
    {
        std::pair<T_ASC_PresentationContextID, T_DIMSE_Message> const command =
            this->_receive_command(DIMSE_BLOCKING);
        
        if(command.second.CommandField != DIMSE_C_FIND_RSP)
        {
            std::ostringstream message;
            message << "DIMSE: Unexpected Response Command Field: 0x" 
                    << std::hex << command.second.CommandField;
            throw Exception(message.str());
        }
        
        T_DIMSE_C_FindRSP const response = command.second.msg.CFindRSP;
        
        if(response.MessageIDBeingRespondedTo != message_id)
        {
            std::ostringstream message;
            message << "DIMSE: Unexpected Response MsgId: "
                    << response.MessageIDBeingRespondedTo 
                    << "(expected: " << message_id << ")";
            throw Exception(message.str());
        }
        
        status = response.DimseStatus;
        ++response_count;
        
        if(status == STATUS_Pending || status == STATUS_FIND_Pending_WarningUnsupportedOptionalKeys)
        {
            // FIXME: include progress callback
            std::pair<T_ASC_PresentationContextID, DcmDataset *> response =
                this->_receive_dataset(DIMSE_BLOCKING);
            // Execute user callback
            callback(response.second);
            
            // Response dataset is allocated in DIMSE_receiveDataSetInMemory,
            // free it now.
            delete response.second;
        }
    }
}

std::vector<DcmDataset *>
FindSCU
::find(DcmDataset const * query) const
{
    std::vector<DcmDataset*> result;
    auto callback = [&result](DcmDataset * dataset) { 
        // We do not manage the allocation of dataset: clone it
        result.push_back(static_cast<DcmDataset*>(dataset->clone())); 
    };
    this->find(query, callback);
    
    return result;
}

}
