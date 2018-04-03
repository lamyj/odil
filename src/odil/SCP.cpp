/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "SCP.h"

#include "odil/Association.h"
#include "odil/DataSet.h"
#include "odil/message/Message.h"
#include "odil/message/Request.h"

namespace odil
{

SCP::DataSetGenerator
::~DataSetGenerator()
{
    // Nothing to do.
}

SCP::Exception
::Exception(
    std::string const & message,
    Value::Integer status, std::shared_ptr<DataSet> status_fields)
: ::odil::Exception(message), status(status), status_fields(status_fields)
{
    // Nothing else.
}

SCP::Exception
::~Exception() noexcept
{
    // Nothing to do.
}

SCP
::SCP(Association & association)
: _association(association)
{
    // Nothing else.
}

void
SCP
::receive_and_process()
{
    auto message = this->_association.receive_message();
    (*this)(message);
}

}
