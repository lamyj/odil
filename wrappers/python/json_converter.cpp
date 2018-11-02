/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <memory>

#include <pybind11/pybind11.h>

#include <json/json.h>

#include "odil/DataSet.h"
#include "odil/json_converter.h"
#include "odil/StringStream.h"

#include "opaque_types.h"
#include "type_casters.h"

void wrap_json_converter(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    m.def(
        "as_json",
        [](std::shared_ptr<odil::DataSet> data_set, bool pretty_print)
        {
            auto const json = as_json(data_set);
            std::shared_ptr<Json::Writer> writer;
            if(pretty_print)
            {
                writer = std::make_shared<Json::StyledWriter>();
            }
            else
            {
                writer = std::make_shared<Json::FastWriter>();
            }

            auto const string = writer->write(json);
            return string;
        },
        "data_set"_a, "pretty_print"_a=false);
    m.def(
        "from_json",
        [](std::string const & json_string)
        {
            IStringStream stream(&json_string[0], json_string.size());
            Json::Value json_value;
            stream >> json_value;
            return as_dataset(json_value);
        }
    );
}
