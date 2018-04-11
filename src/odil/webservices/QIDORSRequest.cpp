/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/


#include "odil/webservices/QIDORSRequest.h"

#include <queue>
#include <string>
#include <sstream>

#include <boost/spirit/include/qi.hpp>

#include "odil/StringStream.h"
#include "odil/VR.h"
#include "odil/webservices/ItemWithParameters.h"

namespace odil
{

namespace webservices
{

QIDORSRequest
::QIDORSRequest(const URL &base_url)
: _base_url(base_url), _media_type(),
  _representation(Representation::DICOM_JSON), _url(), _selector(),
  _query_data_set(), _fuzzymatching(false), _limit(-1), _offset(0)
{
    // Nothing else
}

QIDORSRequest
::QIDORSRequest(HTTPRequest const & request)
: _base_url(), _media_type(), _representation(), _url(), _selector(),
  _query_data_set(), _fuzzymatching(false), _limit(-1), _offset(0)
{
    if(request.has_header("Host"))
    {
        this->_url.authority = request.get_header("Host");
    }

    // Find the media type.
    auto const accept = as<ItemWithParameters>(request.get_header("Accept"));

    // if we have multipart/related, we will have then have application/dicom+xml
    // otherwise we will have application/dicom+json
    if(accept.name == "multipart/related")
    {
        auto const it = accept.name_parameters.find("type");
        // check if the type is not found
        if(it == accept.name_parameters.end())
        {
            std::ostringstream message;
            message
                << "Missing type in Accept header: "
                << request.get_header("Accept");
            throw Exception(message.str());
        }
        // check if type is different from the only available type
        if(it->second != "application/dicom+xml")
        {
            throw Exception("The only available type with multipart option is dicom+xml");
        }
        this->_media_type = it->second;
        this->_representation = Representation::DICOM_XML;
    }
    else
    {
        if(accept.name != "application/dicom+json")
        {
            throw Exception("The type cannot be different from dicom+json");
        }
        this->_media_type = accept.name;
        this->_representation = Representation::DICOM_JSON;
    }

    this->_from_url(request.get_target());
}

bool
QIDORSRequest
::operator==(QIDORSRequest const & other) const
{
    return(
        this->_base_url == other._base_url
        && this->_media_type == other._media_type
        && this->_representation == other._representation
        && this->_url == other._url
        && this->_selector == other._selector
        && *this->_query_data_set == *other._query_data_set
        && this->_fuzzymatching == other._fuzzymatching
        && this->_limit == other._limit
        && this->_offset == other._offset
    );
}

bool
QIDORSRequest
::operator!=(QIDORSRequest const & other) const
{
    return !(*this == other);
}

URL const &
QIDORSRequest
::get_base_url() const
{
    return this->_base_url;
}

void
QIDORSRequest
::set_base_url(const URL &url)
{
    this->_base_url = url;
}

std::string const &
QIDORSRequest
::get_media_type() const
{
    return this->_media_type;
}

Representation const &
QIDORSRequest
::get_representation() const
{
    return this->_representation;
}

URL const &
QIDORSRequest
::get_url() const
{
    return this->_url;
}

Selector const &
QIDORSRequest
::get_selector() const
{
    return this->_selector;
}

std::shared_ptr<DataSet const>
QIDORSRequest
::get_query_data_set() const
{
    return this->_query_data_set;
}

bool
QIDORSRequest
::get_fuzzymatching() const
{
    return this->_fuzzymatching;
}

int
QIDORSRequest
::get_limit() const
{
    return this->_limit;
}

int
QIDORSRequest
::get_offset() const
{
    return this->_offset;
}

void
QIDORSRequest
::request_datasets(
    Representation representation, Selector const & selector,
    std::shared_ptr<DataSet> query_data_set, bool fuzzymatching,
    int limit, int offset, bool numerical_tags)
{
    if(
        representation != Representation::DICOM_JSON &&
        representation != Representation::DICOM_XML)
    {
        throw Exception("Given representation is not available for QIDO-RS");
    }
    this->_representation = representation;
    this->_selector = selector;
    this->_query_data_set = query_data_set;
    this->_fuzzymatching = fuzzymatching;
    this->_limit = limit;
    this->_offset = offset;

    if(!QIDORSRequest::_is_selector_valid(selector))
    {
        throw Exception("Invalid selector");
    }

    this->_url = this->_generate_url(numerical_tags);
}

template<typename Iterator>
Element &
add_qido_element(
    Iterator begin, Iterator end, std::shared_ptr<DataSet> data_set)
{
    namespace qi = boost::spirit::qi;

    qi::rule<Iterator, std::string()> tag = +qi::alnum;
    qi::rule<Iterator, std::vector<std::string>()> attribute_id = tag % ".";

    std::vector<std::string> tags;
    auto const is_parsed = qi::phrase_parse(
        begin, end, attribute_id, qi::ascii::space, tags);
    if(!is_parsed)
    {
        throw Exception("Could not parse attribute id");
    }
    else if(begin != end)
    {
        throw Exception("Attribute id was only partially parsed");
    }

    auto current_ds = data_set;
    if(!tags.empty())
    {
        auto const last = --tags.end();
        for(auto it = tags.begin(); it != last; ++it)
        {
            Tag const tag(*it);
            if(!current_ds->has(tag))
            {
                current_ds->add(tag, {std::make_shared<odil::DataSet>()});
            }
            current_ds = current_ds->as_data_set(tag)[0];
        }
    }
    else
    {
        throw Exception("No tag in attribute list");
    }

    Tag const last(*tags.rbegin());
    if(!current_ds->has(last))
    {
        current_ds->add(last);
    }
    return (*current_ds)[last];
}

void
QIDORSRequest
::_from_url(const URL &url)
{
    this->_base_url.scheme = url.scheme;
    this->_base_url.authority = url.authority;
    std::tie(this->_base_url.path, this->_selector) = Selector::from_path(url.path);

    if (!QIDORSRequest::_is_selector_valid(this->_selector))
    {
        throw Exception(
            "Selector not correctly constructed ("
            + this->_selector.get_path(false) + ")");
    }

    auto const query_items = url.parse_query();

    // std::set<std::vector<Tag>> includefields;
    bool include_all = true;
    this->_query_data_set = std::make_shared<DataSet>();

    for(auto const & item: query_items)
    {
        if(item.first == "fuzzymatching")
        {
            if(item.second == "true")
            {
                this->_fuzzymatching = true;
            }
            else if(item.second == "false")
            {
                this->_fuzzymatching = false;
            }
            else
            {
                throw Exception("Fuzzymatching is not a boolean");
            }
        }
        else if(item.first == "limit")
        {
            try
            {
                this->_limit = std::stoi(item.second);
            }
            catch(std::invalid_argument const &)
            {
                throw Exception("Limit value is not an integer");
            }
        }
        else if(item.first == "offset")
        {
            try
            {
                this->_offset = std::stoi(item.second);
            }
            catch (std::invalid_argument const &)
            {
                throw Exception("Offset value is not an integer");
            }
        }
        else
        {
            if (item.first == "includefield")
            {
                if (item.second == "all")
                {
                    include_all = true;
                }
                else
                {
                    add_qido_element(
                        item.second.begin(), item.second.end(),
                        this->_query_data_set);
                }
            }
            else
            {
                // {AttributeID} = {value}
                auto & element = add_qido_element(
                    item.first.begin(), item.first.end(),
                    this->_query_data_set);

                if(element.is_int())
                {
                    try
                    {
                        element.as_int() = {std::stol(item.second)};
                    }
                    catch(std::invalid_argument const &)
                    {
                        throw Exception("Value must be an integer");
                    }
                }
                else if(element.is_real())
                {
                    try
                    {
                        element.as_real() = {std::stod(item.second)};
                    }
                    catch(std::invalid_argument const &)
                    {
                        throw Exception("Value must be a real");
                    }
                }
                else if(element.is_string())
                {
                    element.as_string() = {item.second};
                }
                else
                {
                    throw Exception("Invalid VR for value");
                }
            }
        }
    }

    // TODO : Fix includefields = all -> need to look for all includefields in the query_dataset (query[tag] = empty
    // with tag that can be a sequence
//    if (include_all)
//    {
//        includefields.clear();
//    }

    this->_url = this->_generate_url(false);
}


HTTPRequest
QIDORSRequest
::get_http_request() const
{
    ItemWithParameters accept;
    if (this->_representation == Representation::DICOM_JSON)
    {
        accept.name = "application/dicom+json";
    }
    else
    {
        accept.name = "multipart/related";
        accept.name_parameters["type"] = "application/dicom+xml";
    }

    std::string accept_string;
    OStringStream stream(accept_string);
    stream << accept;
    HTTPRequest::Headers const headers{ {"Accept", accept_string } };

    return HTTPRequest("GET", this->_url, "HTTP/1.0", headers);
}

bool
QIDORSRequest
::_is_selector_valid(Selector const & selector)
{
    if (!selector.get_frames().empty() || !selector.get_instance().empty())
    {
        return false;
    }
    else
    {
        return (
            // /studies
            (
                selector.is_study_present() && selector.get_study().empty()
                && !selector.is_series_present()
                && !selector.is_instance_present())
            // /studies/1.2/series
            || (
                selector.is_study_present() && !selector.get_study().empty()
                && selector.is_series_present() && selector.get_series().empty()
                && !selector.is_instance_present())
            // /series
            || (
                !selector.is_study_present() && selector.is_series_present()
                && selector.get_series().empty()
                && !selector.is_instance_present())
            // /studies/1.2/series/3.4/instances
            || (
                selector.is_study_present() && !selector.get_study().empty()
                && selector.is_series_present()
                && !selector.get_series().empty()
                && selector.is_instance_present())
            // /studies/1.2/instances
            || (
                selector.is_study_present() && !selector.get_study().empty()
                && !selector.is_series_present()
                && selector.is_instance_present())
            // /instances
            || (
                !selector.is_study_present() && !selector.is_series_present()
                && selector.is_instance_present())
        );
    }
}

std::string
QIDORSRequest
::_tag_to_string(Tag const & tag, bool numerical_tag)
{
    if(numerical_tag)
    {
        return std::string(tag);
    }
    else
    {
        try
        {
            return tag.get_name();
        }
        catch(Exception const &)
        {
            return std::string(tag);
        }
    }
}

URL
QIDORSRequest
::_generate_url(bool numerical_tags)
{
    // Breadth-first walk of the query data set to generate the query terms
    // (e.g. PatientName=Doe) and the include fields
    std::queue<std::pair<std::shared_ptr<odil::DataSet const>, std::string>> queue;
    queue.emplace(std::make_pair(this->_query_data_set, ""));

    std::vector<std::string> terms;
    std::vector<std::string> include_fields;

    while(!queue.empty())
    {
        auto const & front = queue.front();

        auto const & parent_data_set = front.first;
        auto const & parent_path = front.second;

        for(auto const & item: *parent_data_set)
        {
            auto const & tag = item.first;
            auto const & element = item.second;

            std::string child_path = parent_path;
            child_path += (child_path.empty() ? "" : ".");
            child_path += QIDORSRequest::_tag_to_string(tag, numerical_tags);

            if(element.is_data_set())
            {
                queue.emplace(
                    std::make_pair(element.as_data_set()[0], child_path));
            }
            else
            {
                if(element.empty())
                {
                    include_fields.push_back(child_path);
                }
                else
                {
                    std::ostringstream term_stream;
                    term_stream << child_path << "=";
                    if(element.is_int())
                    {
                        term_stream << element.as_int()[0];
                    }
                    else if(element.is_real())
                    {
                        term_stream << element.as_real()[0];
                    }
                    else if(element.is_string())
                    {
                        term_stream << element.as_string()[0];
                    }
                    else
                    {
                        throw Exception(
                            "Query element cannot have VR "
                            + as_string(element.vr));
                    }
                    terms.push_back(term_stream.str());
                }
            }
        }
        queue.pop();
    }

    // Build the query string: search terms (with value), include fields
    // (without value), fuzzy matching, limit and offset
    std::ostringstream query_string_stream;
    for(auto const & term: terms)
    {
        query_string_stream
            << (query_string_stream.tellp()>0 ? "&" : "")
            << term;
    }

    for(auto const & field: include_fields)
    {
        query_string_stream
            << (query_string_stream.tellp()>0 ? "&" : "")
            << "includefield=" << field;
    }

    query_string_stream
        << (query_string_stream.tellp()>0 ? "&" : "")
        << "fuzzymatching=" << std::boolalpha << this->_fuzzymatching;

    if(this->_limit != -1)
    {
        query_string_stream
            << (query_string_stream.tellp()>0 ? "&" : "")
            << "limit=" << this->_limit;
        if(this->_offset != 0)
        {
            query_string_stream
                << (query_string_stream.tellp()>0 ? "&" : "")
                << "offset=" << this->_offset;
        }
    }

    return {
        this->_base_url.scheme, this->_base_url.authority,
        // Frames are never included in QIDO
        this->_base_url.path + this->_selector.get_path(false),
        query_string_stream.str() };
}

}

}
