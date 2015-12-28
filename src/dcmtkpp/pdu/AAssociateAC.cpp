/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/pdu/AAssociateAC.h"

#include <algorithm>
#include <sstream>
#include <vector>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/pdu/AAssociate.h"
#include "dcmtkpp/pdu/PresentationContextAC.h"

namespace dcmtkpp
{

namespace pdu
{

AAssociateAC
::AAssociateAC()
: AAssociate()
{
    this->_item.as_unsigned_int_8("PDU-type") = 0x02;
}

AAssociateAC
::AAssociateAC(std::istream & stream)
: AAssociate(stream)
{
    if(this->_item.as_unsigned_int_8("PDU-type") != 0x02)
    {
        throw Exception("Invalid PDU type");
    }
}

AAssociateAC
::~AAssociateAC()
{
    // Nothing to do.
}

std::vector<PresentationContextAC>
AAssociateAC
::get_presentation_contexts() const
{
    std::vector<PresentationContextAC> result;
    for(auto const & item: this->_item.as_items("Variable-items"))
    {
        if(item.as_unsigned_int_8("Item-type") == 0x21)
        {
            std::stringstream stream;
            stream << item;
            result.push_back(PresentationContextAC(stream));
        }
    }

    return result;
}

void
AAssociateAC
::set_presentation_contexts(std::vector<PresentationContextAC> const & value)
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
