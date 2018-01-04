/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _350775b8_701f_4069_ab1e_c974a209389c
#define _350775b8_701f_4069_ab1e_c974a209389c

#include <memory>

#include "odil/AssociationAcceptor.h"
#include "odil/AssociationParameters.h"
#include "odil/dul/Transport.h"
#include "odil/odil.h"
#include "odil/dul/Object.h"

namespace odil
{

namespace dul
{

/// @brief Data related to events of the DUL state machine.
class ODIL_API EventData
{
public:
    Transport::Socket::endpoint_type peer_endpoint;
    std::shared_ptr<Object> pdu;
    AssociationParameters association_parameters;
    std::shared_ptr<AssociationRejected> reject;
};

}

}

#endif // _350775b8_701f_4069_ab1e_c974a209389c
