/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/SCU.h"

#include <string>

#include <unistd.h>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmnet/cond.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

SCU
::SCU()
: ServiceRole(), _affected_sop_class("")
{
    // Nothing else
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

void
SCU
::echo() const
{
    if(this->_association == NULL || !this->_association->is_associated())
    {
        throw Exception("Not associated");
    }
    
    DIC_US const message_id = this->_association->get_association()->nextMsgID++;
    DIC_US status;
    DcmDataset *detail = NULL;
    // FIXME: block mode
    OFCondition const condition = DIMSE_echoUser(
        this->_association->get_association(), message_id, DIMSE_BLOCKING, 
        this->_network->get_timeout(), 
        &status, &detail);
    
    if(condition.bad())
    {
        OFString empty;
        throw Exception(condition);
    }
}

}
