/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/webservices/STOWRSRequest.h"

#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/version.hpp>

#include <json/json.h>

#include "odil/DataSet.h"
#include "odil/json_converter.h"
#include "odil/Reader.h"
#include "odil/VRFinder.h"
#include "odil/Writer.h"
#include "odil/webservices/ItemWithParameters.h"
#include "odil/webservices/multipart_related.h"
#include "odil/webservices/Selector.h"
#include "odil/webservices/Utils.h"
#include "odil/webservices/URL.h"
#include "odil/xml_converter.h"


namespace  odil
{

namespace webservices
{

STOWRSRequest
::STOWRSRequest(URL const & base_url)
    : _base_url(base_url), _selector(), _url(), _media_type(""),
      _representation(), _data_sets()
{
    // Nothing else.
}

STOWRSRequest
::STOWRSRequest(HTTPRequest const & request)
{
    this->_url = request.get_target();
    if (request.has_header("Host"))
    {
        this->_url.authority = request.get_header("Host");
    }

    // find the media type in Content-Type header
    if (!request.has_header("Content-Type"))
    {
        throw Exception("Cannot parse request : Content-Type header is missing");
    }
    auto const header_content_type = boost::lexical_cast<ItemWithParameters>(
        request.get_header("Content-Type"));
    if (header_content_type.name == "multipart/related")
    {
        auto const it = header_content_type.name_parameters.find("type");
        if(it == header_content_type.name_parameters.end())
        {
            std::ostringstream message;
            message << "Missing type is Accept header :"
                    << request.get_header("Accept");
            throw Exception(message.str());
        }
        this->_media_type = it->second;
    }
    else
    {
        throw Exception("Malformed Content-Type header");
    }

    if (this->_media_type == "application/dicom")
    {
        this->_representation = Representation::DICOM;
        auto const converter =
            [](Message const & part)
            {
                std::stringstream stream(part.get_body());
                Reader reader(stream, odil::registry::ExplicitVRLittleEndian);
                auto const ds = reader.read_file(stream);
                return ds.second;
            };
        transform_parts(
            request, std::back_inserter(this->get_data_sets()), converter);
    }
    else if (this->_media_type == "application/dicom+xml")
    {
        this->_representation = Representation::DICOM_XML;
        std::map< std::string, std::string> uuid_to_bulk_raw;

        auto converter_part =
            [&uuid_to_bulk_raw, this](Message const & part)
            {
                auto const header_content_type = boost::lexical_cast<ItemWithParameters>(
                    part.get_header("Content-Type"));
                if (header_content_type.name == "application/dicom+xml")
                {
                    // get the transfer syntax in the ContentType header
                    auto const transfer_syntax_it = header_content_type.name_parameters.find(
                        "transfer-syntax");
                    std::string transfer_syntax;
                    if(transfer_syntax_it != header_content_type.name_parameters.end())
                    {
                        transfer_syntax = transfer_syntax_it->second;
                    }
                    else
                    {
                        throw Exception("Transfer-syntax option is missing in the header");
                    }
                    // Check here if correct probably ok
                    std::stringstream stream(part.get_body());
                    boost::property_tree::ptree xml;
                    boost::property_tree::read_xml(stream, xml);
                    this->get_data_sets().push_back(as_dataset(xml));
                }
                else
                {
                    auto const location = part.get_header("Content-Location");
                    uuid_to_bulk_raw.insert(std::make_pair(location, part.get_body()));
                }
            };

        for_each_part(request, converter_part);

        // Here restore dataSets to their initial states (With Bulk Data in the correct location)
        for (auto & data_set : this->get_data_sets())
        {
            STOWRSRequest::_restore_data_set(data_set, uuid_to_bulk_raw);
        }
    }
    else if (this->_media_type == "application/dicom+json")
    {
        this->_representation = Representation::DICOM_JSON;
        std::map< std::string, std::string> uuid_to_bulk_raw;

        auto converter_part =
            [&uuid_to_bulk_raw, this](Message const & part)
            {
                auto const header_content_type = boost::lexical_cast<ItemWithParameters>(
                    part.get_header("Content-Type"));
                if (header_content_type.name == "application/dicom+json")
                {
                    // get the transfer syntax in the ContentType header
                    auto const transfer_syntax_it = header_content_type.name_parameters.find(
                        "transfer-syntax");
                    std::string transfer_syntax;
                    if(transfer_syntax_it != header_content_type.name_parameters.end())
                    {
                        transfer_syntax = transfer_syntax_it->second;
                    }
                    else
                    {
                        throw Exception("Transfer-syntax option is missing in the header");
                    }
                    std::stringstream stream(part.get_body());
                    Json::Value array;
                    stream >> array;
                    if(!array.isArray())
                    {
                        throw Exception("Body must be an array");
                    }
                    this->get_data_sets().push_back(as_dataset(array[0]));
                }
                else
                {
                    auto const location = part.get_header("Content-Location");
                    uuid_to_bulk_raw.insert(std::make_pair(location, part.get_body()));
                }
            };
        for_each_part(request, converter_part);

        // Here restore dataSets to their initial state (With Bulk Data in the correct location)
        for (auto & data_set : this->get_data_sets())
        {
            STOWRSRequest::_restore_data_set(data_set, uuid_to_bulk_raw);
        }
    }
    else
    {
        throw Exception("Unknown media type" + this->_media_type);
    }
    std::tie(this->_base_url, this->_selector) =
            STOWRSRequest::_split_full_url(this->_url);
}

bool
STOWRSRequest
::operator==(STOWRSRequest const & other) const
{
    return(
        this->_base_url == other._base_url
        && this->_selector == other._selector
        && this->_url == other._url
        && this->_data_sets == other._data_sets
        && this->_representation == other._representation
        && this->_media_type == other._media_type);
}

bool
STOWRSRequest
::operator!=(STOWRSRequest const & other) const
{
    return !(*this == other);
}

std::pair<URL, Selector>
STOWRSRequest
::_split_full_url(URL const &url)
{
    URL base_url;

    std::string study;
    auto const position = url.path.rfind("/studies");

    if (position != std::string::npos)
    {
        base_url = {
            url.scheme, url.authority, url.path.substr(0, position), "", "" };
        auto const resource = url.path.substr(position+1);

        typedef std::string::const_iterator Iterator;

        namespace qi = boost::spirit::qi;
        namespace p = boost::phoenix;

        using boost::spirit::qi::digit;
        using boost::spirit::qi::lit;
        using boost::spirit::qi::string;
        using boost::spirit::qi::_1;

        qi::rule<Iterator, std::string()> uid = digit >> *(string(".") >> +digit);

        qi::rule<Iterator> retrieve_study =
            lit("studies/") >> uid[p::ref(study) = _1];

        auto iterator = resource.begin();
        qi::phrase_parse(
            iterator, resource.end(),
            retrieve_study,
            boost::spirit::qi::ascii::space
        );
    }

    Selector selector({{"studies", study}});

    return std::make_pair(base_url, selector);
}

bool
STOWRSRequest
::_is_selector_valid(Selector const & selector)
{
    return (selector.is_study_present() && !selector.is_series_present()
            && !selector.is_instance_present() && selector.get_frames().empty());
}

void
STOWRSRequest
::request_dicom(std::vector<DataSet> const & data_sets, Selector const & selector,
                Representation const & representation)
{
    switch (representation)
    {
    case Representation::DICOM :
        this->_representation = Representation::DICOM;
        this->_media_type = "application/dicom";
        break;
    case Representation::DICOM_XML :
        this->_representation = Representation::DICOM_XML;
        this->_media_type = "application/dicom+xml";
        break;
    case Representation::DICOM_JSON :
        this->_representation = Representation::DICOM_JSON;
        this->_media_type = "application/dicom+json";
        break;
    default :
        throw Exception("Invalid representation");
        break;
    }

    this->_data_sets = data_sets;
    if (!_is_selector_valid(selector))
    {
        throw Exception("Selector is not valid (" + selector.get_path(false) + ")");
    }
    this->_selector = selector;
    auto path = this->_base_url.path + selector.get_path(false);
    this->_url = {
        this->_base_url.scheme, this->_base_url.authority, path, "", ""};
}

std::vector<DataSet> const &
STOWRSRequest
::get_data_sets() const
{
    return _data_sets;
}

std::vector<DataSet> &
STOWRSRequest
::get_data_sets()
{
    return this->_data_sets;
}

URL const &
STOWRSRequest
::get_base_url() const
{
    return this->_base_url;
}

void
STOWRSRequest
::set_base_url(URL const & url)
{
    this->_base_url = url;
}

std::string const &
STOWRSRequest
::get_media_type() const
{
    return this->_media_type;
}

Representation const &
STOWRSRequest
::get_representation() const
{
    return this->_representation;
}

URL const &
STOWRSRequest
::get_url() const
{
    return this->_url;
}

Selector const &
STOWRSRequest
::get_selector() const
{
    return this->_selector;
}

HTTPRequest
STOWRSRequest
::get_http_request() const
{
    HTTPRequest request;
    if(this->_representation == Representation::DICOM)
    {
        auto const accumulator =
            [](DataSet const & data_set)
            {
                std::ostringstream stream(
                    std::ios_base::out | std::ios_base::binary);
                odil::Writer::write_file(
                    data_set, stream, DataSet());
                return Message(
                    {
                        {
                            "Content-Type",
                            ItemWithParameters(
                            "application/dicom",
                            {})
                        }
                    },
                    stream.str()
                );
            };
        auto const boundary = random_boundary();
        std::ostringstream body;
        accumulate_parts(
            this->get_data_sets().begin(), this->get_data_sets().end(),
            accumulator, body, boundary);
        request.set_body(body.str());

        request.set_header(
            "Content-Type",
            ItemWithParameters(
                "multipart/related", {
                            {"type", "application/dicom"},
                            {"boundary", boundary}}));
    }
    else if(this->_representation == Representation::DICOM_JSON)
    {
        std::vector<BulkData> bulk_data;

        // Copy the dataSets in order to let them unchanged
        std::vector<odil::DataSet> copy = this->_data_sets;
        for (auto & ds :copy)
        {
            STOWRSRequest::_extract_bulk_data(ds, bulk_data);
        }
        auto const accumulator_bulk_data =
            [](BulkData const & bulk_data)
            {
                return Message(
                    {
                        { "Content-Type", bulk_data.type },
                        { "Content-Location", bulk_data.location }
                    },
                { bulk_data.data.begin(), bulk_data.data.end() }
                );
            };
        auto const default_transfer_syntax =
            odil::registry::ExplicitVRLittleEndian;
        auto const accumulator_meta_data =
            [default_transfer_syntax](DataSet const & data_set)
            {
                Json::Value json;
                json.resize(1);
                json[0] = as_json(data_set);
                auto const transfer_syntax =
                    data_set.get_transfer_syntax().empty()
                        ?default_transfer_syntax
                        :data_set.get_transfer_syntax();

                Json::FastWriter writer;
                return Message(
                    {{
                        "Content-Type",
                        ItemWithParameters(
                            "application/dicom+json",
                            {{"transfer-syntax", transfer_syntax}})
                    }},
                    writer.write(json)
                );
            };
        auto const boundary = random_boundary();
        std::ostringstream body;
        // add here first the meta_data
        accumulate_parts(
            copy.begin(), copy.end(),
            accumulator_meta_data, body, boundary);
        // add then the bulk data
        if (!bulk_data.empty())
        {
            // Remove the last boundary of the message
            auto body_content = body.str();
            for (int i=0; i < boundary.size() + 6*sizeof(char); ++i)
            {
                body_content.pop_back();
            }
            body.str(std::string()); // clear the content
            body << body_content;

            accumulate_parts(
                bulk_data.begin(), bulk_data.end(),
                accumulator_bulk_data, body, boundary);
        }

        request.set_body(body.str());

        request.set_header(
            "Content-Type",
            ItemWithParameters(
                "multipart/related", {
                    {"type", "application/dicom+json"},
                    {"boundary", boundary}}));
    }
    else if(this->_representation == Representation::DICOM_XML)
    {
        std::vector<BulkData> bulk_data;

        // Copy the dataSets in order to let them unchanged
        std::vector<odil::DataSet> copy = this->_data_sets;
        for (auto & ds :copy)
        {
            STOWRSRequest::_extract_bulk_data(ds, bulk_data);
        }

        auto const accumulator_bulk_data =
            [](BulkData const & bulk_data)
            {
                return Message(
                    {
                        { "Content-Type", bulk_data.type },
                        { "Content-Location", bulk_data.location }
                    },
                { bulk_data.data.begin(), bulk_data.data.end() }
                );
            };

        auto const default_transfer_syntax =
            odil::registry::ExplicitVRLittleEndian;
        auto const accumulator_meta_data =
            [default_transfer_syntax](DataSet const & data_set)
            {
                auto const xml = as_xml(data_set);
                std::ostringstream stream;

#if BOOST_VERSION >= 105600
                typedef boost::property_tree::xml_writer_settings<std::string> SettingsType;
#else
                typedef boost::property_tree::xml_writer_settings<char> SettingsType;
#endif

                boost::property_tree::write_xml(stream, xml, SettingsType());

                auto const transfer_syntax =
                    data_set.get_transfer_syntax().empty()
                        ?default_transfer_syntax
                        :data_set.get_transfer_syntax();

                return Message(
                    {{
                        "Content-Type",
                        ItemWithParameters(
                            "application/dicom+xml",
                            {{"transfer-syntax", transfer_syntax}})
                    }},
                    stream.str()
                );
            };

        auto const boundary = random_boundary();
        std::ostringstream body;
        // add here first the meta_data
        accumulate_parts(
            copy.begin(), copy.end(),
            accumulator_meta_data, body, boundary);
        // add then the bulk data
        if (!bulk_data.empty())
        {
            // Remove the last boundary of the message
            auto body_content = body.str();
            for (int i=0; i < boundary.size() + 6*sizeof(char); ++i)
            {
                body_content.pop_back();
            }
            body.str(std::string()); // clear the content
            body << body_content;

            accumulate_parts(
                bulk_data.begin(), bulk_data.end(),
                accumulator_bulk_data, body, boundary);
        }

        request.set_body(body.str());

        request.set_header(
            "Content-Type",
            ItemWithParameters(
                "multipart/related", {
                    {"type", "application/dicom+xml"},
                    {"boundary", boundary}}));
    }
    else
    {
        throw Exception("Unknown type");
    }
    request.set_method("POST");
    request.set_target(this->_url);
    request.set_http_version("HTTP/1.0");
    return request;
}

void
STOWRSRequest
::_extract_bulk_data(DataSet &data_set, std::vector<BulkData> & bulk_data)
{
    for (auto &it : data_set)
    {
        auto & tag = it.first;
        auto & element = it.second;
        if (data_set.is_binary(tag))
        {
            // 1. generate uuid
            boost::uuids::random_generator gen;
            boost::uuids::uuid uuid = gen();
            std::string uuid_string = boost::uuids::to_string(uuid);

            // 2. Get Transfer Syntax from dataSet
            auto const default_transfer_syntax =
                odil::registry::ExplicitVRLittleEndian;
            std::string const & transfer_syntax =
                    data_set.get_transfer_syntax().empty()
                        ?default_transfer_syntax
                        :data_set.get_transfer_syntax();

            // 3. Create a new BulkData
            BulkData data;
            data.data = *element.as_binary().data();
            data.location = uuid_string;
            if (tag == odil::registry::PixelData)
            {
                data.type = STOWRSRequest::_media_type_from_transfer_syntax(transfer_syntax);
            }
            else
            {
                data.type = "application/octet-stream";
            }

            // 4. add an entry to uuid_to_bulk
            bulk_data.push_back(data);

            // 5. Update the data_set giving in parameter
            data_set.add(tag, {uuid_string}, odil::VR::UR);
        }
        else if (data_set.is_data_set(tag))
        {
            // Case of sequence with multiple sub-elements
            for (auto sq : data_set.as_data_set(tag))
            {
                STOWRSRequest::_extract_bulk_data(sq, bulk_data);
            }
        }
        else
        {
            // Do nothing
        }
    }
}

void
STOWRSRequest
::_restore_data_set(DataSet &data_set, std::map<std::string, std::string>& uuid_bulk_raw)
{
    for (auto & it : data_set)
    {
        auto & tag = it.first;
        auto & element = it.second;
        if (data_set.get_vr(tag) == odil::VR::UR)
        {
            if (uuid_bulk_raw.find(element.as_string()[0]) !=
                    uuid_bulk_raw.end())
            {
                auto const uuid = element.as_string()[0];
                auto const bulk = uuid_bulk_raw.at(uuid);
                std::stringstream stream(bulk);

                auto const default_transfer_syntax =
                    odil::registry::ExplicitVRLittleEndian;
                std::string const & transfer_syntax =
                        data_set.get_transfer_syntax().empty()
                            ?default_transfer_syntax
                            :data_set.get_transfer_syntax();

                Reader reader(stream, transfer_syntax);
                std::vector<uint8_t>  data;
                for (auto const character : bulk)
                {
                    data.push_back(character);
                }

                // Update the data_set
                odil::VRFinder vr_finder;
                odil::VR vr = vr_finder(tag, data_set, transfer_syntax);
                data_set.add(tag, odil::Value::Binary({data}), vr);
            }
            else
            {
                // Do nothing (some other UR but not concerned by the bulk data restoration)
            }
        }
        else if (data_set.is_data_set(tag))
        {
            for (auto sq : data_set.as_data_set(tag))
            {
                STOWRSRequest::_restore_data_set(sq, uuid_bulk_raw);
            }
        }
        else
        {
            // Do nothing
        }
    }
}

std::string
STOWRSRequest
::_media_type_from_transfer_syntax(std::string const & transfer_syntax)
{
    std::map<std::string, std::string> transfer_syntax_media_type =
    {
        {"1.2.840.10008.1.2.1" , "application/octet-stream"},
        {"1.2.840.10008.1.2.4.70" , "image/jpeg"},
        {"1.2.840.10008.1.2.4.50" , "image/jpeg"},
        {"1.2.840.10008.1.2.4.51" , "image/jpeg"},
        {"1.2.840.10008.1.2.4.57" , "image/jpeg"},
        {"1.2.840.10008.1.2.5"    , "image/x-dicom-rle"},
        {"1.2.840.10008.1.2.4.80" , "image/x-jls"},
        {"1.2.840.10008.1.2.4.81" , "image/x-jls"},
        {"1.2.840.10008.1.2.4.90" , "image/jp2"},
        {"1.2.840.10008.1.2.4.91" , "image/jp2"},
        {"1.2.840.10008.1.2.4.92" , "image/jpx"},
        {"1.2.840.10008.1.2.4.93" , "image/jpx"},
        {"1.2.840.10008.1.2.4.100" , "video/mpeg2"},
        {"1.2.840.10008.1.2.4.101" , "video/mpeg2"},
        {"1.2.840.10008.1.2.4.102" , "video/mp4"},
        {"1.2.840.10008.1.2.4.103" , "video/mp4"},
        {"1.2.840.10008.1.2.4.104" , "video/mp4"},
        {"1.2.840.10008.1.2.4.105" , "video/mp4"},
        {"1.2.840.10008.1.2.4.106" , "video/mp4"},
    };

    return transfer_syntax_media_type.at(transfer_syntax);
}

}

}
