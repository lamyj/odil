/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/Element.h"

namespace dcmtkpp
{

Element
::Element()
: value(), vr()
{
    // Nothing else
}

bool
Element
::empty() const
{
    return boost::apply_visitor(Empty(), this->value);
}

std::size_t
Element
::size() const
{
    return boost::apply_visitor(Size(), this->value);
}

bool
Element
::is_int() const
{
    return (this->value.type() == typeid(std::vector<int64_t>));
}

std::vector<int64_t> const &
Element
::as_int() const
{
    return this->_as<int64_t>();
}

std::vector<int64_t> &
Element
::as_int()
{
    return this->_as<int64_t>();
}

bool
Element
::is_real() const
{
    return (this->value.type() == typeid(std::vector<double>));
}

std::vector<double> const &
Element
::as_real() const
{
    return this->_as<double>();
}

std::vector<double> &
Element
::as_real()
{
    return this->_as<double>();
}

bool
Element
::is_string() const
{
    return (this->value.type() == typeid(std::vector<std::string>));
}

std::vector<std::string> const &
Element
::as_string() const
{
    return this->_as<std::string>();
}

std::vector<std::string> &
Element
::as_string()
{
    return this->_as<std::string>();
}

}
