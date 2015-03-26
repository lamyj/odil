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

#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

Message
::Message()
{
    ElementAccessor<EVR_UL>::set(this->_command_set, DCM_CommandGroupLength, 0);
    this->set_data_set(NULL);
}

Message
::Message(DcmDataset const & command_set, DcmDataset * data_set)
: _command_set(command_set)
{
    this->set_data_set(data_set);
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
::set_data_set(const DcmDataset * data_set)
{
    this->_data_set = data_set;
    
    Uint16 command_dataset_type;
    if(data_set == NULL || const_cast<DcmDataset*>(data_set)->isEmpty())
    {
        command_dataset_type = DIMSE_DATASET_NULL;
    }
    else
    {
        command_dataset_type = DIMSE_DATASET_PRESENT;
    }
    
    ElementAccessor<EVR_US>::set(
        this->_command_set, DcmTagKey(0x0000, 0x0800), command_dataset_type);
}

void
Message
::delete_data_set()
{
    if(this->_data_set != NULL)
    {
        delete this->_data_set;
        this->set_data_set(NULL);
    }
}

Uint16 
Message
::get_command_field() const
{
    return ElementAccessor<EVR_US>::get(this->_command_set, DCM_CommandField);
}

void 
Message
::set_command_field(Uint16 command_field)
{
    ElementAccessor<EVR_US>::set(
        this->_command_set, DCM_CommandField, command_field);
}

}
