/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <emscripten.h>
#include <emscripten/bind.h>

#include "odil/webservices/WADORSRequest.h"

namespace 
{

odil::webservices::WADORSRequest
WADORSRequest_fromHTTPRequest(odil::webservices::HTTPRequest const & request)
{
    return odil::webservices::WADORSRequest(request);
}

}

void wrap_webservices_WADORSRequest()
{
    using namespace emscripten;
    using namespace odil::webservices;
    
    class_<WADORSRequest>("webservices_WADORSRequest")
        .constructor<URL, std::string, std::string, bool, bool>()
        .class_function("fromHTTPRequest", &WADORSRequest_fromHTTPRequest)
        .function("equal", &WADORSRequest::operator==)
        .function("notEqual", &WADORSRequest::operator!=)
        .function("get_base_url", &WADORSRequest::get_base_url)
        .function("set_base_url", &WADORSRequest::set_base_url)
        .function("get_transfer_syntax", &WADORSRequest::get_transfer_syntax)
        .function("set_transfer_syntax", &WADORSRequest::set_transfer_syntax)
        .function("get_character_set", &WADORSRequest::get_character_set)
        .function("set_character_set", &WADORSRequest::set_character_set)
        .function(
            "get_include_media_type_in_query", 
            &WADORSRequest::get_include_media_type_in_query)
        .function(
            "set_include_media_type_in_query", 
            &WADORSRequest::set_include_media_type_in_query)
        .function(
            "get_include_character_set_in_query", 
            &WADORSRequest::get_include_character_set_in_query)
        .function(
            "set_include_character_set_in_query", 
            &WADORSRequest::set_include_character_set_in_query)
        .function("get_type", &WADORSRequest::get_type)
        .function("get_selector", &WADORSRequest::get_selector)
        .function("get_url", &WADORSRequest::get_url)
        .function("get_media_type", &WADORSRequest::get_media_type)
        .function("get_representation", &WADORSRequest::get_representation)
        .function("request_dicom", &WADORSRequest::request_dicom)
        // request_bulk_data
        // request_bulk_data
        .function("request_pixel_data", &WADORSRequest::request_pixel_data)
        .function("get_http_request", &WADORSRequest::get_http_request)
    ;
    
    EM_ASM(
        Module['webservices']['WADORSRequest'] = 
            Module['webservices_WADORSRequest'];
        delete Module['webservices_WADORSRequest'];
    );

}
