/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/AAssociateRJPDU.h"

#include <cstdint>

#include "dcmtkpp/endian.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/ProtocolDataUnit.h"

namespace dcmtkpp
{

AAssociateRJPDU
::AAssociateRJPDU(unsigned char source, unsigned char reason)
: ProtocolDataUnit(A_ASSOCIATE_RJ)
{
    this->set_source(source);
    this->set_reason(reason);
}

/// @brief Constructor for binary data.
AAssociateRJPDU
::AAssociateRJPDU(Data const & data)
: ProtocolDataUnit(A_ASSOCIATE_RJ)
{
    if(data.size() != 10)
    {
        throw Exception("Invalid data");
    }
    if(data[0] != this->get_pdu_type())
    {
        throw Exception("Not an A_ASSOCIATE_RJ PDU");
    }

    this->set_source(data[8]);
    this->set_reason(data[9]);
}

AAssociateRJPDU
::~AAssociateRJPDU()
{
    // Nothing to do.
}

unsigned char
AAssociateRJPDU
::get_source() const
{
    return this->_source;
}

void
AAssociateRJPDU
::set_source(unsigned char source)
{
    if(source > 3)
    {
        throw Exception("Unknown source");
    }
    this->_source = source;
}

unsigned char
AAssociateRJPDU
::get_reason() const
{
    return this->_reason;
}

void
AAssociateRJPDU
::set_reason(unsigned char reason)
{
    if(reason > 10)
    {
        throw Exception("Unknown reason");
    }
    this->_reason = reason;
}

ProtocolDataUnit::Data
AAssociateRJPDU
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
