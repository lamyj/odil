/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/AAssociateRJ.h"

#include <cstdint>
#include <istream>

#include "odil/Exception.h"
#include "odil/dul/Object.h"

namespace odil
{

namespace dul
{

AAssociateRJ
::AAssociateRJ(unsigned char result, unsigned char source, unsigned char reason)
: PDU(type)
{
    this->_set_pdu_length(4);

    this->_item.add("Reserved-2", uint8_t(0));
    this->_item.add("Result", uint8_t(0));
    this->_item.add("Source", uint8_t(0));
    this->_item.add("Reason", uint8_t(0));

    this->set_result(result);
    this->set_source(source);
    this->set_reason(reason);
}

AAssociateRJ
::AAssociateRJ(std::istream & stream)
: PDU(type, stream)
{
    this->_item.read(stream, "Reserved-2", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Result", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Source", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Reason", Item::Field::Type::unsigned_int_8);
}

unsigned char
AAssociateRJ
::get_result() const
{
    return this->_item.as_unsigned_int_8("Result");
}

void
AAssociateRJ
::set_result(unsigned char result)
{
    if(result > 2)
    {
        throw Exception("Unknown result");
    }
    this->_item.as_unsigned_int_8("Result") = result;
}

unsigned char
AAssociateRJ
::get_source() const
{
    return this->_item.as_unsigned_int_8("Source");
}

void
AAssociateRJ
::set_source(unsigned char source)
{
    if(source > 3)
    {
        throw Exception("Unknown source");
    }
    this->_item.as_unsigned_int_8("Source") = source;
}

unsigned char
AAssociateRJ
::get_reason() const
{
    return this->_item.as_unsigned_int_8("Reason");
}

void
AAssociateRJ
::set_reason(unsigned char reason)
{
    if(reason > 10)
    {
        throw Exception("Unknown reason");
    }
    this->_item.as_unsigned_int_8("Reason") = reason;
}

}

}
