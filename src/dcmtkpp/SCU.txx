/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _8ac39caa_b7b1_44a8_82fc_e8e3de18b2f8
#define _8ac39caa_b7b1_44a8_82fc_e8e3de18b2f8

#include "SCU.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmnet/dimse.h>
#include <dcmtk/ofstd/ofcond.h>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

template<> struct SCU::Traits<DIMSE_C_FIND_RQ> { typedef T_DIMSE_C_FindRQ Type; };
template<> struct SCU::Traits<DIMSE_C_GET_RQ> { typedef T_DIMSE_C_GetRQ Type; };
template<> struct SCU::Traits<DIMSE_C_STORE_RQ> { typedef T_DIMSE_C_StoreRQ Type; };
template<> struct SCU::Traits<DIMSE_C_STORE_RSP> { typedef T_DIMSE_C_StoreRSP Type; };

template<T_DIMSE_Command VCommand>
void
SCU
::_send(typename Traits<VCommand>::Type const & command, DcmDataset* payload, 
    ProgressCallback callback, void* callback_data) const
{
    T_DIMSE_Message message; 
    bzero((char*)&message, sizeof(message));
    
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
        this->_association->get_association(), this->_find_presentation_context(), 
        &message, NULL /* status_detail */,
        payload, 
        (callback != NULL)?(SCU::_progress_callback_wrapper):NULL, 
        (callback != NULL)?(&encapsulated):NULL,
        NULL /* commandSet */);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

}

#endif // _8ac39caa_b7b1_44a8_82fc_e8e3de18b2f8
