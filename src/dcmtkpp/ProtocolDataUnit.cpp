/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/ProtocolDataUnit.h"

#include <cstdint>
#include <memory>
#include <vector>

#include "dcmtkpp/AAbortPDU.h"
#include "dcmtkpp/AAssociateRJPDU.h"
#include "dcmtkpp/AReleaseRPPDU.h"
#include "dcmtkpp/AReleaseRQPDU.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/PDataTFPDU.h"

namespace dcmtkpp
{

std::shared_ptr<ProtocolDataUnit>
ProtocolDataUnit
::factory(Data const & data)
{
    if(data.size() < 1)
    {
        throw Exception("Invalid data");
    }

    unsigned char const pdu_type = data[0];

    if(pdu_type == A_ASSOCIATE_RJ)
    {
        return std::make_shared<AAssociateRJPDU>(data);
    }
    else if(pdu_type == P_DATA_TF)
    {
        return std::make_shared<PDataTFPDU>(data);
    }
    else if(pdu_type == A_RELEASE_RQ)
    {
        return std::make_shared<AReleaseRQPDU>(data);
    }
    else if(pdu_type == A_RELEASE_RP)
    {
        return std::make_shared<AReleaseRPPDU>(data);
    }
    else if(pdu_type == A_ABORT)
    {
        return std::make_shared<AAbortPDU>(data);
    }
    else
    {
        throw Exception("Unknown PDU type");
    }
}

ProtocolDataUnit
::ProtocolDataUnit(Type pdu_type)
: _pdu_type(pdu_type)
{
    // Nothing else.
}

ProtocolDataUnit
::~ProtocolDataUnit()
{
    // Nothing to do.
}

ProtocolDataUnit::Type
ProtocolDataUnit
::get_pdu_type() const
{
    return this->_pdu_type;
}

}
