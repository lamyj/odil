/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/AAbortPDU.h"

#include <cstdint>

#include "dcmtkpp/endian.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/ProtocolDataUnit.h"

namespace dcmtkpp
{

AAbortPDU
::AAbortPDU(unsigned char source, unsigned char reason)
: ProtocolDataUnit(A_ABORT)
{
    this->set_source(source);
    this->set_reason(reason);
}

/// @brief Constructor for binary data.
AAbortPDU
::AAbortPDU(Data const & data)
: ProtocolDataUnit(A_ABORT)
{
    if(data.size() != 10)
    {
        throw Exception("Invalid data");
    }
    if(data[0] != this->get_pdu_type())
    {
        throw Exception("Not an A-ABORT PDU");
    }

    this->set_source(data[8]);
    this->set_reason(data[9]);
}

AAbortPDU
::~AAbortPDU()
{
    // Nothing to do.
}

unsigned char
AAbortPDU
::get_source() const
{
    return this->_source;
}

void
AAbortPDU
::set_source(unsigned char source)
{
    if(source > 2)
    {
        throw Exception("Unknown source");
    }
    this->_source = source;
}

unsigned char
AAbortPDU
::get_reason() const
{
    return this->_reason;
}

void
AAbortPDU
::set_reason(unsigned char reason)
{
    if(reason > 6)
    {
        throw Exception("Unknown reason");
    }
    this->_reason = reason;
}

ProtocolDataUnit::Data
AAbortPDU
::as_binary() const
{
    Data data(10);
    data[0] = this->get_pdu_type();
    data[1] = 0;
    *reinterpret_cast<uint32_t*>(&data[2]) = htobe32(0x0004);
    data[6] = 0;
    data[7] = 0;
    data[8] = this->get_source();
    data[9] = this->get_reason();

    return data;
}

}
