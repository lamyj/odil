/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Message.h"

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dctagkey.h>
#include <dcmtk/dcmnet/dimse.h>
#include <dcmtk/ofstd/oftypes.h>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

Message
::Message()
{
    this->set_data_set(NULL);
}

Message
::~Message()
{
    // Nothing to do.
}

DcmDataset const & 
Message
::get_command_set() const
{
    return this->_command_set;
}

DcmDataset const *
Message
::get_data_set() const
{
    return this->_data_set;
}

void
Message
::set_data_set(DcmDataset * data_set)
{
    this->_data_set = data_set;
    
    Uint16 command_dataset_type;
    if(data_set == NULL || data_set->isEmpty())
    {
        command_dataset_type = DIMSE_DATASET_NULL;
    }
    else
    {
        command_dataset_type = DIMSE_DATASET_PRESENT;
    }
    
    auto const condition = this->_command_set.putAndInsertUint16(
        DcmTagKey(0x0000, 0x0800), command_dataset_type);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

Uint16 
Message
::get_command_field() const
{
    auto command_set = const_cast<DcmDataset &>(this->_command_set);
    Uint16 command_field;
    
    auto const condition = command_set.findAndGetUint16(
        DCM_CommandField, command_field);
    if(condition.bad())
    {
        throw Exception(condition);
    }
    
    return command_field;
}

void 
Message
::set_command_field(Uint16 command_field)
{
    auto const condition = this->_command_set.putAndInsertUint16(
        DCM_CommandField, command_field);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

}
