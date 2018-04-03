/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <iterator>
#include <map>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "odil/base64.h"
#include "odil/DataSet.h"
#include "odil/registry.h"
#include "odil/Value.h"
#include "odil/xml_converter.h"

namespace
{

template<typename TIterator>
std::string join(TIterator first, TIterator last, std::string const & separator)
{
    std::string joined;
    bool is_first=true;
    while(first != last)
    {
        if(!is_first)
        {
            joined += separator;
        }
        joined += *first;
        is_first = false;
        ++first;
    }
    return joined;
}

template<typename TIterator>
void split(
    std::string const & string, std::string const & separator,
    TIterator destination)
{
    std::string::size_type begin=0;
    while(begin < string.size())
    {
        auto end = std::min(string.find(separator, begin), string.size());
        *destination = string.substr(begin, end-begin);
        ++destination;
        begin = end+1;
    }
}

}

namespace odil
{

/// @brief Element visitor converting to XML.
struct ToXMLVisitor
{
    BulkDataCreator bulk_data_creator;

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

    result_type operator()(VR const vr, Value::Strings const & value) const
    {
        result_type result;

        result.put("<xmlattr>.vr", as_string(vr)); // Mandatory

        if(vr == VR::PN)
        {
            std::vector<std::string> const representation_names{
                "Alphabetic", "Ideographic", "Phonetic" };
            std::vector<std::string> const field_names{
                "FamilyName", "GivenName", "MiddleName", "NamePrefix",
                "NameSuffix" };

            unsigned int count = 0;
            for(auto const & item: value)
            {
                ++count;
                boost::property_tree::ptree tag_value;
                tag_value.put("<xmlattr>.number", count); // Mandatory

                std::vector<std::string> representations;
                split(item, "=", std::back_inserter(representations));
                for(unsigned int r=0;
                    r<std::min(representation_names.size(), representations.size());
                    ++r)
                {
                    if(representations[r].empty())
                    {
                        continue;
                    }

                    boost::property_tree::ptree representation_node;

                    std::vector<std::string> fields;
                    split(representations[r], "^", std::back_inserter(fields));
                    for(unsigned int f=0;
                        f<std::min(field_names.size(), fields.size()); ++f)
                    {
                        if(fields[f].empty())
                        {
                            continue;
                        }

                        representation_node.put(field_names[f], fields[f]);
                    }

                    tag_value.add_child(
                        representation_names[r], representation_node);
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
            boost::property_tree::ptree tag_result = as_xml(
                item, this->bulk_data_creator);
            tag_value.insert(tag_value.end(), tag_result.front().second.begin(),
                                              tag_result.front().second.end());
            result.add_child("Item", tag_value);
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

        result.put("<xmlattr>.vr", as_string(vr)); // Mandatory

        boost::property_tree::ptree tag_value;

        std::string encoded;
        encoded.reserve(value[0].size()*4/3);
        base64::encode(value[0].begin(), value[0].end(), std::back_inserter(encoded));
        tag_value.put_value(encoded);

        result.add_child("InlineBinary", tag_value);

        return result;
    }
};

boost::property_tree::ptree as_xml(
    std::shared_ptr<DataSet const> data_set,
    BulkDataCreator const & bulk_data_creator)
{
    ToXMLVisitor visitor;
    visitor.bulk_data_creator = bulk_data_creator;

    // XML dataset element
    boost::property_tree::ptree nativedicommodel;
    for(auto const & it: *data_set)
    {
        auto const & tag = it.first;
        auto const & element = it.second;

        boost::property_tree::ptree dicomattribute;

        auto const bulk_data_info =
            bulk_data_creator?bulk_data_creator(data_set, tag)
            :std::make_pair(std::string(), std::string());
        if(!bulk_data_info.first.empty())
        {
            boost::property_tree::ptree bulk_data_element;
            bulk_data_element.put(
                "<xmlattr>."+bulk_data_info.first, bulk_data_info.second);
            dicomattribute.add_child("BulkData", bulk_data_element);
            dicomattribute.put("<xmlattr>.vr", as_string(element.vr));
        }
        else
        {
            dicomattribute = apply_visitor(visitor, element);
        }
        // Add Mandatory attribute Tag
        dicomattribute.put("<xmlattr>.tag",  std::string(tag));
        // Add Optional attribute Keyword
        auto const dictionary_it = registry::public_dictionary.find(tag);
        if(dictionary_it != registry::public_dictionary.end())
        {
            dicomattribute.put(
                "<xmlattr>.keyword", dictionary_it->second.keyword);
        }
        // Add Optional attribute PrivateCreator
        //dicomattribute.put("<xmlattr>.privateCreator", todo);
        nativedicommodel.add_child("DicomAttribute", dicomattribute);
    }

    // root element
    boost::property_tree::ptree dataset_xml;

    // Add XML dataset into root element
    dataset_xml.add_child("NativeDicomModel", nativedicommodel);

    return dataset_xml;
}

void parse_value(
    boost::property_tree::ptree const & xml, Element & element)
{
    auto const number = xml.get<unsigned int>("<xmlattr>.number");
    if(element.is_int())
    {
        element.as_int()[number-1] = xml.get_value<Value::Integer>();
    }
    else if(element.is_real())
    {
        element.as_real()[number-1] = xml.get_value<Value::Real>();
    }
    else if(element.is_string())
    {
        // FIXME: Orthanc does not split strings using backslash
        element.as_string()[number-1] = xml.get_value<Value::String>();
    }
    // SQ is handled by parse_item
    // Binary is handled by parse_inline_binary
    else
    {
        throw Exception("Cannot parse "+as_string(element.vr)+" as Value");
    }
}

void parse_bulk_data(
    boost::property_tree::ptree const & xml, Element & element)
{
    try
    {
        element.as_string() = {xml.get<std::string>("<xmlattr>.uri")};
    }
    catch(boost::property_tree::ptree_bad_path const &)
    {
        element.as_string() = {xml.get<std::string>("<xmlattr>.uuid")};
    }
}

void parse_person_name(
    boost::property_tree::ptree const & xml, Element & element)
{
    auto const number = xml.get<unsigned int>("<xmlattr>.number");

    std::vector<std::string> const representations = {
        "Alphabetic", "Ideographic", "Phonetic"
    };
    std::vector<std::string> names;
    for(auto const & representation: representations)
    {
        auto const representation_it = xml.find(representation);
        if(representation_it == xml.not_found())
        {
            names.push_back("");
        }
        else
        {
            std::vector<std::string> name;

            std::vector<std::string> const components = {
                "FamilyName", "GivenName", "MiddleName", "NamePrefix", "NameSuffix"};
            for(auto const & component: components)
            {
                auto const & component_it = representation_it->second.find(component);
                if(component_it == representation_it->second.not_found())
                {
                    name.push_back("");
                }
                else
                {
                    name.push_back(component_it->second.get_value<std::string>());
                }
            }

            while(!name.empty() && name.rbegin()->empty())
            {
                name.pop_back();
            }

            names.push_back(join(name.begin(), name.end(), "^"));
        }
    }

    while(!names.empty() && names.rbegin()->empty())
    {
        names.pop_back();
    }

    element.as_string()[number-1] = join(names.begin(), names.end(), "=");
}

void parse_attributes(
    boost::property_tree::ptree const & xml, std::shared_ptr<DataSet> data_set);

void parse_item(
    boost::property_tree::ptree const & xml, Element & element)
{
    auto data_set = std::make_shared<DataSet>();
    parse_attributes(xml, data_set);
    auto const number = xml.get<unsigned int>("<xmlattr>.number");
    element.as_data_set()[number-1] = data_set;
}

void parse_inline_binary(
    boost::property_tree::ptree const & xml, Element & element)
{
    auto const & encoded = xml.get_value<std::string>();
    Value::Binary::value_type decoded;
    decoded.reserve(encoded.size()*3/4);
    base64::decode(
        encoded.begin(), encoded.end(),
        std::back_inserter(decoded));
    element.as_binary() = { decoded };
}

void parse_attributes(
    boost::property_tree::ptree const & xml, std::shared_ptr<DataSet> data_set)
{
    auto const attributes = xml.equal_range("DicomAttribute");
    for(auto attribute = attributes.first; attribute != attributes.second; ++attribute)
    {
        auto const & children = attribute->second;

        Tag const tag(children.get<std::string>("<xmlattr>.tag"));
        VR const vr = as_vr(children.get<std::string>("<xmlattr>.vr"));

        Element element(VR::UN);

        std::pair<
            boost::property_tree::ptree::const_assoc_iterator,
            boost::property_tree::ptree::const_assoc_iterator> range(
                children.not_found(), children.not_found());
        std::function<void(boost::property_tree::ptree const &, Element &)> parser;
        boost::property_tree::ptree normalized;
        if(children.find("Value") != children.not_found())
        {
            range = children.equal_range("Value");
            if(vr != VR::LT && vr != VR::ST && vr != VR::UT)
            {
                // Some providers use a wrong representation where multi-valued
                // elements are joined using \\ instead of using multiple
                // <Value> elements. Be nice to them.
                bool must_normalize = false;
                for(auto it=range.first; it != range.second; ++it)
                {
                    auto const value = it->second.get_value<std::string>();
                    if(value.find("\\") != std::string::npos)
                    {
                        must_normalize = true;
                        break;
                    }
                }
                if(must_normalize)
                {
                    int count=0;
                    for(auto it=range.first; it != range.second; ++it)
                    {
                        auto const original_value =
                            it->second.get_value<std::string>();
                        std::vector<std::string> values;
                        split(original_value, "\\", std::back_inserter(values));
                        for(auto const & value: values)
                        {
                            boost::property_tree::ptree value_node;
                            value_node.put("<xmlattr>.number", 1+count);
                            value_node.put_value(value);
                            normalized.add_child("Value", value_node);
                            ++count;
                        }
                    }
                    range = normalized.equal_range("Value");
                }
                // Otherwise, nothing to do: range is OK
            }
            // Otherwise, nothing to do: range is OK
            element = Element(vr);
            parser = parse_value;
        }
        else if(children.find("BulkData") != children.not_found())
        {
            range = children.equal_range("BulkData");
            element = Element(VR::UR);
            parser = parse_bulk_data;
        }
        else if(children.find("PersonName") != children.not_found())
        {
            range = children.equal_range("PersonName");
            element = Element(VR::PN);
            parser = parse_person_name;
        }
        else if(children.find("Item") != children.not_found())
        {
            range = children.equal_range("Item");
            element = Element(VR::SQ);
            parser = parse_item;
        }
        else if(children.find("InlineBinary") != children.not_found())
        {
            range = children.equal_range("InlineBinary");
            element = Element(vr);
            parser = parse_inline_binary;
        }
        else
        {
            element = Element(vr);
            parser = [](boost::property_tree::ptree const &, Element &) {};
        }

        auto const size = range.first==children.not_found()?0
            :std::distance(range.first, range.second);
        if(element.is_int())
        {
            element.as_int().resize(size);
        }
        else if(element.is_real())
        {
            element.as_real().resize(size);
        }
        else if(element.is_string())
        {
            element.as_string().resize(size);
        }
        else if(element.is_data_set())
        {
            element.as_data_set().resize(size);
        }
        else if(element.is_binary())
        {
            element.as_binary().resize(size);
        }
        else
        {
            throw Exception("Cannot resize "+as_string(vr));
        }

        for(auto it = range.first; it != range.second; ++it)
        {
            parser(it->second, element);
        }

        data_set->add(tag, element);
    }
}

std::shared_ptr<DataSet> as_dataset(boost::property_tree::ptree const & xml)
{
    if(xml.size() < 1 || xml.front().first != "NativeDicomModel")
    {
        throw Exception("Missing root node NativeDicomModel");
    }

    auto data_set = std::make_shared<DataSet>();

    auto const & root = xml.get_child("NativeDicomModel");
    parse_attributes(root, data_set);
    return data_set;
}

} // namespace odil
