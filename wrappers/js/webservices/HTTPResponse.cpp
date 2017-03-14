#include <emscripten.h>
#include <emscripten/bind.h>

#include <odil/webservices/HTTPResponse.h>
#include <odil/webservices/Message.h>

void wrap_webservices_HTTPResponse()
{
    using namespace emscripten;
    using namespace odil::webservices;
    
    class_<HTTPResponse, base<Message>>("webservices_HTTPResponse")
        .constructor<std::string, int, std::string, std::map<std::string, std::string>, std::string>()
        .function("get_http_version", &HTTPResponse::get_http_version)
        .function("set_http_version", &HTTPResponse::set_http_version)
        .function("get_status", &HTTPResponse::get_status)
        .function("set_status", &HTTPResponse::set_status)
        .function("get_reason", &HTTPResponse::get_reason)
        .function("set_reason", &HTTPResponse::set_reason)
    ;
    
    EM_ASM(
        Module['webservices']['HTTPResponse'] = Module['webservices_HTTPResponse'];
        delete Module['webservices_HTTPResponse'];
    );
}
