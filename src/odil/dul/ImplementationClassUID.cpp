/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/ImplementationClassUID.h"

#include <cstdint>
#include <istream>
#include <string>

#include "odil/Exception.h"
#include "odil/dul/SubItem.h"

namespace odil
{

namespace dul
{

ImplementationClassUID
::ImplementationClassUID(std::string const & implementation_class_uid)
: SubItem(type)
{
    this->_item.add("Implementation-class-uid", std::string());

    this->set_implementation_class_uid(implementation_class_uid);
}

ImplementationClassUID
::ImplementationClassUID(std::istream & stream)
: SubItem(type, stream)
{
    this->_item.read(
        stream, "Implementation-class-uid", Item::Field::Type::string,
        this->get_sub_item_length());
}

std::string
ImplementationClassUID
::get_implementation_class_uid() const
{
    return this->_item.as_string("Implementation-class-uid");
}

void
ImplementationClassUID
::set_implementation_class_uid(std::string const & value)
{
    this->_item.as_string("Implementation-class-uid") = value;
    this->_set_sub_item_length(this->_compute_length());
}

}

}
