#include <odil/VR.h>

#include <map>
#include <stdexcept>
#include <string>

#include "odil/Exception.h"
#include "odil/registry.h"
#include "odil/Tag.h"

// Anonymous namespace, should not be publicly accessed
namespace
{

#define ADD_TO_MAP(map, vr) map[odil::VR::vr] = #vr

std::map<odil::VR, std::string>
_build_enum_to_name()
{
    std::map<odil::VR, std::string> result;
    ADD_TO_MAP(result, AE);
    ADD_TO_MAP(result, AS);
    ADD_TO_MAP(result, AT);
    ADD_TO_MAP(result, CS);
    ADD_TO_MAP(result, DA);
    ADD_TO_MAP(result, DS);
    ADD_TO_MAP(result, DT);
    ADD_TO_MAP(result, FL);
    ADD_TO_MAP(result, FD);
    ADD_TO_MAP(result, IS);
    ADD_TO_MAP(result, LO);
    ADD_TO_MAP(result, LT);
    ADD_TO_MAP(result, OB);
    ADD_TO_MAP(result, OD);
    ADD_TO_MAP(result, OF);
    ADD_TO_MAP(result, OL);
    ADD_TO_MAP(result, OW);
    ADD_TO_MAP(result, PN);
    ADD_TO_MAP(result, SH);
    ADD_TO_MAP(result, SL);
    ADD_TO_MAP(result, SQ);
    ADD_TO_MAP(result, SS);
    ADD_TO_MAP(result, ST);
    ADD_TO_MAP(result, TM);
    ADD_TO_MAP(result, UC);
    ADD_TO_MAP(result, UI);
    ADD_TO_MAP(result, UL);
    ADD_TO_MAP(result, UN);
    ADD_TO_MAP(result, UR);
    ADD_TO_MAP(result, US);
    ADD_TO_MAP(result, UT);

    return result;
}

#undef ADD_TO_MAP

std::map<std::string, odil::VR>
_build_name_to_enum()
{
    std::map<odil::VR, std::string> const enum_to_name = _build_enum_to_name();

    std::map<std::string, odil::VR> result;
    for(std::map<odil::VR, std::string>::const_iterator it = enum_to_name.begin();
        it != enum_to_name.end(); ++it)
    {
        result[it->second] = it->first;
    }

    return result;
}

std::map<odil::VR, std::string> const
_enum_to_name = _build_enum_to_name();

std::map<std::string, odil::VR> const
_name_to_enum = _build_name_to_enum();

}

namespace odil
{

std::string as_string(VR vr)
{
    try
    {
        return _enum_to_name.at(vr);
    }
    catch(std::out_of_range const &)
    {
        throw Exception("Unknown VR: "+std::to_string(static_cast<int>(vr)));
    }
}

VR as_vr(std::string const & vr)
{
    try
    {
        return _name_to_enum.at(vr);
    }
    catch(std::out_of_range const &)
    {
        throw Exception("Unknown VR: "+vr);
    }
}

VR as_vr(Tag const & tag)
{
    auto const dictionary_it = registry::public_dictionary.find(tag);
    if(dictionary_it == registry::public_dictionary.end())
    {
        throw Exception("No such element: "+std::string(tag));
    }

    VR const vr(as_vr(std::string(dictionary_it->second.vr)));

    return vr;
}

bool is_int(VR vr)
{
    return (
        vr == VR::IS || vr == VR::SL || vr == VR::SS || vr == VR::SV || 
        vr == VR::UL || vr == VR::US || vr == VR::UV);
}

bool is_real(VR vr)
{
    return (vr == VR::DS || vr == VR::FL || vr == VR::FD);
}

bool is_string(VR vr)
{
    return (
        vr == VR::AE || vr == VR::AS || vr == VR::AT || vr == VR::CS || vr == VR::DA ||
        vr == VR::DT || vr == VR::LO || vr == VR::LT || vr == VR::PN ||
        vr == VR::SH || vr == VR::ST || vr == VR::TM || vr == VR::UC ||
        vr == VR::UI || vr == VR::UR || vr == VR::UT);
}

bool is_binary(VR vr)
{
    return (
        vr == VR::OB || vr == VR::OD || vr == VR::OF || vr == VR::OL ||
        vr == VR::OV || vr == VR::OW || vr == VR::UN);
}


}
