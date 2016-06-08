/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/pdu/UserInformation.h"

#include <algorithm>
#include <istream>
#include <vector>

#include "odil/endian.h"
#include "odil/Exception.h"
#include "odil/logging.h"
#include "odil/pdu/ImplementationClassUID.h"
#include "odil/pdu/ImplementationVersionName.h"
#include "odil/pdu/MaximumLength.h"
#include "odil/pdu/Object.h"
#include "odil/pdu/RoleSelection.h"
#include "odil/pdu/UserIdentityAC.h"
#include "odil/pdu/UserIdentityRQ.h"

namespace odil
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

    // Store sub-items so that all sub-items of a given type are adjacent, and
    // that their type is in growing order.

    std::vector<MaximumLength> maximum_length;
    std::vector<ImplementationClassUID> implementation_class_uid;
    std::vector<RoleSelection> role_selection;
    std::vector<ImplementationVersionName> implementation_version_name;
    std::vector<UserIdentityRQ> user_identity_rq;
    std::vector<UserIdentityAC> user_identity_ac;

    while(stream.tellg()-begin < item_length)
    {
        uint8_t const type = stream.peek();
        if(type == 0x51)
        {
            maximum_length.push_back(MaximumLength(stream));
        }
        else if(type == 0x52)
        {
            implementation_class_uid.push_back(ImplementationClassUID(stream));
        }
        // 0x53: Asynchronous Operations Window, PS 3.7, D.3.3.3.1
        else if(type == 0x54)
        {
            role_selection.push_back(RoleSelection(stream));
        }
        else if(type == 0x55)
        {
            implementation_version_name.push_back(
                ImplementationVersionName(stream));
        }
        // 0x56: SOP Class Extended Negotiation, PS 3.7, D.3.3.5.1
        // 0x57: SOP Class Common Extended Negotiation, PS 3.7, D.3.3.6.1
        else if(type == 0x58)
        {
            user_identity_rq.push_back(UserIdentityRQ(stream));
        }
        else if(type == 0x59)
        {
            user_identity_ac.push_back(UserIdentityAC(stream));
        }
        else
        {
            stream.ignore(2*sizeof(uint8_t)); // item type, reserved
            if(!stream.good())
            {
                throw Exception("Could not skip sub-item header");
            }

            uint16_t sub_item_length;
            stream.read(
                reinterpret_cast<char*>(&sub_item_length),
                sizeof(sub_item_length));
            if(!stream.good())
            {
                throw Exception("Could not read length");
            }
            sub_item_length = big_endian_to_host(sub_item_length);

            ODIL_LOG(WARN)
                << "Skipping unknown item with type "
                << std::hex << (unsigned int)type << std::dec << " "
                << "(" << sub_item_length << " byte"
                << (sub_item_length>1?"s":"") << ")";

            if(sub_item_length > 0)
            {
                // CAUTION: using ignore could cause eofbit to be positioned and
                // change semantics of later calls. Read the sub-item instead; this
                // is sub-optimal but does not crash.
                std::string sub_item(sub_item_length, '\0');
                stream.read(reinterpret_cast<char*>(&sub_item[0]), sub_item.size());

                if(!stream.good())
                {
                    throw Exception("Could not skip sub-item");
                }
            }
        }
    }

    this->set_sub_items(maximum_length);
    this->set_sub_items(implementation_class_uid);
    this->set_sub_items(role_selection);
    this->set_sub_items(implementation_version_name);
    this->set_sub_items(user_identity_rq);
    this->set_sub_items(user_identity_ac);
}

}

}
