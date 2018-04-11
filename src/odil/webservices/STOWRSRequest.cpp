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
#include "odil/StringStream.h"
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
: _base_url(base_url), _transfer_syntax(""), _selector(), _url(),
  _media_type(""), _representation(), _data_sets()
{
    // Nothing else.
}

STOWRSRequest
::STOWRSRequest(HTTPRequest const & request)
{
    this->_url = request.get_target();
    if(request.has_header("Host"))
    {
        this->_url.authority = request.get_header("Host");
    }

    auto const content_type = as<ItemWithParameters>(
        request.get_header("Content-Type"));
    if(content_type.name == "multipart/related")
    {
        this->_media_type = content_type.name_parameters.at("type");
    }
    else
    {
        throw Exception("Malformed Content-Type header");
    }

    if(this->_media_type == "application/dicom")
    {
        this->_representation = Representation::DICOM;

        transform_parts(
            request, std::back_inserter(this->get_data_sets()),
            [](Message const & part)
            {
                IStringStream stream(
                    &part.get_body()[0], part.get_body().size());
                Reader reader(stream, registry::ExplicitVRLittleEndian);
                auto const ds = reader.read_file(stream);
                return ds.second;
            });
    }
    else if(this->_media_type == "application/dicom+xml")
    {
        this->_representation = Representation::DICOM_XML;

        // Get data sets and bulk data from parts
        BulkMap bulk_map;
        for_each_part(
            request,
            [&bulk_map, this](Message const & part)
            {
                auto const content_type = as<ItemWithParameters>(
                    part.get_header("Content-Type"));
                if(content_type.name == "application/dicom+xml")
                {
                    this->_transfer_syntax = content_type.name_parameters.at(
                        "transfer-syntax");

                    IStringStream stream(
                        &part.get_body()[0], part.get_body().size());
                    boost::property_tree::ptree xml;
                    boost::property_tree::read_xml(stream, xml);
                    this->get_data_sets().push_back(as_dataset(xml));
                }
                else
                {
                    auto const location = part.get_header("Content-Location");
                    Value::Binary::value_type const data(
                        part.get_body().begin(), part.get_body().end());
                    bulk_map.insert({location, data});
                }
            });

        // Restore bulk data items to data sets
        for(auto & data_set : this->get_data_sets())
        {
            STOWRSRequest::_restore_data_set(data_set, bulk_map);
        }
    }
    else if (this->_media_type == "application/dicom+json")
    {
        this->_representation = Representation::DICOM_JSON;

        // Get data sets and bulk data from parts
        BulkMap bulk_map;
        for_each_part(
            request,
            [&bulk_map, this](Message const & part)
            {
                auto const content_type = as<ItemWithParameters>(
                    part.get_header("Content-Type"));
                if(content_type.name == "application/dicom+json")
                {
                    this->_transfer_syntax = content_type.name_parameters.at(
                        "transfer-syntax");

                    IStringStream stream(
                        &part.get_body()[0], part.get_body().size());
                    Json::Value array;
                    stream >> array;
                    if(!array.isArray())
                    {
                        throw Exception("Body must be an array");
                    }

                    for(auto const & json: array)
                    {
                        this->get_data_sets().push_back(as_dataset(json));
                    }
                }
                else
                {
                    auto const location = part.get_header("Content-Location");
                    Value::Binary::value_type const data{
                        part.get_body().begin(), part.get_body().end()};
                    bulk_map.insert({location, data});
                }
            });

        // Restore bulk data items to data sets
        for(auto & data_set: this->get_data_sets())
        {
            STOWRSRequest::_restore_data_set(data_set, bulk_map);
        }
    }
    else
    {
        throw Exception("Unknown media type: " + this->_media_type);
    }

    this->_base_url.scheme = request.get_target().scheme;
    this->_base_url.authority = request.get_target().authority;
    std::tie(this->_base_url.path, this->_selector) = Selector::from_path(
        request.get_target().path);
    if(!STOWRSRequest::_is_selector_valid(this->_selector))
    {
        throw Exception("Invalid selector");
    }
}

