/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/python.hpp>

#include "odil/webservices/Message.h"

boost::python::dict
convert_headers(odil::webservices::Message::Headers const & headers)
{
    using namespace boost::python;

    dict result;
    for(auto const & item: headers)
    {
        result[item.first] = item.second;
    }

    return result;
}

odil::webservices::Message::Headers
convert_headers(boost::python::dict const & headers)
{
    using namespace boost::python;
    using namespace odil::webservices;

    Message::Headers result;

    auto items = headers.items();
    for(int item_index=0; item_index<len(items); ++item_index)
    {
        auto item = items[item_index];

        auto key_python = item[0];
        std::string const key_cpp = extract<std::string>(key_python);

        auto value_python = item[1];
        std::string const value_cpp = extract<std::string>(value_python);

        result.insert(std::make_pair(key_cpp, value_cpp));
    }

    return result;
}
