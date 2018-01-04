/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/MaximumLength.h"

#include <cstdint>
#include <istream>

#include "odil/Exception.h"
#include "odil/dul/SubItem.h"

namespace odil
{

namespace dul
{

MaximumLength
::MaximumLength(uint32_t maximum_length)
: SubItem(type)
{
    this->_set_sub_item_length(4);
    this->_item.add("Maximum-length-received", uint32_t(0));

    this->set_maximum_length(maximum_length);
}

MaximumLength
::MaximumLength(std::istream & stream)
: SubItem(type, stream)
{
    this->_item.read(
        stream, "Maximum-length-received", Item::Field::Type::unsigned_int_32);
}

uint32_t
MaximumLength
::get_maximum_length() const
{
    return this->_item.as_unsigned_int_32("Maximum-length-received");
}

void
MaximumLength
::set_maximum_length(uint32_t value)
{
    this->_item.as_unsigned_int_32("Maximum-length-received") = value;
}

}

}
