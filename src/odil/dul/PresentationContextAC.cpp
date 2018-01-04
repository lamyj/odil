/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/PresentationContextAC.h"

#include <cstdint>
#include <istream>
#include <string>

#include "odil/Exception.h"
#include "odil/dul/PresentationContext.h"

namespace odil
{

namespace dul
{

PresentationContextAC
::PresentationContextAC(
    uint8_t id, std::string const & transfer_syntax, uint8_t result_reason)
{
    this->_add_fields();
    this->_item.as_unsigned_int_8("Item-type") = 0x21;
    this->set_id(id);
    this->set_transfer_syntax(transfer_syntax);
    this->set_result_reason(result_reason);
}

PresentationContextAC
::PresentationContextAC(std::istream & stream)
: PresentationContext(stream)
{
    if(this->get_item_type() != 0x21)
    {
        throw Exception("Invalid item type");
    }
}

PresentationContextAC
::~PresentationContextAC()
{
    // Nothing to do.
}

uint8_t
PresentationContextAC
::get_result_reason() const
{
    return this->_item.as_unsigned_int_8("Result/Reason");
}

void
PresentationContextAC
::set_result_reason(uint8_t result_reason)
{
    this->_item.as_unsigned_int_8("Result/Reason") = result_reason;
}

std::string
PresentationContextAC
::get_transfer_syntax() const
{
    auto const & syntaxes = this->_get_syntaxes("Transfer");
    if(syntaxes.empty())
    {
        throw Exception("No Transfer Syntax sub-item");
    }
    else if(syntaxes.size() > 1)
    {
        throw Exception("Several Transfer Syntax sub-items");
    }

    return syntaxes[0];
}

void
PresentationContextAC
::set_transfer_syntax(std::string const & transfer_syntax)
{
    this->_set_syntaxes("Transfer", {transfer_syntax});
}

}

}
