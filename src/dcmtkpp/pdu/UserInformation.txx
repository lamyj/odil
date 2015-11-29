/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _bb325c55_d983_41e3_b6c4_e3b957baedba
#define _bb325c55_d983_41e3_b6c4_e3b957baedba

#include "dcmtkpp/pdu/UserInformation.h"

#include <algorithm>
#include <istream>
#include <sstream>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/pdu/Item.h"
#include "dcmtkpp/pdu/MaximumLength.h"
#include "dcmtkpp/pdu/Object.h"
#include "dcmtkpp/pdu/UserIdentityAC.h"
#include "dcmtkpp/pdu/UserIdentityRQ.h"

namespace dcmtkpp
{

namespace pdu
{

template<typename TObject>
bool
UserInformation
::has_sub_item() const
{
    auto const it = this->_find_sub_item<TObject>();
    return (it != this->_item.as_items("User-data").end());
}

template<typename TObject>
TObject
UserInformation
::get_sub_item() const
{
    auto const it = this->_find_sub_item<TObject>();
    if(it == this->_item.as_items("User-data").end())
    {
        throw Exception("No such sub-item");
    }
    std::stringstream stream;
    stream << *it;
    return TObject(stream);
}

template<typename TObject>
void
UserInformation
::set_sub_item(TObject const & sub_item)
{
    auto const & old_items = this->_item.as_items("User-data");
    std::vector<Item> new_items;

    std::copy_if(
        old_items.begin(), old_items.end(), std::back_inserter(new_items),
        [](Item const & item) {
            return item.as_unsigned_int_8("Item-type") != TObject::type;
        }
    );

    auto const it = std::find_if(
        new_items.begin(), new_items.end(),
        [](Item const & item) {
            return item.as_unsigned_int_8("Item-type") > TObject::type;
        }
    );
    new_items.insert(it, sub_item.get_item());

    this->_item.as_items("User-data") = new_items;

    this->_item.as_unsigned_int_16("Item-length") = this->_compute_length();
}

template<typename TObject>
void
UserInformation
::delete_sub_item()
{
    auto const it = this->_find_sub_item<TObject>();
    auto & items = this->_item.as_items("User-data");
    if(it == items.end())
    {
        throw Exception("No such sub-item");
    }
    items.erase(it);

    this->_item.as_unsigned_int_16("Item-length") = this->_compute_length();
}

template<typename TObject>
UserInformation::Items::const_iterator
UserInformation
::_find_sub_item() const
{
    auto const & sub_items = this->_item.as_items("User-data");
    auto const it = std::find_if(
        sub_items.begin(), sub_items.end(),
        [](Item const & item)
        { return item.as_unsigned_int_8("Item-type") == TObject::type; });
    return it;
}

template<typename TObject>
UserInformation::Items::iterator
UserInformation
::_find_sub_item()
{
    auto & sub_items = this->_item.as_items("User-data");
    auto const it = std::find_if(
        sub_items.begin(), sub_items.end(),
        [](Item const & item)
        { return item.as_unsigned_int_8("Item-type") == TObject::type; });
    return it;
}

}

}

#endif // _bb325c55_d983_41e3_b6c4_e3b957baedba
