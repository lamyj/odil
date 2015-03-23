/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _8ac39caa_b7b1_44a8_82fc_e8e3de18b2f8
#define _8ac39caa_b7b1_44a8_82fc_e8e3de18b2f8

#include "ServiceRole.h"

#include <unistd.h>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmnet/dimse.h>
#include <dcmtk/ofstd/ofcond.h>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

template<> struct ServiceRole::Traits<DIMSE_C_FIND_RQ> { typedef T_DIMSE_C_FindRQ Type; };
template<> struct ServiceRole::Traits<DIMSE_C_GET_RQ> { typedef T_DIMSE_C_GetRQ Type; };
template<> struct ServiceRole::Traits<DIMSE_C_MOVE_RQ> { typedef T_DIMSE_C_MoveRQ Type; };
template<> struct ServiceRole::Traits<DIMSE_C_STORE_RQ> { typedef T_DIMSE_C_StoreRQ Type; };
template<> struct ServiceRole::Traits<DIMSE_C_STORE_RSP> { typedef T_DIMSE_C_StoreRSP Type; };

template<T_DIMSE_Command VCommand>
void
ServiceRole
::_send(
    typename Traits<VCommand>::Type const & command, 
    std::string const & abstract_syntax, DcmDataset* payload,
    ProgressCallback callback, void* callback_data) const
{
    this->_check_dimse_ready();
    
    T_DIMSE_Message message; 
    memset(static_cast<void*>(&message), 0, sizeof(message));
    
    message.CommandField = VCommand;
    typedef typename Traits<VCommand>::Type CommandType;
    // Generic access to union member
    *(reinterpret_cast<CommandType*>(&message.msg)) = command;
    
    // Encapsulate the callback and its data
    ProgressCallbackData encapsulated;
    if(callback != NULL)
    {
        encapsulated.callback = callback;
        encapsulated.data = callback_data;
    }
    
    OFCondition const condition = DIMSE_sendMessageUsingMemoryData(
        this->_association->get_association(), 
        this->_find_presentation_context(abstract_syntax), 
        &message, NULL /* status_detail */,
        payload, 
        (callback != NULL)?(ServiceRole::_progress_callback_wrapper):NULL, 
        (callback != NULL)?(&encapsulated):NULL,
        NULL /* commandSet */);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

}

#endif // _8ac39caa_b7b1_44a8_82fc_e8e3de18b2f8
