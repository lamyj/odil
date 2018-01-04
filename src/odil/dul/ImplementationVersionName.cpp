/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/ImplementationVersionName.h"

#include <cstdint>
#include <istream>
#include <string>

#include "odil/Exception.h"
#include "odil/dul/SubItem.h"

namespace odil
{

namespace dul
{

ImplementationVersionName
::ImplementationVersionName(std::string const & implementation_version_name)
: SubItem(type)
{
    this->_item.add("Implementation-version-name", std::string());

    this->set_implementation_version_name(implementation_version_name);
}

ImplementationVersionName
::ImplementationVersionName(std::istream & stream)
: SubItem(type, stream)
{
    this->_item.read(
        stream, "Implementation-version-name", Item::Field::Type::string,
        this->get_sub_item_length());
}

std::string
ImplementationVersionName
::get_implementation_version_name() const
{
    return this->_item.as_string("Implementation-version-name");
}

void
ImplementationVersionName
::set_implementation_version_name(std::string const & value)
{
    if(value.empty() || value.size()>16)
    {
        throw Exception("Invalid implementation version name");
    }
    this->_item.as_string("Implementation-version-name") = value;
    this->_set_sub_item_length(this->_compute_length());
}

}

}
