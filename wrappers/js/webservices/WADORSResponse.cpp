#include <emscripten.h>
#include <emscripten/bind.h>

#include <odil/webservices/WADORSResponse.h>

namespace 
{

odil::webservices::WADORSResponse
WADORSResponse_fromHTTPResponse(odil::webservices::HTTPResponse const & response)
{
    return odil::webservices::WADORSResponse(response);
}

}

void wrap_webservices_WADORSResponse()
{
    using namespace emscripten;
    using namespace odil;
    using namespace odil::webservices;
    
    class_<WADORSResponse>("webservices_WADORSResponse")
        .constructor<>()
        .class_function("fromHTTPResponse", &WADORSResponse_fromHTTPResponse)
        .function("equal", &WADORSResponse::operator==)
        .function("notEqual", &WADORSResponse::operator!=)
        .function(
            "get_data_sets", 
            select_overload<std::vector<DataSet> const & () const>(
                &WADORSResponse::get_data_sets))
        .function("set_data_sets", &WADORSResponse::set_data_sets)
        // get_bulk_data
        // set_bulk_data
        .function("is_partial", &WADORSResponse::is_partial)
        .function("set_partial", &WADORSResponse::set_partial)
        .function("get_type", &WADORSResponse::get_type)
        .function("get_representation", &WADORSResponse::get_representation)
        .function("respond_dicom", &WADORSResponse::respond_dicom)
        .function("respond_bulk_data", &WADORSResponse::respond_bulk_data)
        .function("respond_pixel_data", &WADORSResponse::respond_pixel_data)
        .function("get_http_response", &WADORSResponse::get_http_response)
    ;
    
    EM_ASM(
        Module['webservices']['WADORSResponse'] = Module['webservices_WADORSResponse'];
        delete Module['webservices_WADORSResponse'];
    );
}
