/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "SCP.h"

#include "dcmtkpp/Association.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/message/Message.h"
#include "dcmtkpp/message/Request.h"

namespace dcmtkpp
{

SCP::DataSetGenerator
::~DataSetGenerator()
{
    // Nothing to do.
}

SCP
::SCP(Association & association)
: _association(association)
{
    // Nothing else.
}

SCP
::~SCP()
{
    // Nothing to do.
}

void
SCP
::receive_and_process()
{
    auto const message = this->_association.receive_message();
    (*this)(message);
}

}
