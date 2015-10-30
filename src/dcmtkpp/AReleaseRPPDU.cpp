/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/AReleaseRPPDU.h"

#include <cstdint>

#include "dcmtkpp/endian.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/ProtocolDataUnit.h"

namespace dcmtkpp
{

AReleaseRPPDU
::AReleaseRPPDU()
: ProtocolDataUnit(A_RELEASE_RP)
{
    // Nothing else
}

/// @brief Constructor for binary data.
AReleaseRPPDU
::AReleaseRPPDU(Data const & data)
: ProtocolDataUnit(A_RELEASE_RP)
{
    if(data.size() != 10)
    {
        throw Exception("Invalid data");
    }
    if(data[0] != this->get_pdu_type())
    {
        throw Exception("Not an A-RELEASE-RP PDU");
    }
}

AReleaseRPPDU
::~AReleaseRPPDU()
{
    // Nothing to do.
}

ProtocolDataUnit::Data
AReleaseRPPDU
::as_binary() const
{
    Data data(10);
    data[0] = this->get_pdu_type();
    data[1] = 0;
    *reinterpret_cast<uint32_t*>(&data[2]) = htobe32(0x0004);
    data[6] = 0;
    data[7] = 0;
    data[8] = 0;
    data[9] = 0;

    return data;
}

}
