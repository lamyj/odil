/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <vector>

#include <boost/python.hpp>

#include "odil/DataSet.h"
#include "odil/webservices/WADORSResponse.h"

void wrap_webservices_WADORSResponse()
{
    using namespace boost::python;
    using namespace odil;
    using namespace odil::webservices;

    class_<WADORSResponse>("WADORSResponse", init<>())
        .def(init<HTTPResponse>())
        .def(
            "get_data_sets",
            static_cast<
                std::vector<DataSet> const & (WADORSResponse::*)() const
            >(&WADORSResponse::get_data_sets),
            return_value_policy<copy_const_reference>())
        .def("set_data_sets", &WADORSResponse::set_data_sets)
        // TODO: bulk_data
        .def("is_partial", &WADORSResponse::is_partial)
        .def("set_partial", &WADORSResponse::set_partial)
        .def("get_type", &WADORSResponse::get_type)
        .def(
            "get_representation", &WADORSResponse::get_representation,
            return_value_policy<copy_const_reference>())
        .def("respond_dicom", &WADORSResponse::respond_dicom)
        .def("respond_bulk_data", &WADORSResponse::respond_bulk_data)
        .def("respond_pixel_data", &WADORSResponse::respond_pixel_data)
        .def("get_http_response", &WADORSResponse::get_http_response)
        .def(self == self)
        .def(self != self)
    ;
}
