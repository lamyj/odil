/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/AAssociateRQ.h"

#include <algorithm>
#include <sstream>
#include <vector>

#include "odil/Exception.h"
#include "odil/dul/AAssociate.h"
#include "odil/dul/PresentationContextRQ.h"

namespace odil
{

namespace dul
{

AAssociateRQ
::AAssociateRQ()
: AAssociate()
{
    this->_item.as_unsigned_int_8("PDU-type") = 0x01;
}

AAssociateRQ
::AAssociateRQ(std::istream & stream)
: AAssociate(stream)
{
    if(this->_item.as_unsigned_int_8("PDU-type") != 0x01)
    {
        throw Exception("Invalid PDU type");
    }
}

AAssociateRQ
::~AAssociateRQ()
{
    // Nothing to do.
}

std::vector<PresentationContextRQ>
AAssociateRQ
::get_presentation_contexts() const
{
    std::vector<PresentationContextRQ> result;
    for(auto const & item: this->_item.as_items("Variable-items"))
    {
        if(item.as_unsigned_int_8("Item-type") == 0x20)
        {
            std::stringstream stream;
            stream << item;
            result.push_back(PresentationContextRQ(stream));
        }
    }

    return result;
}

void
AAssociateRQ
::set_presentation_contexts(std::vector<PresentationContextRQ> const & value)
{
    auto const & old_items = this->_item.as_items("Variable-items");
    std::vector<Item> new_items;

    std::copy_if(
        old_items.begin(), old_items.end(), std::back_inserter(new_items),
        [](Item const & item)  {
            return item.as_unsigned_int_8("Item-type") == 0x10; });

    std::transform(
        value.begin(), value.end(), std::back_inserter(new_items),
        [](PresentationContext const & x) { return x.get_item(); });

    std::copy_if(
        old_items.begin(), old_items.end(), std::back_inserter(new_items),
        [](Item const & item) {
            return item.as_unsigned_int_8("Item-type") == 0x50; });

    this->_item.as_items("Variable-items") = new_items;
    this->_item.as_unsigned_int_32("PDU-length") = this->_compute_length();
}

}

}
