/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/SCU.h"

#include <string>

#include "odil/Association.h"
#include "odil/Exception.h"
#include "odil/message/CEchoRequest.h"
#include "odil/message/CEchoResponse.h"
#include "odil/message/Message.h"
#include "odil/registry.h"

namespace odil
{

SCU
::SCU(Association & association)
: _association(association), _affected_sop_class("")
{
    // Nothing else.
}

SCU
::~SCU()
{
    // Nothing to do.
}

std::string const &
SCU
::get_affected_sop_class() const
{
    return this->_affected_sop_class;
}
    
void 
SCU
::set_affected_sop_class(std::string const & sop_class)
{
    this->_affected_sop_class = sop_class;
}

}
