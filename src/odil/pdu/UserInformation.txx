/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _bb325c55_d983_41e3_b6c4_e3b957baedba
#define _bb325c55_d983_41e3_b6c4_e3b957baedba

#include "odil/pdu/UserInformation.h"

#include <algorithm>
#include <initializer_list>
#include <istream>
#include <iterator>
#include <sstream>
#include <vector>

#include "odil/Exception.h"
#include "odil/pdu/Item.h"
#include "odil/pdu/MaximumLength.h"
#include "odil/pdu/Object.h"
#include "odil/pdu/UserIdentityAC.h"
#include "odil/pdu/UserIdentityRQ.h"

namespace odil
{

namespace pdu
{

template<typename TObject>
std::vector<TObject>
UserInformation
::get_sub_items() const
{
    auto const iterators = this->_find_sub_items<TObject>();

    std::vector<TObject> result;
    result.reserve(iterators.size());
    std::transform(
        iterators.begin(), iterators.end(), std::back_inserter(result),
        [](Items::const_iterator const & it)
        {
            std::stringstream stream;
            stream << *it;
            return TObject(stream);
        }
    );

    return result;
}

template<typename TObject>
void
UserInformation
::set_sub_items(std::vector<TObject> const & sub_items)
{
    auto const & old_items = this->_item.as_items("User-data");
    std::vector<Item> new_items;

    auto old_items_iterator = old_items.begin();
    while(old_items_iterator != old_items.end() &&
        old_items_iterator->as_unsigned_int_8("Item-type") < TObject::type)
    {
        new_items.push_back(*old_items_iterator);
        ++old_items_iterator;
    }

    std::transform(
        sub_items.begin(), sub_items.end(), std::back_inserter(new_items),
        [](Object const & object) { return object.get_item(); });

    while(old_items_iterator != old_items.end() &&
        old_items_iterator->as_unsigned_int_8("Item-type") == TObject::type)
    {
        ++old_items_iterator;
    }

    while(old_items_iterator != old_items.end())
    {
        new_items.push_back(*old_items_iterator);
        ++old_items_iterator;
    }

    this->_item.as_items("User-data") = new_items;

    this->_item.as_unsigned_int_16("Item-length") = this->_compute_length();
}

template<typename TObject>
void
UserInformation
::delete_sub_items()
{
    auto const & old_items = this->_item.as_items("User-data");
    std::vector<Item> new_items;
    std::copy_if(
        old_items.begin(), old_items.end(), std::back_inserter(new_items),
        [](Item const & item)
        {
            return item.as_unsigned_int_8("Item-type") != TObject::type;
        }
    );

    this->_item.as_items("User-data") = new_items;

    this->_item.as_unsigned_int_16("Item-length") = this->_compute_length();
}

template<typename TObject>
std::vector<UserInformation::Items::const_iterator>
UserInformation
::_find_sub_items() const
{
    std::vector<Items::const_iterator> result;

    auto const & sub_items = this->_item.as_items("User-data");
    auto iterator = sub_items.begin();
    for(; iterator != sub_items.end(); ++iterator)
    {
        if(iterator->as_unsigned_int_8("Item-type") == TObject::type)
        {
            result.push_back(iterator);
        }
    }

    return result;
}

template<typename TObject>
std::vector<UserInformation::Items::iterator>
UserInformation
::_find_sub_items()
{
    std::vector<Items::iterator> result;

    auto & sub_items = this->_item.as_items("User-data");
    auto iterator = sub_items.begin();
    for(; iterator != sub_items.end(); ++iterator)
    {
        if(iterator->as_unsigned_int_8("Item-type") == TObject::type)
        {
            result.push_back(iterator);
        }
    }

    return result;
}

}

}

#endif // _bb325c55_d983_41e3_b6c4_e3b957baedba
