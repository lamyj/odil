/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <emscripten.h>
#include <emscripten/bind.h>

#include "iostream"
#include "odil/webservices/QIDORSRequest.h"
#include "odil/webservices/Utils.h"
#include "odil/json_converter.h"
#include "json/json.h"

namespace
{

odil::webservices::QIDORSRequest
QIDORSRequest_fromHTTPRequest(odil::webservices::HTTPRequest const & request)
{
    return odil::webservices::QIDORSRequest(request);
}

}


void
request_datasets(odil::webservices::QIDORSRequest & qido,
                 odil::webservices::Representation const & repr,
                 odil::webservices::Selector const & selector,
                 Json::Value const & array)
// Following fields are not handled still now
//                               bool fuzzymatching,
//                               int limit,
//                               int offset,
//                               bool numerical_tags)
{
    odil::DataSet query = odil::as_dataset(array[0]);

    std::vector<odil::Tag> wanted_includefields = {
        odil::Tag("00100010"), // PatientName
        odil::Tag("0008103e"), // SeriesDesc
        odil::Tag("00081030"), // StudyDesc
        // Study
        odil::Tag("0020000d"), // StudyInstanceUID
        odil::Tag("00080020"), // StudyDate
        odil::Tag("00080030"), // StudyTime
        odil::Tag("00201206"), // NumberOfStudyRelatedSeries
        // Series
        odil::Tag("00200011"), // Series Number
        odil::Tag("00080060"), // Modality
        odil::Tag("0020000E"), // SeriesInstanceUID
        odil::Tag("00201209"), // NumberOfSeriesRelatedInstances
    };

    for (auto const tag : wanted_includefields)
    {
        if (!query.has(tag))
        {
            query.add(tag);
        }
    }


    // Still here ds is correctly constructed, and qido is correctly obtained, repr is ok, selector
    qido.request_datasets(repr, selector, query);
}

void wrap_webservices_QIDORSRequest()
{
    using namespace emscripten;
    using namespace odil::webservices;

    class_<QIDORSRequest>("webservices_QIDORSRequest")
        .constructor<URL>()
        .class_function("fromHTTPRequest", &QIDORSRequest_fromHTTPRequest)
        .function("get_base_url", &QIDORSRequest::get_base_url)
        .function("set_base_url", &QIDORSRequest::set_base_url)
        .function("get_media_type", &QIDORSRequest::get_media_type)
        .function("get_representation", &QIDORSRequest::get_representation)
        .function("get_query_data_set", &QIDORSRequest::get_query_data_set)
        .function("get_includefields", &QIDORSRequest::get_includefields)
        .function("get_fuzzymatching", &QIDORSRequest::get_fuzzymatching)
        .function("get_limit", &QIDORSRequest::get_limit)
        .function("get_offset", &QIDORSRequest::get_offset)
        .function("get_http_request", &QIDORSRequest::get_http_request)
        .function("request_datasets", &request_datasets)
        .function("equal", &QIDORSRequest::operator==)
        .function("notEqual", &QIDORSRequest::operator!=)
    ;

    EM_ASM(
        Module['webservices']['QIDORSRequest'] =
            Module['webservices_QIDORSRequest'];
        delete Module['webservices_QIDORSRequest'];
    );
}
