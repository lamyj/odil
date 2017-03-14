#include <emscripten.h>
#include <emscripten/bind.h>

#include <odil/webservices/HTTPRequest.h>
#include <odil/webservices/Message.h>

void wrap_webservices_HTTPRequest()
{
    using namespace emscripten;
    using namespace odil::webservices;
    
    class_<HTTPRequest, base<Message>>("webservices_HTTPRequest")
        .constructor<std::string, URL, std::string, std::map<std::string, std::string>, std::string>()
        .function("get_method", &HTTPRequest::get_method)
        .function("set_method", &HTTPRequest::set_method)
        .function("get_target", &HTTPRequest::get_target)
        .function("set_target", &HTTPRequest::set_target)
        .function("get_http_version", &HTTPRequest::get_http_version)
        .function("set_http_version", &HTTPRequest::set_http_version)
    ;
    
    EM_ASM(
        Module['webservices']['HTTPRequest'] = Module['webservices_HTTPRequest'];
        delete Module['webservices_HTTPRequest'];
    );
}
