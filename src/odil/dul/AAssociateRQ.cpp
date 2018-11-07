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
: AAssociate(type)
{
    // Nothing else
}

AAssociateRQ
::AAssociateRQ(std::istream & stream)
: AAssociate(type, stream)
{
    // Nothing else
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
        if(item.as_unsigned_int_8("Item-type") == PresentationContextRQ::type)
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
            return item.as_unsigned_int_8("Item-type") == ApplicationContext::type; });

    std::transform(
        value.begin(), value.end(), std::back_inserter(new_items),
        [](PresentationContext const & x) { return x.get_item(); });

    std::copy_if(
        old_items.begin(), old_items.end(), std::back_inserter(new_items),
        [](Item const & item) {
            return item.as_unsigned_int_8("Item-type") == UserInformation::type; });

    this->_item.as_items("Variable-items") = new_items;
    this->_set_pdu_length(this->_compute_length());
}

}

}