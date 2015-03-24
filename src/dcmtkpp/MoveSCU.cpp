/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/MoveSCU.h"

#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/StoreSCP.h"

namespace dcmtkpp
{

MoveSCU
::MoveSCU()
: SCU(), _move_destination("")
{
    // Nothing else.
}

MoveSCU
::~MoveSCU()
{
    // Nothing to do
}

std::string const & 
MoveSCU
::get_move_destination() const
{
    return this->_move_destination;
}

void
MoveSCU
::set_move_destination(std::string const & move_destination)
{
    this->_move_destination = move_destination;
}

void
MoveSCU
::move(DcmDataset const * query, Callback callback) const
{
    // Send the request
    DIC_US const message_id = this->_association->get_association()->nextMsgID++;
    T_DIMSE_C_MoveRQ request;
    memset(&request, 0, sizeof(request));
    
    request.MessageID = message_id;
    strcpy(request.AffectedSOPClassUID, this->_affected_sop_class.c_str());
    
    request.DataSetType = DIMSE_DATASET_PRESENT;
    request.Priority = DIMSE_PRIORITY_MEDIUM;
    
    strncpy(
        request.MoveDestination,
        this->_move_destination.c_str(), 16);
    
    // FIXME: include progress callback
    this->_send<DIMSE_C_MOVE_RQ>(
        request, this->_affected_sop_class, const_cast<DcmDataset*>(query));
    
    // Receive the responses
    Association store_association;
    bool done = false;
    while(!done)
    {
        // Use a small timeout to avoid blocking for a long time.
        if(!store_association.is_associated() && 
           this->_network->is_association_waiting(1))
        {
            store_association.receive(*this->_network, true);
        }
        
        done = this->_dispatch(store_association, callback);
    }
}

std::vector<DcmDataset *>
MoveSCU
::move(DcmDataset const * query) const
{
    std::vector<DcmDataset*> result;
    auto callback = [&result](DcmDataset * dataset) { 
        // We do not manage the allocation of dataset: clone it
        result.push_back(static_cast<DcmDataset*>(dataset->clone())); 
    };
    this->move(query, callback);
    
    return result;
}

bool 
MoveSCU
::_dispatch(Association & association, Callback callback) const
{
    T_ASC_Association *associations[2];
    int size = 0;

    associations[0] = this->_association->get_association();
    size = 1;
    associations[1] = association.get_association();
    if(association.get_association() != NULL) 
    {
        ++size;
    }
    
    // At this point, we should have a readable association.
    if(!ASC_selectReadableAssociation(associations, size, 1)) 
    {
        throw Exception("No readable association");
    }
    
    bool move_finished;
    
    if(associations[0] != NULL) 
    {
        move_finished = this->_handle_main_association();
    }
    else if(associations[1] != NULL) 
    {
        bool const release = 
            this->_handle_store_association(association, callback);
        if(release)
        {
            association.drop();
        }
    }
    
    return move_finished;
}

bool
MoveSCU
::_handle_main_association() const
{
    std::pair<T_ASC_PresentationContextID, T_DIMSE_Message> const command =
        this->_receive_command(DIMSE_BLOCKING);
    
    if(command.second.CommandField != DIMSE_C_MOVE_RSP)
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response Command Field: 0x" 
                << std::hex << command.second.CommandField;
        throw Exception(message.str());
    }
    
    T_DIMSE_C_MoveRSP const response = command.second.msg.CMoveRSP;
    if (response.DataSetType != DIMSE_DATASET_NULL) 
    {
        std::pair<T_ASC_PresentationContextID, DcmDataset *> dataset = 
            this->_receive_dataset(DIMSE_BLOCKING);
        delete dataset.second;
    }
    
    bool const done = (response.DimseStatus != STATUS_Pending);
    
    return done;
}

bool
MoveSCU
::_handle_store_association(Association & association, Callback callback) const
{
    StoreSCP scp;
    scp.set_network(this->_network);
    scp.set_association(&association);
    return scp.store(callback);
}

}
