/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/json_converter.h"

#include <iterator>

#include <json/json.h>

#include "odil/base64.h"
#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/registry.h"
#include "odil/unicode.h"
#include "odil/Value.h"
#include "odil/VR.h"

namespace odil
{

/// @brief Element visitor converting to JSON.
class ToJSONVisitor
{
public:
    typedef Json::Value result_type;

    ToJSONVisitor(Value::Strings const & specific_char_set)
    : _specific_character_set(specific_char_set)
    {
        // Nothing else.
    }

    result_type operator()(VR const vr) const
    {
        result_type result;

        result["vr"] = as_string(vr);

        return result;
    }

    template<typename T>
    result_type operator()(VR const vr, T const & value) const
    {
        result_type result;

        result["vr"] = as_string(vr);

        for(auto const & item: value)
        {
            result["Value"].append(item);
        }

        return result;
    }

    result_type operator()(VR const vr, Value::Integers const & value) const
    {
        result_type result;

        result["vr"] = as_string(vr);

        for(auto const & item: value)
        {
            result["Value"].append(Json::Int64(item));
        }
        return result;
    }

    result_type operator()(VR const vr, Value::Strings const & value) const
    {
        result_type result;

        result["vr"] = as_string(vr);

        if(vr == VR::PN)
        {
            for(auto const & item: value)
            {
                result["Value"].append(this->_convert_pn(item));
            }
        }
        else
        {
            for(auto const & item: value)
            {
                result["Value"].append(this->_convert_string(vr, item));
            }
        }
        return result;
    }

    result_type operator()(VR const vr, Value::DataSets const & value) const
    {
        result_type result;

        result["vr"] = as_string(vr);

        for(auto const & item: value)
        {
            result["Value"].append(as_json(item));
        }
        return result;
    }

    result_type operator()(VR const vr, Value::Binary const & value) const
    {
        if(value.size() > 1)
        {
            // PS3.18 2016b, F.2.7: There is a single InlineBinary value
            // representing the entire Value Field.
            // PS3.18 2016b, Figure 6.5-1: Pixel data is not encoded in
            // JSON/XML, but transfered using a different content type
            throw Exception("Binary element is multiple-valued");
        }

        result_type result;

        result["vr"] = as_string(vr);

        std::string encoded;
        encoded.reserve(value[0].size()*4/3);
        base64::encode(
            value[0].begin(), value[0].end(), std::back_inserter(encoded));
        result["InlineBinary"] = encoded;

        return result;
    }

private:
    Value::Strings _specific_character_set;

    std::string _convert_string(VR const vr, Value::String const & value) const
    {
        if(
            vr != VR::LO && vr != VR::LT &&
            vr != VR::PN && vr != VR::SH &&
            vr != VR::ST && vr != VR::UT)
        {
            // Nothing to do
            return value;
        }

        return as_utf8(value, this->_specific_character_set, vr==VR::PN);
    }

    Json::Value _convert_pn(Value::String const & value) const
    {
        static auto const fields = { "Alphabetic", "Ideographic", "Phonetic" };

        Json::Value json;

        auto fields_it = fields.begin();

        std::string::size_type begin=0;
        while(begin != std::string::npos)
        {
            auto const end = value.find("=", begin);

            std::string::size_type size = 0;
            if(end != std::string::npos)
            {
                size = end-begin;
            }
            else
            {
                size = std::string::npos;
            }

            auto const component = value.substr(begin, size);
            json[*fields_it] = this->_convert_string(VR::PN, component);

            if(end != std::string::npos)
            {
                begin = end+1;
                ++fields_it;
                if(fields_it == fields.end())
                {
                    throw Exception("Invalid Person Name");
                }
            }
            else
            {
                begin = end;
            }
        }

        return json;
    }
};

Json::Value as_json(
    std::shared_ptr<DataSet const> data_set,
    Value::Strings const & specific_character_set)
{
    auto current_specific_char_set = specific_character_set;

    Json::Value json;
    if(!data_set)
    {
        return json;
    }

    for(auto const & it: *data_set)
    {
        auto const & tag = it.first;
        if(tag.element == 0)
        {
            // Skip group length tags
            continue;
        }

        auto const & element = it.second;

        // Specific character set
        if(tag == registry::SpecificCharacterSet)
        {
            current_specific_char_set = element.as_string();
        }

        std::string const key(tag);

        ToJSONVisitor const visitor(current_specific_char_set);
        auto const value = apply_visitor(visitor, element);

        json[key] = value;
    }

    return json;
}

std::shared_ptr<DataSet> as_dataset(Json::Value const & json)
{
    auto data_set = std::make_shared<DataSet>();

    for(auto it=json.begin(); it != json.end(); ++it)
    {
        Tag const tag(it.memberName());

        auto const & json_element = *it;
        auto const vr = as_vr(json_element["vr"].asString());

        Element element(vr);

        if(is_string(vr) && vr != VR::PN)
        {
            auto const & json_value = json_element["Value"];
            for(auto const & json_item: json_value)
            {
                element.as_string().push_back(json_item.asString());
            }
        }
        else if(vr == VR::PN)
        {
            auto const & json_value = json_element["Value"];
            for(auto const & json_item: json_value)
            {   
                Value::Strings::value_type dicom_item;
                auto const fields = { "Alphabetic", "Ideographic", "Phonetic" };
                for(auto const & field: fields)
                {
                    if(json_item.isMember(field))
                    {
                        dicom_item += json_item[field].asString();
                    }
                    dicom_item += "=";
                }

                while(*dicom_item.rbegin() == '=')
                {
                    dicom_item = dicom_item.substr(0, dicom_item.size()-1);
                }

                element.as_string().push_back(dicom_item);
            }
        }
        else if(is_real(vr))
        {
            auto const & json_value = json_element["Value"];
            for(auto const & json_item: json_value)
            {
                element.as_real().push_back(json_item.asDouble());
            }
        }
        else if(is_int(vr))
        {
            auto const & json_value = json_element["Value"];
            for(auto const & json_item: json_value)
            {
                element.as_int().push_back(json_item.asInt64());
            }
        }
        else if(vr == VR::SQ)
        {
            auto const & json_value = json_element["Value"];
            for(auto const & json_item: json_value)
            {
                auto const dicom_item = as_dataset(json_item);
                element.as_data_set().push_back(dicom_item);
            }
        }
        else if(is_binary(vr))
        {
            // cf. ToJSONVisitor::operator()(VR, Value::Binary): InlineBinary is
            // single-valued
            auto const & encoded = json_element["InlineBinary"].asString();
            auto & decoded = element.as_binary();
            decoded.resize(1);
            decoded.reserve(encoded.size()*3/4);
            base64::decode(
                encoded.begin(), encoded.end(), std::back_inserter(decoded[0]));
        }
        else
        {
            throw Exception("Unknown VR: "+as_string(vr));
        }

        data_set->add(tag, element);
    }

    return data_set;
}

}
