/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Message.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

Message
::Message()
{
    this->_command_set.add(registry::CommandDataSetType, { DIMSE_DATASET_NULL });
}

Message
::Message(DataSet const & command_set)
: _command_set(command_set)
{
    if(!this->_command_set.has(registry::CommandDataSetType))
    {
        this->_command_set.add(registry::CommandDataSetType, VR::US);
    }
    this->_command_set.as_int(registry::CommandDataSetType) = { DIMSE_DATASET_NULL };
}

Message
::Message(DataSet const & command_set, DataSet const & data_set)
: _command_set(command_set)
{
    if(!this->_command_set.has(registry::CommandDataSetType))
    {
        this->_command_set.add(registry::CommandDataSetType, VR::US);
    }
    this->set_data_set(data_set);
}

Message
::~Message()
{
    // Nothing to do.
}

DataSet const &
Message
::get_command_set() const
{
    return this->_command_set;
}

bool
Message
::has_data_set() const
{
    return (this->_command_set.as_int(registry::CommandDataSetType, 0) == DIMSE_DATASET_PRESENT);
}

DataSet const &
Message
::get_data_set() const
{
    if(!this->has_data_set())
    {
        throw Exception("No data set in message");
    }
    return this->_data_set;
}

void
Message
::set_data_set(DataSet const & data_set)
{
    this->_data_set = data_set;
    this->_command_set.as_int(registry::CommandDataSetType) = { DIMSE_DATASET_PRESENT };
}

void
Message
::delete_data_set()
{
    this->_command_set.as_int(registry::CommandDataSetType) = { DIMSE_DATASET_NULL };
    this->_data_set = DataSet();
}

}
