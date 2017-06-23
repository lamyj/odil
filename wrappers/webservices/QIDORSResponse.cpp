/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/DataSet.h"
#include "odil/Value.h"
#include "odil/webservices/HTTPResponse.h"
#include "odil/webservices/QIDORSResponse.h"


void
set_data_sets(odil::webservices::QIDORSResponse& self,
                   boost::python::list data_sets)
{
//    std::vector<odil::DataSet> odil_ds;
    odil::Value::DataSets odil_ds;
    for(int i = 0; i < boost::python::len(data_sets) ; ++i)
    {
        odil_ds.push_back(boost::python::extract<odil::DataSet>(data_sets[i]));
    }
    self.set_data_sets(odil_ds);
}

boost::python::list
get_data_sets(odil::webservices::QIDORSResponse& self)
{
    boost::python::list python_ds;
    auto const cpp_val = self.get_data_sets();
    for (auto const ds : cpp_val)
    {
        python_ds.append(ds);
    }
    return python_ds;
}

void
wrap_webservices_QIDORSResponse()
{
    using namespace boost::python;
    using namespace odil;
    using namespace odil::webservices;

    class_<QIDORSResponse>(
        "QIDORSResponse")
        .def(init<HTTPResponse>())
        .def(self == self)
        .def(self != self)
        .def(
            "get_data_sets", get_data_sets
            )
        .def(
            "set_data_sets", set_data_sets
            )
        .def(
            "get_representation", &QIDORSResponse::get_representation,
            return_value_policy<copy_const_reference>())
        .def(
            "set_representation", &QIDORSResponse::set_representation
            )
        .def(
            "get_media_type", &QIDORSResponse::get_media_type,
            return_value_policy<copy_const_reference>())
        .def(
            "get_http_response", &QIDORSResponse::get_http_response
            )
    ;
}
