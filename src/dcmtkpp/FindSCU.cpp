/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/FindSCU.h"

#include <functional>
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
::find(DcmDataset const * query, FullCallback callback, void * data) const
{
    // Encapsulate the callback and its data
    FullCallbackData encapsulated;
    encapsulated.callback = callback;
    encapsulated.data = data;
    
    this->_find(query, FindSCU::_callback_wrapper, &encapsulated);
}

void 
FindSCU
::find(DcmDataset const * query, SimpleCallback callback) const
{
    // Encapsulate the simple callback into a full-featured callback
    auto full_callback = [&callback](void *, T_DIMSE_C_FindRQ *,
            int, T_DIMSE_C_FindRSP *, DcmDataset * dataset)
        {
            callback(dataset);
        };
    this->find(query, full_callback, NULL);
   
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

void
FindSCU
::_callback_wrapper(void * data, T_DIMSE_C_FindRQ * request, 
    int response_index, T_DIMSE_C_FindRSP * response, 
    DcmDataset * response_identifiers)
{
    FullCallbackData * encapsulated = 
        reinterpret_cast<FullCallbackData*>(data);
    encapsulated->callback(encapsulated->data, request, response_index, response, 
        response_identifiers);
}

void
FindSCU
::_find(DcmDataset const * query, 
    DIMSE_FindUserCallback callback, void * callback_data) const
{
    if(this->_association == NULL || !this->_association->is_associated())
    {
        throw Exception("Not associated");
    }
    
    T_ASC_PresentationContextID const presentation_id = 
        ASC_findAcceptedPresentationContextID(
            this->_association->get_association(), 
            this->_affected_sop_class.c_str());
    if(presentation_id == 0) 
    {
        throw Exception("No Presentation Context for Find Operation");
    }
    
    DIC_US const message_id = this->_association->get_association()->nextMsgID++;
    
    T_DIMSE_C_FindRQ request;
    memset(&request, 0, sizeof(request));
    
    request.MessageID = message_id;
    strcpy(request.AffectedSOPClassUID, this->_affected_sop_class.c_str());
    request.Priority = DIMSE_PRIORITY_LOW;
    
    T_DIMSE_C_FindRSP response;
    DcmDataset * status_detail = NULL;
    
    OFCondition const condition = DIMSE_findUser(
        this->_association->get_association(), presentation_id, 
        &request, const_cast<DcmDataset*>(query), 
        callback, callback_data, 
        DIMSE_BLOCKING, this->_network->get_timeout(), 
        &response, &status_detail);
    
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

}
