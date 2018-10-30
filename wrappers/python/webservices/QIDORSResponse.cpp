/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "odil/DataSet.h"
#include "odil/Value.h"
#include "odil/webservices/HTTPResponse.h"
#include "odil/webservices/QIDORSResponse.h"

namespace
{

void
set_data_sets(
    odil::webservices::QIDORSResponse& self, pybind11::sequence data_sets)
{
    odil::Value::DataSets cpp_val(pybind11::len(data_sets));
    std::transform(
        data_sets.begin(), data_sets.end(), cpp_val.begin(), 
        [](pybind11::handle const & h) 
        { return h.cast<std::shared_ptr<odil::DataSet>>(); });
    self.set_data_sets(cpp_val);
}

}

void
wrap_webservices_QIDORSResponse(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    using namespace odil::webservices;

    class_<QIDORSResponse>(m, "QIDORSResponse")
        .def(init())
        .def(init<HTTPResponse>())
        .def(self == self)
        .def(self != self)
        .def(
            "get_data_sets",
            static_cast<
                Value::DataSets const &(QIDORSResponse::*)() const
            >(&QIDORSResponse::get_data_sets))
        .def("set_data_sets", set_data_sets)
        .def("get_representation", &QIDORSResponse::get_representation)
        .def("set_representation", &QIDORSResponse::set_representation)
        .def("get_media_type", &QIDORSResponse::get_media_type)
        .def("get_http_response", &QIDORSResponse::get_http_response)
    ;
}
