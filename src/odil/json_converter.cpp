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
#include "odil/Value.h"
#include "odil/VR.h"

namespace odil
{

struct ToJSONVisitor
{
    typedef Json::Value result_type;

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
            auto const fields = { "Alphabetic", "Ideographic", "Phonetic" };

            for(auto const item: value)
            {
                auto fields_it = fields.begin();

                Json::Value json_item;

                std::string::size_type begin=0;
                while(begin != std::string::npos)
                {
                    std::string::size_type const end = item.find("=", begin);

                    std::string::size_type size = 0;
                    if(end != std::string::npos)
                    {
                        size = end-begin;
                    }
                    else
                    {
                        size = std::string::npos;
                    }

                    json_item[*fields_it] = item.substr(begin, size);

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
                result["Value"].append(json_item);
            }
        }
        else
        {
            for(auto const & item: value)
            {
                result["Value"].append(item);
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
        base64::encode(value[0].begin(), value[0].end(), std::back_inserter(encoded));
        result["InlineBinary"] = encoded;

        return result;
    }

};

Json::Value as_json(DataSet const & data_set)
{
    Json::Value json;

    for(auto const & it: data_set)
    {
        auto const & tag = it.first;
        auto const & element = it.second;

        std::string const key(tag);
        auto const value = apply_visitor(ToJSONVisitor(), element);
        json[key] = value;
    }

    return json;
}

DataSet as_dataset(Json::Value const & json)
{
    DataSet data_set;

    for(Json::Value::const_iterator it=json.begin(); it != json.end(); ++it)
    {
        Tag const tag(it.memberName());

        Json::Value const & json_element = *it;
        VR const vr = as_vr(json_element["vr"].asString());

        Element element;

        if(vr == VR::AE || vr == VR::AS || vr == VR::AT || vr == VR::CS ||
           vr == VR::DA || vr == VR::DT || vr == VR::LO || vr == VR::LT ||
           vr == VR::SH || vr == VR::ST || vr == VR::TM || vr == VR::UI ||
           vr == VR::UT)
        {
            element = Element(Value::Strings(), vr);

            auto const & json_value = json_element["Value"];
            for(auto const & json_item: json_value)
            {
                element.as_string().push_back(json_item.asString());
            }
        }
        else if(vr == VR::PN)
        {
            element = Element(Value::Strings(), vr);
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
        else if(vr == VR::DS || vr == VR::FD || vr == VR::FL)
        {
            element = Element(Value::Reals(), vr);

            auto const & json_value = json_element["Value"];
            for(auto const & json_item: json_value)
            {
                element.as_real().push_back(json_item.asDouble());
            }
        }
        else if(vr == VR::IS || vr == VR::SL || vr == VR::SS ||
                vr == VR::UL || vr == VR::US)
        {
            element = Element(Value::Integers(), vr);

            auto const & json_value = json_element["Value"];
            for(auto const & json_item: json_value)
            {
                element.as_int().push_back(json_item.asInt64());
            }
        }
        else if(vr == VR::SQ)
        {
            element = Element(Value::DataSets(), vr);
            auto const & json_value = json_element["Value"];
            for(auto const & json_item: json_value)
            {
                auto const dicom_item = as_dataset(json_item);
                element.as_data_set().push_back(dicom_item);
            }
        }
        else if(vr == VR::OB || vr == VR::OF || vr == VR::OW || vr == VR::UN)
        {
            element = Element(Value::Binary(), vr);

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

        data_set.add(tag, element);
    }

    return data_set;
}

}
