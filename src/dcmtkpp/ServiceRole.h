/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _fa7d372a_dd27_4a1e_9b29_be9d5fbe602a
#define _fa7d372a_dd27_4a1e_9b29_be9d5fbe602a

#include <functional>
#include <utility>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/assoc.h>

#include "dcmtkpp/DcmtkAssociation.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/message/Message.h"
#include "dcmtkpp/Network.h"

namespace dcmtkpp
{

/// @brief Base class for all Service Class Users and Providers.
class ServiceRole
{
public:
    /// @brief Create a default Service Role with no network and no association.
    ServiceRole();

    /// @brief Create a Service Role with network and association.
    ServiceRole(Network * network, DcmtkAssociation * association);
    
    /// @brief Copy the other service role.
    ServiceRole(ServiceRole const & other);
    
    /// @brief Copy the other service role.
    ServiceRole & operator=(ServiceRole const & other);
    
    /// @brief Destructor, network and association are not modified.
    virtual ~ServiceRole();
    
    /// @brief Return the network used by the ServiceRole.
    Network * get_network() const;
    /// @brief Set the network used by the ServiceRole.
    void set_network(Network * network);
    
    /// @brief Return the association used by the ServiceRole.
    DcmtkAssociation * get_association() const;
    /// @brief Set the association used by the ServiceRole.
    void set_association(DcmtkAssociation * association);

protected:
    /// @brief Network used by the ServiceRole.
    Network * _network;
    
    /// @brief Association used by the ServiceRole.
    DcmtkAssociation * _association;

private:

};

}

#endif // _fa7d372a_dd27_4a1e_9b29_be9d5fbe602a
