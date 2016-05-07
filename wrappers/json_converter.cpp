/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include <json/json.h>

#include "odil/DataSet.h"
#include "odil/json_converter.h"

namespace
{

std::string as_json(odil::DataSet const & data_set, bool pretty_print)
{
    auto const json = odil::as_json(data_set);

    Json::Writer * writer = NULL;
    if(pretty_print)
    {
        writer = new Json::StyledWriter();
    }
    else
    {
        writer = new Json::FastWriter();
    }

    auto const string = writer->write(json);
    return string;
}

odil::DataSet from_json(std::string const & json_string)
{
    std::istringstream stream(json_string);
    Json::Value json_value;
    stream >> json_value;
    return odil::as_dataset(json_value);
}

}

void wrap_json_converter()
{
    using namespace boost::python;

    def("as_json", &as_json, (arg("data_set"), arg("pretty_print")=false));
    def("from_json", &from_json);
}
