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

namespace
{

boost::python::tuple 
read(std::string const & path, bool keep_group_length=false)
{
    std::ifstream stream(path);
    if(!stream)
    {
        throw odil::Exception("Could not open "+path);
    }

    auto const header_and_data_set = 
        odil::Reader::read_file(stream, keep_group_length);

    return boost::python::make_tuple(
        header_and_data_set.first, header_and_data_set.second);
}

}

BOOST_PYTHON_FUNCTION_OVERLOADS(read_overloads, read, 1, 2)

void wrap_read()
{
    using namespace boost::python;

    def(
        "read", 
        static_cast<boost::python::tuple (*)(std::string const &, bool)>(read),
        read_overloads());
}
