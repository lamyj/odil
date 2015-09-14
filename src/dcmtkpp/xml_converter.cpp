/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/ofstd.h>
#include <dcmtk/ofstd/ofstream.h>

#include "dcmtkpp/registry.h"
#include "dcmtkpp/xml_converter.h"

namespace dcmtkpp
{

struct ToXMLVisitor
{
    typedef boost::property_tree::ptree result_type;

    result_type operator()(VR const vr) const
    {
        result_type result;

        result.put("<xmlattr>.vr", as_string(vr)); // Mandatory

        return result;
    }

    template<typename T>
    result_type operator()(VR const vr, T const & value) const
    {
        result_type result;

        result.put("<xmlattr>.vr", as_string(vr)); // Mandatory

        unsigned int count = 0;
        for(auto const & item: value)
        {
            ++count;
            boost::property_tree::ptree tag_value;
            tag_value.put("<xmlattr>.number", count); // Mandatory
            tag_value.put_value(item);

            result.add_child("Value", tag_value);
        }

        return result;
    }

    result_type operator()(VR const vr, Value::Integers const & value) const
    {
        result_type result;

        result.put("<xmlattr>.vr", as_string(vr)); // Mandatory

        unsigned int count = 0;
        for(auto const & item: value)
        {
            ++count;
            boost::property_tree::ptree tag_value;
            tag_value.put("<xmlattr>.number", count); // Mandatory
            tag_value.put_value(item);

            result.add_child("Value", tag_value);
        }

        return result;
    }

    result_type operator()(VR const vr, Value::Strings const & value) const
    {
        result_type result;

        result.put("<xmlattr>.vr", as_string(vr)); // Mandatory

        if(vr == VR::PN)
        {
            auto const fields = { "Alphabetic", "Ideographic", "Phonetic" };

            unsigned int count = 0;
            for(auto const & item: value)
            {
                ++count;
                boost::property_tree::ptree tag_value;
                tag_value.put("<xmlattr>.number", count); // Mandatory

                auto fields_it = fields.begin();
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

                    boost::property_tree::ptree tag_field;
                    std::string value_name = item.substr(begin, size);

                    auto const fields_name = { "FamilyName", "GivenName", "MiddleName", "NamePrefix", "NameSuffix" };
                    auto fields_name_it = fields_name.begin();
                    std::string::size_type begin_name=0;
                    while(begin_name != std::string::npos)
                    {
                        std::string::size_type const end_name = value_name.find("^", begin_name);

                        std::string::size_type size_name = 0;
                        if(end_name != std::string::npos)
                        {
                            size_name = end_name-begin_name;
                        }
                        else
                        {
                            size_name = std::string::npos;
                        }

                        boost::property_tree::ptree tag_name;

                        tag_name.put_value(value_name.substr(begin_name, size_name));

                        tag_field.add_child(*fields_name_it, tag_name);

                        if(end_name != std::string::npos)
                        {
                            begin_name = end_name+1;
                            ++fields_name_it;
                            if(fields_name_it == fields_name.end())
                            {
                                throw Exception("Invalid Person Name");
                            }
                        }
                        else
                        {
                            begin_name = end_name;
                        }
                    }

                    tag_value.add_child(*fields_it, tag_field);

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
                result.add_child("PersonName", tag_value);
            }
        }
        else
        {
            unsigned int count = 0;
            for(auto const & item: value)
            {
                ++count;
                boost::property_tree::ptree tag_value;
                tag_value.put("<xmlattr>.number", count); // Mandatory
                tag_value.put_value(item);

                result.add_child("Value", tag_value);
            }
        }

        return result;
    }

    result_type operator()(VR const vr, Value::DataSets const & value) const
    {
        result_type result;

        result.put("<xmlattr>.vr", as_string(vr)); // Mandatory

        unsigned int count = 0;
        for(auto const & item: value)
        {
            ++count;
            boost::property_tree::ptree tag_value;
            tag_value.put("<xmlattr>.number", count); // Mandatory
            boost::property_tree::ptree tag_result = as_xml(item);
            tag_value.insert(tag_value.end(), tag_result.front().second.begin(),
                                              tag_result.front().second.end());
            result.add_child("Item", tag_value);
        }

        return result;
    }

    result_type operator()(VR const vr, Value::Binary const & value) const
    {
        result_type result;

        result.put("<xmlattr>.vr", as_string(vr)); // Mandatory

        boost::property_tree::ptree tag_value;

        unsigned char const * data =
            reinterpret_cast<unsigned char const *>(&value[0]);
        OFStringStream stream;
        OFStandard::encodeBase64(stream, data, value.size());
        tag_value.put_value(stream.str().c_str());

        result.add_child("InlineBinary", tag_value);

        return result;
    }

};

boost::property_tree::ptree as_xml(DataSet const & data_set)
{
    // XML dataset element
    boost::property_tree::ptree nativedicommodel;
    for(auto const & it: data_set)
    {
        auto const & tag = it.first;
        auto const & element = it.second;

        boost::property_tree::ptree dicomattribute = apply_visitor(ToXMLVisitor(), element);

        auto const dictionary_it = registry::public_dictionary.find(tag);
        if(dictionary_it == registry::public_dictionary.end())
        {
            throw Exception("No such element: " + std::string(tag));
        }

        dicomattribute.put("<xmlattr>.tag",  std::string(tag));                  // Mandatory
        dicomattribute.put("<xmlattr>.keyword", dictionary_it->second.keyword);  // Optional
        //dicomattribute.put("<xmlattr>.privateCreator", todo);                    // Optional

        nativedicommodel.add_child("DicomAttribute", dicomattribute);
    }

    // root element
    boost::property_tree::ptree dataset_xml;

    // Add XML dataset into root element
    dataset_xml.add_child("NativeDicomModel", nativedicommodel);

    return dataset_xml;
}

} // namespace dcmtkpp
