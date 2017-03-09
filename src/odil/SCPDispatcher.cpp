/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/Association.h"
#include "odil/Exception.h"
#include "odil/SCP.h"
#include "odil/SCPDispatcher.h"
#include "odil/Value.h"

#include <map>
#include <memory>
#include <sstream>

namespace odil
{

SCPDispatcher
::SCPDispatcher(Association& association)
    : _association(association)
{
    // Nothing else.
}

SCPDispatcher
::~SCPDispatcher()
{
    // Nothing to do.
}

bool
SCPDispatcher
::has_scp(Value::Integer command) const
{
    auto const it = this->_providers.find(command);
    return (it != this->_providers.end());
}

std::shared_ptr<SCP> const&
SCPDispatcher
::get_scp(Value::Integer command) const
{
    auto const it = this->_providers.find(command);
    if(it == this->_providers.end())
    {
        throw Exception("No such provider");
    }
    return it->second;
}

void
SCPDispatcher
::set_scp(Value::Integer command, std::shared_ptr<SCP> const& scp)
{
    this->_providers[command] = scp;
}

void
SCPDispatcher
::dispatch()
{
    auto const message = this->_association.receive_message();

    auto const it = this->_providers.find(message.get_command_field());
    if(it == this->_providers.end())
    {
        std::ostringstream error_message;
        error_message << "No provider for: " << message.get_command_field();
        throw Exception(error_message.str());
    }

    auto& scp = *(it->second);
    scp(message);
}

}
