/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ServiceRole.h"

#include <unistd.h>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

ServiceRole
::ServiceRole()
: _association(NULL), _network(NULL)
{
    // Nothing else
}

ServiceRole
::ServiceRole(ServiceRole const & other)
: _association(other._association), _network(other._network)
{
    // Nothing else
}

ServiceRole const &
ServiceRole
::operator=(ServiceRole const & other)
{
    if(this != &other)
    {
        this->set_association(other.get_association());
        this->set_network(other.get_network());
    }
    
    return *this;
}

ServiceRole
::~ServiceRole()
{
    // Nothing to do.
}

Network *
ServiceRole
::get_network() const
{
    return this->_network;
}

void
ServiceRole
::set_network(Network * network)
{
    this->_network = network;
}

Association *
ServiceRole
::get_association() const
{
    return this->_association;
}

void
ServiceRole
::set_association(Association * association)
{
    this->_association = association;
}

void 
ServiceRole
::_progress_callback_wrapper(void * data, unsigned long bytes_count)
{
    ProgressCallbackData * encapsulated = 
        reinterpret_cast<ProgressCallbackData*>(data);
    encapsulated->callback(encapsulated->data, bytes_count);
}

T_ASC_PresentationContextID
ServiceRole
::_find_presentation_context(std::string const & abstract_syntax) const
{
    T_ASC_PresentationContextID const presentation_id = 
        ASC_findAcceptedPresentationContextID(
            this->_association->get_association(), 
            abstract_syntax.c_str());
    if(presentation_id == 0) 
    {
        throw Exception("No Presentation Context for Get Operation");
    }
    
    return presentation_id;
}

std::pair<T_ASC_PresentationContextID, T_DIMSE_Message>
ServiceRole
::_receive_command(T_DIMSE_BlockingMode block_mode) const
{
    this->_check_dimse_ready();
    
    std::pair<T_ASC_PresentationContextID, T_DIMSE_Message> result;
    
    result.first = -1;
    memset(static_cast<void*>(&result.second), 0, sizeof(result.second));
    
    OFCondition const condition = DIMSE_receiveCommand(
        this->_association->get_association(), block_mode, 
        this->_network->get_timeout(), 
        &result.first, &result.second, 
        NULL /*statusDetail*/, NULL /*commandSet*/);
    
    if(condition.bad())
    {
        throw Exception(condition);
    }
    
    return result;
}

std::pair<T_ASC_PresentationContextID, DcmDataset *>
ServiceRole
::_receive_dataset(
    T_DIMSE_BlockingMode block_mode,
    ProgressCallback callback, void* callback_data) const
{
    this->_check_dimse_ready();
    
    std::pair<T_ASC_PresentationContextID, DcmDataset *> result;
    result.second = NULL;
    
    // Encapsulate the callback and its data
    ProgressCallbackData encapsulated;
    if(callback != NULL)
    {
        encapsulated.callback = callback;
        encapsulated.data = callback_data;
    }
    
    OFCondition const condition = DIMSE_receiveDataSetInMemory(
        this->_association->get_association(), block_mode, 
        this->_network->get_timeout(), 
        &result.first, &result.second, 
        (callback != NULL)?(ServiceRole::_progress_callback_wrapper):NULL, 
        (callback != NULL)?(&encapsulated):NULL
    );
    
    if(condition.bad())
    {
        throw Exception(condition);
    }
    
    return result;
}

void
ServiceRole
::_check_dimse_ready() const
{
    if(this->_network == NULL)
    {
        throw Exception("No network");
    }
    else if(!this->_network->is_initialized())
    {
        throw Exception("Network is not initialized");
    }
    else if(this->_association == NULL)
    {
        throw Exception("No association");
    }
    else if(!this->_association->is_associated())
    {
        throw Exception("Not associated");
    }
}

}
