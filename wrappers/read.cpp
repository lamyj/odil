/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <fstream>
#include <string>

#include <boost/python.hpp>

#include "odil/Exception.h"
#include "odil/Reader.h"
#include "odil/Tag.h"

namespace
{

boost::python::tuple 
read(
    std::string const & path, bool keep_group_length, 
    boost::python::object const & halt_condition)
{
    std::ifstream stream(path);
    if(!stream)
    {
        throw odil::Exception("Could not open "+path);
    }

    std::function<bool(odil::Tag const &)> halt_condition_cpp = 
        [](odil::Tag const &) { return false;};
    if(halt_condition)
    {
        halt_condition_cpp = 
            [halt_condition](odil::Tag const & tag) 
            { 
                return boost::python::call<bool>(halt_condition.ptr(), tag); 
            };
    }

    auto const header_and_data_set = odil::Reader::read_file(
            stream, keep_group_length, halt_condition_cpp);

    return boost::python::make_tuple(
        header_and_data_set.first, header_and_data_set.second);
}

}

void wrap_read()
{
    using namespace boost::python;

    def(
        "read", 
        static_cast<boost::python::tuple (*)(std::string const &, bool, object const &)>(read),
        (
            arg("path"), arg("keep_group_length")=false, 
            arg("halt_condition")=object())
        );
}
