/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/SOPClassExtendedNegotiation.h"

#include <algorithm>
#include <cstdint>
#include <istream>
#include <string>
#include <vector>

#include "odil/Exception.h"
#include "odil/dul/SubItem.h"

namespace odil
{

namespace dul
{

SOPClassExtendedNegotiation
::SOPClassExtendedNegotiation(
    std::string const & sop_class_uid,
    std::vector<uint8_t> const & service_class_application_information)
: SubItem(type)
{
    this->_item.add("SOP-class-uid-length", uint16_t(0));
    this->_item.add("SOP-class-uid", std::string());
    this->_item.add("Service-class-application-information", std::string());

    this->set_sop_class_uid(sop_class_uid);
    this->set_service_class_application_information(
        service_class_application_information);
}

SOPClassExtendedNegotiation
::SOPClassExtendedNegotiation(std::istream & stream)
: SubItem(type, stream)
{
    this->_item.read(
        stream, "SOP-class-uid-length", Item::Field::Type::unsigned_int_16);
    this->_item.read(
        stream, "SOP-class-uid", Item::Field::Type::string,
        this->_item.as_unsigned_int_16("SOP-class-uid-length"));

    this->_item.read(
        stream, "Service-class-application-information",
        Item::Field::Type::string,
        this->get_sub_item_length()
            -this->_item.as_unsigned_int_16("SOP-class-uid-length")
            -2);
}

bool
SOPClassExtendedNegotiation
::operator==(SOPClassExtendedNegotiation const & other) const
{
    return (
        this->get_sop_class_uid() == other.get_sop_class_uid()
        && this->get_service_class_application_information() ==
            other.get_service_class_application_information()
    );
}

std::string const &
SOPClassExtendedNegotiation
::get_sop_class_uid() const
{
    return this->_item.as_string("SOP-class-uid");
}

void
SOPClassExtendedNegotiation
::set_sop_class_uid(std::string const & value)
{
    this->_item.as_unsigned_int_16("SOP-class-uid-length") = value.size();
    this->_item.as_string("SOP-class-uid") = value;
    this->_set_sub_item_length(this->_compute_length());
}

std::vector<uint8_t>
SOPClassExtendedNegotiation
::get_service_class_application_information() const
{
    auto const & string = this->_item.as_string(
        "Service-class-application-information");
    std::vector<uint8_t> result(string.size());
    std::copy(string.begin(), string.end(), result.begin());
    return result;
}

void
SOPClassExtendedNegotiation
::set_service_class_application_information(std::vector<uint8_t> const & value)
{
    std::string string(value.size(), '\0');
    std::copy(value.begin(), value.end(), string.begin());

    this->_item.as_string("Service-class-application-information") = string;
    this->_set_sub_item_length(this->_compute_length());
}

}

}
