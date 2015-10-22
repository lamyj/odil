/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f4680d8c_18a8_4317_956d_3ae238cb39cc
#define _f4680d8c_18a8_4317_956d_3ae238cb39cc

#include "dcmtkpp/Association.h"
#include "dcmtkpp/CEchoRequest.h"
#include "dcmtkpp/Message.h"
#include "dcmtkpp/Network.h"
#include "dcmtkpp/ServiceRole.h"

namespace dcmtkpp
{

/// @brief Base class for all Service Class Providers.
class SCP: public ServiceRole
{
public:
    /// @brief Create a default Service Class Provider with no network and no association.
    SCP();

    /// @brief Create a Service Class Provider with network and association.
    SCP(Network * network, Association * association);

    /// @brief Destructor
    virtual ~SCP();

    /// @brief Receive and process a message.
    void receive_and_process();

    /// @brief Process a message.
    virtual void operator()(Message const & message) =0;
protected:
    /// @brief Send a C-ECHO response.
    void _send_echo_response(CEchoRequest const & request) const;
};

}

#endif // _f4680d8c_18a8_4317_956d_3ae238cb39cc
