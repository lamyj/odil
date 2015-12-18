/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ServiceRole.h"

#include <unistd.h>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/DcmtkAssociation.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Reader.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Writer.h"

namespace dcmtkpp
{

ServiceRole
::ServiceRole()
: _network(NULL), _association(NULL)
{
    // Nothing else
}

ServiceRole
::ServiceRole(Network * network, DcmtkAssociation * association)
{
    this->set_network(network);
    this->set_association(association);
}

ServiceRole
::ServiceRole(ServiceRole const & other)
: _network(other._network), _association(other._association)
{
    // Nothing else
}

ServiceRole &
ServiceRole
::operator=(ServiceRole const & other)
{
    if(this != &other)
    {
        this->set_association(other.get_association());
        this->set_network(other.get_network());
    }
    
    return *this;
}

ServiceRole
::~ServiceRole()
{
    // Nothing to do.
}

Network *
ServiceRole
::get_network() const
{
    return this->_network;
}

void
ServiceRole
::set_network(Network * network)
{
    this->_network = network;
}

DcmtkAssociation *
ServiceRole
::get_association() const
{
    return this->_association;
}

void
ServiceRole
::set_association(DcmtkAssociation * association)
{
    this->_association = association;
}

}