bool
STOWRSRequest
::operator==(STOWRSRequest const & other) const
{
    return(
        this->_base_url == other._base_url
        && this->_transfer_syntax == other._transfer_syntax
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

bool
STOWRSRequest
::_is_selector_valid(Selector const & selector)
{
    return (
        selector.is_study_present() && !selector.is_series_present()
        && !selector.is_instance_present() && selector.get_frames().empty());
}

void
STOWRSRequest
::request_dicom(
    Value::DataSets const & data_sets, Selector const & selector,
    Representation const & representation, std::string const & transfer_syntax)
{
    this->_representation = representation;

    if(representation == Representation::DICOM)
    {
        this->_media_type = "application/dicom";
    }
    else if(representation == Representation::DICOM_XML)
    {
        this->_media_type = "application/dicom+xml";
        this->_transfer_syntax = transfer_syntax;
    }
    else if(representation == Representation::DICOM_JSON)
    {
        this->_media_type = "application/dicom+json";
        this->_transfer_syntax = transfer_syntax;
    }
    else
    {
        throw Exception("Invalid representation");
    }

    this->_data_sets = data_sets;

    if(!STOWRSRequest::_is_selector_valid(selector))
    {
        throw Exception("Invalid selector");
    }
    this->_selector = selector;

    auto path = this->_base_url.path + selector.get_path(false);
    this->_url = {
        this->_base_url.scheme, this->_base_url.authority, path, "", ""};
}

Value::DataSets const &
STOWRSRequest
::get_data_sets() const
{
    return this->_data_sets;
}

Value::DataSets &
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
::get_transfer_syntax() const
{
    return this->_transfer_syntax;
}

void
STOWRSRequest
::set_transfer_syntax(std::string const & transfer_syntax)
{
    this->_transfer_syntax = transfer_syntax;
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
        auto const boundary = random_boundary();
        std::string body;
        OStringStream stream(body);
        accumulate_parts(
            this->get_data_sets().begin(), this->get_data_sets().end(),
            [](std::shared_ptr<DataSet const> data_set)
            {
                std::string buffer;
                OStringStream stream(buffer);
                odil::Writer::write_file(data_set, stream);
                stream.flush();

                return Message(
                    {
                        {
                            "Content-Type",
                            ItemWithParameters("application/dicom")
                        }
                    },
                    buffer
                );
            },
            stream, boundary);
        stream.flush();

        request.set_body(body);

        request.set_header(
            "Content-Type",
            ItemWithParameters(
                "multipart/related",
                {
                    {"type", "application/dicom"}, {"boundary", boundary}
                }));
    }
    else if(this->_representation == Representation::DICOM_JSON)
    {
        // Copy the dataSets in order to let them unchanged
        Value::DataSets copy;
        for(auto const & data_set: this->_data_sets)
        {
            copy.push_back(std::make_shared<DataSet>(*data_set));
        }

        std::vector<BulkData> bulk_data;
        for(auto & ds: copy)
        {
            STOWRSRequest::_extract_bulk_data(ds, bulk_data);
        }

        Json::Value json;
        json.resize(this->_data_sets.size());
        for(int i=0; i<copy.size(); ++i)
        {
            json[i] = as_json(copy[i]);
        }

        std::vector<Json::Value> const json_vector{{json}};
        auto const boundary = random_boundary();
        std::ostringstream body;

        // Add data sets
        accumulate_parts(
            json_vector.begin(), json_vector.end(),
            [this](Json::Value const & json)
            {
                Json::FastWriter writer;
                return Message(
                    {{
                        "Content-Type",
                        ItemWithParameters(
                            "application/dicom+json",
                            {{"transfer-syntax", this->_transfer_syntax}})
                    }},
                    writer.write(json)
                );
            },
            body, boundary);

        // add then the bulk data
        if(!bulk_data.empty())
        {
            // Remove the last boundary of the message
            auto body_content = body.str();
            body_content = body_content.substr(
                0, body_content.size()-boundary.size()-6);
            body.str(std::string()); // clear the content
            body << body_content;

            accumulate_parts(
                bulk_data.begin(), bulk_data.end(),
                [](BulkData const & bulk_data)
                {
                    return Message(
                        {
                            { "Content-Type", bulk_data.type },
                            { "Content-Location", bulk_data.location }
                        },
                        { bulk_data.data.begin(), bulk_data.data.end() }
                    );
                },
                body, boundary);
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
        // Copy the dataSets in order to let them unchanged
        Value::DataSets copy;
        for(auto const & data_set: this->_data_sets)
        {
            copy.push_back(std::make_shared<DataSet>(*data_set));
        }

        std::vector<BulkData> bulk_data;
        for (auto & ds: copy)
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

        auto const boundary = random_boundary();
        std::ostringstream body;

        // Add the data sets
        accumulate_parts(
            copy.begin(), copy.end(),
            [this](std::shared_ptr<DataSet const> data_set)
            {
                auto const xml = as_xml(data_set);
                std::ostringstream stream;

    #if BOOST_VERSION >= 105600
                typedef boost::property_tree::xml_writer_settings<std::string> SettingsType;
    #else
                typedef boost::property_tree::xml_writer_settings<char> SettingsType;
    #endif

                boost::property_tree::write_xml(stream, xml, SettingsType());

                return Message(
                    {{
                        "Content-Type",
                        ItemWithParameters(
                            "application/dicom+xml",
                            {{"transfer-syntax", this->_transfer_syntax}})
                    }},
                    stream.str()
                );
            },
            body, boundary);

        // add then the bulk data
        if (!bulk_data.empty())
        {
            // Remove the last boundary of the message
            auto body_content = body.str();
            body_content = body_content.substr(
                0, body_content.size()-boundary.size()-6);
            body.str(std::string()); // clear the content
            body << body_content;

            accumulate_parts(
                bulk_data.begin(), bulk_data.end(),
                [](BulkData const & bulk_data)
                {
                    return Message(
                        {
                            { "Content-Type", bulk_data.type },
                            { "Content-Location", bulk_data.location }
                        },
                    { bulk_data.data.begin(), bulk_data.data.end() }
                    );
                },
                body, boundary);
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
::_extract_bulk_data(
    std::shared_ptr<DataSet> data_set, std::vector<BulkData> & bulk_data)
{
    for(auto & it: *data_set)
    {
        auto & tag = it.first;
        auto & element = it.second;
        if(element.is_binary())
        {
            // 1. generate uuid
            boost::uuids::random_generator gen;
            boost::uuids::uuid uuid = gen();
            std::string uuid_string = boost::uuids::to_string(uuid);

            // 2. Get Transfer Syntax from dataSet
            std::string const & transfer_syntax =
                    data_set->get_transfer_syntax().empty()
                        ?odil::registry::ExplicitVRLittleEndian
                        :data_set->get_transfer_syntax();

            // 3. Create a new BulkData
            BulkData data;
            data.data = *element.as_binary().data();
            data.location = uuid_string;
            if(tag == registry::PixelData)
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
            data_set->add(tag, {uuid_string}, VR::UR);
        }
        else if (data_set->is_data_set(tag))
        {
            // Case of sequence with multiple sub-elements
            for(auto & item: element.as_data_set())
            {
                STOWRSRequest::_extract_bulk_data(item, bulk_data);
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
::_restore_data_set(std::shared_ptr<DataSet> data_set, BulkMap & bulk_map)
{
    for(auto & it: *data_set)
    {
        auto & tag = it.first;
        auto & element = it.second;
        if(element.vr == odil::VR::UR)
        {
            auto const bulk_map_it = bulk_map.find(element.as_string()[0]);
            if(bulk_map_it != bulk_map.end())
            {
                std::string const & transfer_syntax =
                    data_set->get_transfer_syntax().empty()
                    ?registry::ExplicitVRLittleEndian
                    :data_set->get_transfer_syntax();
                odil::VRFinder vr_finder;
                auto const vr = vr_finder(tag, data_set, transfer_syntax);

                data_set->add(tag, odil::Value::Binary({bulk_map_it->second}), vr);
            }
            else
            {
                // Do nothing: not a bulk data element
            }
        }
        else if(element.is_data_set())
        {
            for(auto & item: element.as_data_set())
            {
                STOWRSRequest::_restore_data_set(item, bulk_map);
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
