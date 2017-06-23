/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "odil/webservices/QIDORSRequest.h"
#include "odil/webservices/HTTPRequest.h"
#include "odil/webservices/Utils.h"


// Need to cast into boost::python::list because boost::python::set doesn't exist
boost::python::object
get_includefields(odil::webservices::QIDORSRequest self)
{
    auto const result_cpp = self.get_includefields();
    boost::python::list result_python;
    for (auto const & fields : result_cpp)
    {
        boost::python::list sub_res;
        for (auto const & tag : fields)
        {
            sub_res.append(tag);
        }
        result_python.append(sub_res);
    }
    return result_python;
}

void request_datasets(odil::webservices::QIDORSRequest& self,
                      odil::webservices::Representation representation,
                      odil::webservices::Selector selector,
                      odil::DataSet dataset,
                      boost::python::list includefields,
                      bool fuzzymatching,
                      int limit,
                      int offset,
                      bool numerical_tags
                      )
{
    // Convert here boost::python::list into std::set
    std::set < std::vector< odil::Tag> > cpp_set;
    for (int i = 0; i < boost::python::len(includefields); ++i)
    {
        std::vector<odil::Tag> cpp_vec;
        for (int j = 0; j < boost::python::len(includefields[i]); ++j)
        {
            cpp_vec.push_back(boost::python::extract<odil::Tag>(includefields[i][j]));
        }
        cpp_set.insert(cpp_vec);
    }
    self.request_datasets(
        representation, selector, dataset, cpp_set,
        fuzzymatching, limit, offset, numerical_tags);
}


void wrap_webservices_QIDORSRequest()
{
    using namespace boost::python;
    using namespace odil::webservices;

    class_<QIDORSRequest>(
        "QIDORSRequest",
        init<URL>((
            arg("base_url")=URL()
        )))
        .def(init<HTTPRequest>())
        .def(
            "get_base_url", &QIDORSRequest::get_base_url,
            return_value_policy<copy_const_reference>())
        .def(
            "set_base_url", &QIDORSRequest::set_base_url)
        .def(
            "get_media_type", &QIDORSRequest::get_media_type,
            return_value_policy<copy_const_reference>())
        .def(
            "get_representation", &QIDORSRequest::get_representation,
            return_value_policy<copy_const_reference>())
        .def(
            "get_url", &QIDORSRequest::get_url,
            return_value_policy<copy_const_reference>())
        .def(
            "get_selector", &QIDORSRequest::get_selector,
            return_value_policy<copy_const_reference>())
        .def(
            "get_query_data_set", &QIDORSRequest::get_query_data_set,
            return_value_policy<copy_const_reference>())
        .def(
            "get_include_fields", get_includefields)
        .def(
            "get_fuzzymatching", &QIDORSRequest::get_fuzzymatching)
        .def(
            "get_limit", &QIDORSRequest::get_limit)
        .def(
            "get_offset", &QIDORSRequest::get_offset)
        .def(
            "get_http_request", &QIDORSRequest::get_http_request)
        .def(
            "request_datasets", request_datasets,
            (arg("representation"), arg("selector"), arg("query"),
             arg("includefields") = boost::python::list(),
             arg("fuzzymatching") = false, arg("limit") = -1,
             arg("offset") = 0, arg("numerical_tags") = false
            ))
        .def(self == self)
        .def(self != self)
    ;
}
