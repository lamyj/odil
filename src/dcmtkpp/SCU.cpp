/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/SCU.h"

#include <stdint.h>
#include <string>
#include <utility>
#include <vector>

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
: _association(NULL), _affected_sop_class("")
{
    // Nothing else
}

SCU
::SCU(SCU const & other)
:  _association(other._association), _affected_sop_class(other._affected_sop_class)
{
    // Nothing else
}

SCU const &
SCU
::operator=(SCU const & other)
{
    if(this != &other)
    {
        this->set_association(other.get_association());
        this->set_affected_sop_class(other.get_affected_sop_class());
    }
    
    return *this;
}

SCU
::~SCU()
{
    // Nothing to do.
}

Network *
SCU
::get_network() const
{
    return this->_network;
}

void
SCU
::set_network(Network * network)
{
    this->_network = network;
}

Association *
SCU
::get_association() const
{
    return this->_association;
}

void
SCU
::set_association(Association * association)
{
    this->_association = association;
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
    // FIXME: block mode and timeout
    OFCondition const condition = DIMSE_echoUser(
        this->_association->get_association(), message_id, DIMSE_BLOCKING, 30, 
        &status, &detail);
    
    if(condition.bad())
    {
        OFString empty;
        throw Exception(DimseCondition::dump(empty, condition).c_str());
    }
}

}
