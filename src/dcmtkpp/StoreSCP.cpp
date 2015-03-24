/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/StoreSCP.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmnet/dimse.h>

namespace dcmtkpp
{

bool 
StoreSCP
::store(Callback callback) const
{
    std::pair<T_ASC_PresentationContextID, T_DIMSE_Message> command;
    try
    {
        command = this->_receive_command(DIMSE_BLOCKING);
    }
    catch(Exception const & e)
    {
        if(e.get_source() != Exception::Source::Condition ||
           e.get_condition() != DUL_PEERREQUESTEDRELEASE)
        {
            throw;
        }
        else
        {
            return true;
        }
    }
    
    if(command.second.CommandField == DIMSE_C_ECHO_RQ)
    {
        this->_send_echo_response(command.second.msg.CEchoRQ);
    }
    else if(command.second.CommandField == DIMSE_C_STORE_RQ)
    {
        this->store(command.second.msg.CStoreRQ, callback);
    }
    else
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response Command Field: 0x" 
                << std::hex << command.second.CommandField;
        throw Exception(message.str());
    }
    
    return false;
}

void
StoreSCP
::store(T_DIMSE_C_StoreRQ request, Callback callback) const
{
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
    this->_send<DIMSE_C_STORE_RSP>(response, request.AffectedSOPClassUID);
}

}
