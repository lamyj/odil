/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/SOPClassCommonExtendedNegotiation.h"

#include <algorithm>
#include <istream>
#include <string>
#include <vector>

#include "odil/Exception.h"
#include "odil/dul/SubItem.h"

namespace odil
{

namespace dul
{

SOPClassCommonExtendedNegotiation
::SOPClassCommonExtendedNegotiation(
    std::string const & sop_class_uid, std::string const & service_class_uid,
    std::vector<std::string> const & related_general_sop_class_uids)
: SubItem(type)
{
    this->_item.add("SOP-class-uid-length", uint16_t(0));
    this->_item.add("SOP-class-uid", std::string());
    this->_item.add("Service-class-uid-length", uint16_t(0));
    this->_item.add("Service-class-uid", std::string());
    this->_item.add(
        "Related-general-sop-class-identification-length", uint16_t(0));
    this->_item.add(
        "Related-general-sop-class-identification", std::vector<Item>());

    this->set_sop_class_uid(sop_class_uid);
    this->set_service_class_uid(service_class_uid);
    this->set_related_general_sop_class_uids(related_general_sop_class_uids);
}

SOPClassCommonExtendedNegotiation
::SOPClassCommonExtendedNegotiation(std::istream & stream)
: SubItem(type, stream)
{
    this->_item.read(
        stream, "SOP-class-uid-length", Item::Field::Type::unsigned_int_16);
    this->_item.read(
        stream, "SOP-class-uid", Item::Field::Type::string,
        this->_item.as_unsigned_int_16("SOP-class-uid-length"));

    this->_item.read(
        stream, "Service-class-uid-length", Item::Field::Type::unsigned_int_16);
    this->_item.read(
        stream, "Service-class-uid", Item::Field::Type::string,
        this->_item.as_unsigned_int_16("Service-class-uid-length"));

    this->_item.read(
        stream, "Related-general-sop-class-identification-length",
        Item::Field::Type::unsigned_int_16);
    auto const related_classes_length = this->_item.as_unsigned_int_16(
        "Related-general-sop-class-identification-length");

    auto const begin = stream.tellg();
    std::vector<Item> sub_items;
    while(stream.tellg()-begin < related_classes_length)
    {
        Item item;
        item.read(
            stream, "Related-general-sop-class-uid-length",
            Item::Field::Type::unsigned_int_16);
        item.read(
            stream, "Related-general-sop-class-uid", Item::Field::Type::string,
            item.as_unsigned_int_16("Related-general-sop-class-uid-length"));
        sub_items.push_back(item);
    }
    this->_item.add("Related-general-sop-class-identification", sub_items);
}

bool
SOPClassCommonExtendedNegotiation
::operator==(SOPClassCommonExtendedNegotiation const & other) const
{
    return (
        this->get_sop_class_uid() == other.get_sop_class_uid()
        && this->get_service_class_uid() == other.get_service_class_uid()
        && this->get_related_general_sop_class_uids() ==
            other.get_related_general_sop_class_uids()
    );
}

std::string const &
SOPClassCommonExtendedNegotiation
::get_sop_class_uid() const
{
    return this->_item.as_string("SOP-class-uid");
}

void
SOPClassCommonExtendedNegotiation
::set_sop_class_uid(std::string const & value)
{
    this->_item.as_unsigned_int_16("SOP-class-uid-length") = value.size();
    this->_item.as_string("SOP-class-uid") = value;
    this->_set_sub_item_length(this->_compute_length());
}

std::string const &
SOPClassCommonExtendedNegotiation
::get_service_class_uid() const
{
    return this->_item.as_string("Service-class-uid");
}

void
SOPClassCommonExtendedNegotiation
::set_service_class_uid(std::string const & value)
{
    this->_item.as_unsigned_int_16("Service-class-uid-length") = value.size();
    this->_item.as_string("Service-class-uid") = value;
    this->_set_sub_item_length(this->_compute_length());
}

std::vector<std::string>
SOPClassCommonExtendedNegotiation
::get_related_general_sop_class_uids() const
{
    auto const & sub_items = this->_item.as_items(
        "Related-general-sop-class-identification");

    std::vector<std::string> result(sub_items.size());
    std::transform(
        sub_items.begin(), sub_items.end(),
        result.begin(),
        [](Item const & item)
        {
            return item.as_string("Related-general-sop-class-uid");
        });

    return result;
}

void
SOPClassCommonExtendedNegotiation
::set_related_general_sop_class_uids(std::vector<std::string> const & value)
{
    auto & sub_items = this->_item.as_items(
        "Related-general-sop-class-identification");
    sub_items.resize(value.size());
    uint16_t size=0;
    std::transform(
        value.begin(), value.end(),
        sub_items.begin(),
        [&size](std::string const & sop_class_uid)
        {
            Item item;
            item.add(
                "Related-general-sop-class-uid-length",
                uint16_t(sop_class_uid.size()));
            item.add("Related-general-sop-class-uid", sop_class_uid);

            size += (2+sop_class_uid.size());

            return item;
        });

    this->_item.as_unsigned_int_16(
        "Related-general-sop-class-identification-length") = size;
    this->_item.as_items(
        "Related-general-sop-class-identification") = sub_items;
    this->_set_sub_item_length(this->_compute_length());
}

}

}
