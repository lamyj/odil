/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _952c6d4c_b331_4033_8476_5b0e75022b68
#define _952c6d4c_b331_4033_8476_5b0e75022b68

#include "odil/dul/PresentationContextRQ.h"

#include <cstdint>
#include <istream>
#include <string>
#include <vector>

#include "odil/Exception.h"
#include "odil/dul/PresentationContext.h"

namespace odil
{

namespace dul
{

PresentationContextRQ
::PresentationContextRQ(
    uint8_t id, std::string const & abstract_syntax,
    std::vector<std::string> const & transfer_syntaxes)
{
    this->_add_fields();

    this->_item.as_unsigned_int_8("Item-type") = 0x20;
    this->set_id(id);
    this->set_abstract_syntax(abstract_syntax);
    this->set_transfer_syntaxes(transfer_syntaxes);
}

PresentationContextRQ
::PresentationContextRQ(std::istream & stream)
: PresentationContext(stream)
{
    if(this->get_item_type() != 0x20)
    {
        throw Exception("Invalid item type");
    }
}

PresentationContextRQ
::~PresentationContextRQ()
{
    // Nothing to do.
}

std::string
PresentationContextRQ
::get_abstract_syntax() const
{
    auto const & syntaxes = this->_get_syntaxes("Abstract");
    if(syntaxes.empty())
    {
        throw Exception("No Abstract Syntax sub-item");
    }
    else if(syntaxes.size() > 1)
    {
        throw Exception("Several Abstract Syntax sub-items");
    }

    return syntaxes[0];
}

void
PresentationContextRQ
::set_abstract_syntax(std::string const & abstract_syntax)
{
    this->_set_syntaxes("Abstract", {abstract_syntax});
}

std::vector<std::string>
PresentationContextRQ
::get_transfer_syntaxes() const
{
    return this->_get_syntaxes("Transfer");
}

void
PresentationContextRQ
::set_transfer_syntaxes(std::vector<std::string> const & transfer_syntaxes)
{
    this->_set_syntaxes("Transfer", transfer_syntaxes);
}

}

}

#endif // _952c6d4c_b331_4033_8476_5b0e75022b68


