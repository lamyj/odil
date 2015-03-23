/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/Network.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/cond.h>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

Network
::Network()
: _role(NET_REQUESTOR), _port(0), _timeout(30), _options(0), _network(NULL)
{
    // Nothing else.
}

Network
::Network(T_ASC_NetworkRole role, int port, int timeout, unsigned long options)
: _role(role), _port(port), _timeout(timeout), _options(options), _network(NULL)
{
    // Nothing else.
}

Network
::Network(Network const & other)
: _role(other.get_role()), _port(other.get_port()), 
  _timeout(other.get_timeout()), _options(other.get_options()), _network(NULL)
{
    // Nothing else
}

Network
::~Network()
{
    if(this->is_initialized())
    {
        this->drop();
    }
}

Network &
Network
::operator=(Network const & other)
{
    if(this != &other)
    {
        this->set_role(other.get_role());
        this->set_port(other.get_port());
        this->set_timeout(other.get_timeout());
        this->set_options(other.get_options());
    }
    
    return *this;
}

T_ASC_NetworkRole
Network
::get_role() const
{
    return this->_role;
}

void
Network
::set_role(T_ASC_NetworkRole role)
{
    if(this->is_initialized())
    {
        throw Exception("Cannot set member while initialized");
    }
    
    this->_role = role;
}

int
Network
::get_port() const
{
    return this->_port;
}

void
Network
::set_port(int port)
{
    if(this->is_initialized())
    {
        throw Exception("Cannot set member while initialized");
    }
    
    this->_port = port;
}

int
Network
::get_timeout() const
{
    return this->_timeout;
}

void
Network
::set_timeout(int timeout)
{
    if(this->is_initialized())
    {
        throw Exception("Cannot set member while initialized");
    }
    
    this->_timeout = timeout;
}

unsigned long
Network
::get_options() const
{
    return this->_options;
}

void
Network
::set_options(unsigned long options)
{
    if(this->is_initialized())
    {
        throw Exception("Cannot set member while initialized");
    }
    
    this->_options = options;
}

void
Network
::initialize()
{
    if(this->is_initialized())
    {
        throw Exception("Already initialized");
    }
    
    OFCondition const condition = ASC_initializeNetwork(
        this->_role, this->_port, this->_timeout, &this->_network, 
        this->_options);
    
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

T_ASC_Network *
Network
::get_network()
{
    return this->_network;
}

bool 
Network
::is_association_waiting()
{
    return ASC_associationWaiting(this->_network, this->_timeout);
}

void
Network
::drop()
{
    if(!this->is_initialized())
    {
        throw Exception("Not initialized");
    }
    
    OFCondition const condition = ASC_dropNetwork(&this->_network);
    
    if(condition.bad())
    {
        throw Exception(condition);
    }
    
    this->_network = NULL;
}

bool
Network
::is_initialized() const
{
    return (this->_network != NULL);
}

}
