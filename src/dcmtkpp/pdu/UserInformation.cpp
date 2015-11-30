/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/pdu/UserInformation.h"

#include <algorithm>
#include <istream>
#include <vector>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/pdu/ImplementationClassUID.h"
#include "dcmtkpp/pdu/ImplementationVersionName.h"
#include "dcmtkpp/pdu/MaximumLength.h"
#include "dcmtkpp/pdu/Object.h"
#include "dcmtkpp/pdu/UserIdentityAC.h"
#include "dcmtkpp/pdu/UserIdentityRQ.h"

namespace dcmtkpp
{

namespace pdu
{

UserInformation
::UserInformation()
{
    this->_item.add("Item-type", uint8_t(0x50));
    this->_item.add("Reserved", uint8_t(0));
    this->_item.add("Item-length", uint16_t(4));
    this->_item.add("User-data", std::vector<Item>());
}

UserInformation
::UserInformation(std::istream & stream)
{
    this->_item.read(stream, "Item-type", Item::Field::Type::unsigned_int_8);
    if(this->_item.as_unsigned_int_8("Item-type") != 0x50)
    {
        throw Exception("Invalid item type");
    }

    this->_item.read(stream, "Reserved", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Item-length", Item::Field::Type::unsigned_int_16);

    this->_item.add("User-data", std::vector<Item>());

    auto const begin = stream.tellg();
    auto const item_length = this->_item.as_unsigned_int_16("Item-length");

    while(stream.tellg()-begin < item_length)
    {
        uint8_t const type = stream.peek();
        if(type == 0x51)
        {
            MaximumLength const sub_item(stream);
            this->set_sub_item(sub_item);
        }
        else if(type == 0x52)
        {
            ImplementationClassUID const sub_item(stream);
            this->set_sub_item(sub_item);
        }
        else if(type == 0x55)
        {
            ImplementationVersionName const sub_item(stream);
            this->set_sub_item(sub_item);
        }
        // 0x53: Asynchronous Operations Window, PS 3.7, D.3.3.3.1
        // 0x54: SCP/SCU Role Selection, PS 3.7, D.3.3.4.1
        // 0x56: SOP Class Extended Negotiation, PS 3.7, D.3.3.5.1
        // 0x57: SOP Class Common Extended Negotiation, PS 3.7, D.3.3.6.1
        else if(type == 0x58)
        {
            UserIdentityRQ const sub_item(stream);
            this->set_sub_item(sub_item);
        }
        else if(type == 0x59)
        {
            UserIdentityAC const sub_item(stream);
            this->set_sub_item(sub_item);
        }
        else
        {
            throw Exception("Invalid sub-item type");
        }
    }
}

}

}
