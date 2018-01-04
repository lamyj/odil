/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/ApplicationContext.h"

#include <cstdint>
#include <istream>
#include <string>

#include "odil/Exception.h"
#include "odil/dul/SubItem.h"

namespace odil
{

namespace dul
{

ApplicationContext
::ApplicationContext(std::string const & name)
: SubItem(type)
{
    this->_item.add("Application-context-name", std::string());

    this->set_name(name);
}

ApplicationContext
::ApplicationContext(std::istream & stream)
: SubItem(type, stream)
{
    this->_item.read(
        stream, "Application-context-name", Item::Field::Type::string,
        this->get_sub_item_length());
}

std::string
ApplicationContext
::get_name() const
{
    return this->_item.as_string("Application-context-name");
}

void
ApplicationContext
::set_name(std::string const & name)
{
    this->_item.as_string("Application-context-name") = name;
    this->_set_sub_item_length(this->_compute_length());
}

}

}
