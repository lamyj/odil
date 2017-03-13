#include <sstream>
#include <string>

#include <emscripten/bind.h>

#include "odil/json_converter.h"
#include "odil/Reader.h"
#include "odil/registry.h"

std::string readBuffer(std::string const & buffer)
{
    std::istringstream istream(buffer);
    auto const header_and_data_set = odil::Reader::read_file(istream);
    
    auto const json_header = odil::as_json(header_and_data_set.first);
    auto const json_data_set = odil::as_json(header_and_data_set.second);
    
    Json::Value root;
    root.append(json_header);
    root.append(json_data_set);
    std::ostringstream ostream;
    ostream << root;
    
    return ostream.str();
}

emscripten::val getTag(std::string const & name)
{
    auto const iterator = odil::registry::public_tags.find(name);
    
    emscripten::val result = emscripten::val::undefined();
    if(iterator != odil::registry::public_tags.end())
    {
        result = emscripten::val(iterator->second);
    }
    else
    {
        result = emscripten::val::null();
    }
    
    return result;
}

void wrap_Tag();

EMSCRIPTEN_BINDINGS(odil)
{
    wrap_Tag();
        
    emscripten::function("readBuffer", readBuffer);
    emscripten::function("getTag", getTag);
}
