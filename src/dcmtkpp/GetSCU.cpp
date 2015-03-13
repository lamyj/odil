/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/GetSCU.h"

#include <functional>
#include <sstream>
#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

GetSCU
::~GetSCU()
{
    // Nothing to do
}

void 
GetSCU
::get(DcmDataset const * query, Callback callback) const
{
    // Send the request
    DIC_US const message_id = this->_association->get_association()->nextMsgID++;
    T_DIMSE_C_GetRQ request;
    memset(&request, 0, sizeof(request));
    
    request.MessageID = message_id;
    strcpy(request.AffectedSOPClassUID, this->_affected_sop_class.c_str());
    
    request.DataSetType = DIMSE_DATASET_PRESENT;
    request.Priority = DIMSE_PRIORITY_MEDIUM;
    
    // FIXME: include progress callback
    this->_send<DIMSE_C_GET_RQ>(request, const_cast<DcmDataset*>(query));
    
    // Receive the responses
    bool done = false;
    while(!done)
    {
        std::pair<T_ASC_PresentationContextID, T_DIMSE_Message> const command =
            this->_receive_command(DIMSE_BLOCKING);
        
        if(command.second.CommandField == DIMSE_C_GET_RSP)
        {
            done = this->_get_response(command.second.msg.CGetRSP);
        }
        else if(command.second.CommandField == DIMSE_C_STORE_RQ)
        {
            try
            {
                this->_store_request(command.second.msg.CStoreRQ, callback);
            }
            catch(...)
            {
                // FIXME: logging
                done = true;
            }
        }
        else
        {
            std::ostringstream message;
            message << "DIMSE: Unexpected Response Command Field: 0x" 
                    << std::hex << command.second.CommandField;
            throw Exception(message.str());
        }
    }
}

std::vector<DcmDataset *>
GetSCU
::get(DcmDataset const * query) const
{
    std::vector<DcmDataset*> result;
    auto callback = [&result](DcmDataset * dataset) { 
        // We do not manage the allocation of dataset: clone it
        result.push_back(static_cast<DcmDataset*>(dataset->clone())); 
    };
    this->get(query, callback);
    
    return result;
}

bool
GetSCU
::_get_response(T_DIMSE_C_GetRSP response) const
{
    bool done;
    if(response.DimseStatus & 0xf000 == STATUS_GET_Failed_UnableToProcess)
    {
        done = true;
        // FIXME: logging
    }
    else if(response.DimseStatus == STATUS_GET_Refused_OutOfResourcesNumberOfMatches)
    {
        done = true;
        // FIXME: logging
    }
    else if(response.DimseStatus == STATUS_GET_Refused_OutOfResourcesSubOperations)
    {
        done = true;
        // FIXME: logging
    }
    else if(response.DimseStatus == STATUS_GET_Failed_IdentifierDoesNotMatchSOPClass)
    {
        done = true;
        // FIXME: logging
    }
    else if(response.DimseStatus == STATUS_GET_Cancel_SubOperationsTerminatedDueToCancelIndication)
    {
        done = true;
        // FIXME: logging
    }
    else if(response.DimseStatus == STATUS_GET_Warning_SubOperationsCompleteOneOrMoreFailures)
    {
        done = true;
        // FIXME: logging
    }
    else if(response.DimseStatus == STATUS_Pending)
    {
        done = false;
    }
    else if(response.DimseStatus == STATUS_Success)
    {
        done = true;
    }
    else
    {
        done = true;
        // FIXME: logging
    }
    
    return done;
}

void
GetSCU
::_store_request(T_DIMSE_C_StoreRQ request, Callback callback) const
{
    // FIXME: include progress callback
    std::pair<T_ASC_PresentationContextID, DcmDataset *> dataset =
        this->_receive_dataset(DIMSE_BLOCKING);
    // Execute user callback
    Uint16 store_status = 0;
    try
    {
        callback(dataset.second);
    }
    catch(...)
    {
        // FIXME: logging
        store_status = STATUS_STORE_Error_CannotUnderstand;
    }
    
    // Request dataset is allocated in DIMSE_receiveDataSetInMemory,
    // free it now.
    delete dataset.second;
    
    // Send store response
    T_DIMSE_C_StoreRSP response;
    memset(&response, 0, sizeof(response));
    response.MessageIDBeingRespondedTo = request.MessageID;
    response.DimseStatus = store_status;
    response.DataSetType = DIMSE_DATASET_NULL;
    OFStandard::strlcpy(
        response.AffectedSOPClassUID, request.AffectedSOPClassUID, 
        sizeof(response.AffectedSOPClassUID));
    OFStandard::strlcpy(
        response.AffectedSOPInstanceUID, request.AffectedSOPInstanceUID, 
        sizeof(response.AffectedSOPInstanceUID));
    response.opts = O_STORE_AFFECTEDSOPCLASSUID | O_STORE_AFFECTEDSOPINSTANCEUID;
    this->_send<DIMSE_C_STORE_RSP>(response);
}

}
