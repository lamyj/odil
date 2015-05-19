/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/json_converter.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/ofstd.h>
#include <dcmtk/ofstd/ofstream.h>
#include <jsoncpp/json/json.h>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Value.h"
#include "dcmtkpp/VR.h"

namespace dcmtkpp
{

struct ToJSONVisitor
{
    typedef Json::Value result_type;

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

                std::string::size_type begin=0;
                while(begin != std::string::npos)
                {
                    Json::Value json_item;

                    std::string::size_type const end = item.find("=", begin);

                    std::string::size_type size = 0;
                    if(end != std::string::npos)
                    {
                        size = end-begin+1;
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

                    result["Value"].append(json_item);
                }
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
            result["Value"].append(to_json(item));
        }
        return result;
    }

    result_type operator()(VR const vr, Value::Binary const & value) const
    {
        result_type result;

        result["vr"] = as_string(vr);

        unsigned char const * data =
            reinterpret_cast<unsigned char const *>(&value[0]);
        OFStringStream stream;
        OFStandard::encodeBase64(stream, data, value.size());
        result["InlineBinary"] = stream.str().c_str();

        return result;
    }

};

Json::Value to_json(DataSet const & data_set)
{
    Json::Value json;

    for(auto const & it: data_set)
    {
        auto const & tag = it.first;
        auto const & element = it.second;

        std::string const key(tag);
        json[key] = apply_visitor(ToJSONVisitor(), element);
    }

    return json;
}

}
