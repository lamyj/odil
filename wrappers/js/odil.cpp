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

std::string getDictionaryEntry(odil::Tag const & tag)
{
    auto const it = odil::registry::public_dictionary.find(tag);
    Json::Value result;
    if(it != odil::registry::public_dictionary.end())
    {
        result["name"] = it->second.name;
        result["keyword"] = it->second.keyword;
        result["vr"] = it->second.vr;
        result["vm"] = it->second.vm;
    }
    
    std::ostringstream ostream;
    ostream << result;
    
    return ostream.str();
}

EMSCRIPTEN_BINDINGS(odil)
{
    using namespace emscripten;
    using namespace odil;
    
    class_<Tag>("Tag")
        .constructor<int, int>()
        .property("group", &Tag::group)
        .property("element", &Tag::element)
    ;
        
    function("getDictionaryEntry", getDictionaryEntry);
    function("readBuffer", readBuffer);
}
