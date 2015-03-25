/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Request.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Message.h"

namespace dcmtkpp
{

Request
::Request(Uint16 message_id)
: Message()
{
    this->set_message_id(message_id);
}

Request
::~Request()
{
    // Nothing to do.
}

Uint16 
Request
::get_message_id() const
{
    auto command_set = const_cast<DcmDataset &>(this->_command_set);
    Uint16 message_id;
    
    auto const condition = command_set.findAndGetUint16(
        DCM_MessageID, message_id);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

void 
Request
::set_message_id(Uint16 message_id)
{
    auto const condition = this->_command_set.putAndInsertUint16(
        DCM_MessageID, message_id);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

}
