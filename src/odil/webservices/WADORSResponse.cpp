/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/webservices/WADORSResponse.h"

#include <algorithm>
#include <functional>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/version.hpp>

#include <json/json.h>

#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/json_converter.h"
#include "odil/Reader.h"
#include "odil/webservices/BulkData.h"
#include "odil/webservices/HTTPResponse.h"
#include "odil/webservices/ItemWithParameters.h"
#include "odil/webservices/multipart_related.h"
#include "odil/webservices/Utils.h"
#include "odil/Writer.h"
#include "odil/xml_converter.h"

namespace
{

std::vector<odil::DataSet>
multipart_converter(
    std::function<odil::DataSet(std::string const &)> part_converter,
    std::string const & body)
{
    std::vector<odil::DataSet> data_sets;

    return data_sets;
}

}

namespace odil
{

namespace webservices
{

WADORSResponse
::WADORSResponse()
: _data_sets(), _is_partial(false), _type(odil::webservices::Type::None),
  _representation(odil::webservices::Representation::DICOM), _media_type("")
{
    // Nothing else.
}

WADORSResponse
::WADORSResponse(HTTPResponse const & response)
{
    if(response.get_status() == 200)
    {
        this->_is_partial = false;
    }
    else if(response.get_status() == 206)
    {
        this->_is_partial = true;
    }
    else
    {
        throw Exception(
            "Invalid status: "+std::to_string(response.get_status()));
    }

    // Find media type
    auto const & content_type = boost::lexical_cast<ItemWithParameters>(
        response.get_header("Content-Type"));
    if(content_type.name == "multipart/related")
    {
        auto const it = content_type.name_parameters.find("type");
        if(it == content_type.name_parameters.end())
        {
            std::ostringstream message;
            message << "Missing type in Content-Type header: " << content_type;
            throw Exception(message.str());
        }
        this->_media_type = it->second;
    }
    else
    {
        this->_media_type = content_type.name;
    }

    if(this->_media_type == "application/dicom")
    {
        this->_type = odil::webservices::Type::DICOM;
        this->_representation = odil::webservices::Representation::DICOM;

        std::string transfer_syntax = odil::registry::ExplicitVRLittleEndian;
        auto const transfer_syntax_it = content_type.name_parameters.find(
            "transfer-syntax");
        if(transfer_syntax_it != content_type.name_parameters.end())
        {
            transfer_syntax = transfer_syntax_it->second;
        }

        auto const converter =
            [&transfer_syntax](Message const & part)
            {
                std::stringstream stream(part.get_body());
                Reader reader(stream, transfer_syntax);
                return reader.read_data_set();
            };

        transform_parts(
            response, std::back_inserter(this->get_data_sets()), converter);
    }
    else if(this->_media_type == "application/dicom+xml")
    {
        this->_type = odil::webservices::Type::DICOM;
        this->_representation = odil::webservices::Representation::DICOM_XML;

        auto const converter =
            [](Message const & part)
            {
                std::stringstream stream(part.get_body());
                boost::property_tree::ptree xml;
                boost::property_tree::read_xml(stream, xml);
                return as_dataset(xml);
            };
        transform_parts(
            response, std::back_inserter(this->get_data_sets()), converter);
    }
    else if(this->_media_type == "application/dicom+json")
    {
        this->_type = odil::webservices::Type::DICOM;
        this->_representation = odil::webservices::Representation::DICOM_JSON;

        std::istringstream stream(response.get_body());
        Json::Value array;
        stream >> array;
        if(!array.isArray())
        {
            throw Exception("Body must be an array");
        }

        this->get_data_sets().reserve(array.size());
        std::transform(
            array.begin(), array.end(),
            std::back_inserter(this->get_data_sets()),
            static_cast<DataSet(*)(Json::Value const &)>(as_dataset));
    }
    else if(this->_media_type == "application/octet-stream")
    {
        // This could be a non-compressed pixel data or a non-pixel
        // bulk data. Since we cannot distinguish, assume the most generic
        // one
        this->_type = odil::webservices::Type::BulkData;
        auto const converter =
            [](Message const & part)
            {
                auto const & body = part.get_body();
                return BulkData{
                    {body.begin(), body.end()},
                    part.get_header("Content-Type"),
                    part.get_header("Content-Location")};
            };
        transform_parts(
            response, std::back_inserter(this->get_bulk_data()), converter);
    }
    else
    {
        // Specific media type: compressed pixel data
        this->_type = odil::webservices::Type::PixelData;
        auto const converter =
            [](Message const & part)
            {
                auto const & body = part.get_body();
                return BulkData{
                    {body.begin(), body.end()},
                    part.get_header("Content-Type"),
                    part.get_header("Content-Location")};
            };
        transform_parts(
            response, std::back_inserter(this->get_bulk_data()), converter);
    }
}

bool 
WADORSResponse
::operator==(WADORSResponse const & other) const
{
    return (
        this->_data_sets == other._data_sets
        && this->_is_partial == other._is_partial
        && this->_type == other._type
        && this->_representation == other._representation
        && this->_media_type == other._media_type);
}

bool 
WADORSResponse
::operator!=(WADORSResponse const & other) const
{
    return !(*this == other);
}

std::vector<DataSet> const & 
WADORSResponse
::get_data_sets() const
{
    return this->_data_sets;
}

std::vector<DataSet> & 
WADORSResponse
::get_data_sets()
{
    return this->_data_sets;
}

void 
WADORSResponse
::set_data_sets(std::vector<DataSet> const & data_sets)
{
    this->_data_sets = data_sets;    
}

std::vector<BulkData> const &
WADORSResponse
::get_bulk_data() const
{
    return this->_bulk_data;
}

std::vector<BulkData> &
WADORSResponse
::get_bulk_data()
{
    return this->_bulk_data;
}

void
WADORSResponse
::set_bulk_data(std::vector<BulkData> const & bulk_data)
{
    this->_bulk_data = bulk_data;
}

bool
WADORSResponse
::is_partial() const
{
    return this->_is_partial;
}

void
WADORSResponse
::set_partial(bool partial)
{
    this->_is_partial = partial;
}

odil::webservices::Type
WADORSResponse
::get_type() const
{
    return this->_type;
}

odil::webservices::Representation const &
WADORSResponse
::get_representation() const
{
    return this->_representation;
}

void 
WADORSResponse
::respond_dicom(odil::webservices::Representation representation)
{
    this->_type = odil::webservices::Type::DICOM;
    this->_representation = representation;
}

void 
WADORSResponse
::respond_bulk_data()
{
    this->_type = odil::webservices::Type::BulkData;
}

void 
WADORSResponse
::respond_pixel_data(std::string const & media_type)
{
    this->_type = odil::webservices::Type::PixelData;
    this->_media_type = media_type;
}

HTTPResponse 
WADORSResponse
::get_http_response() const
{
    HTTPResponse response;
    response.set_status(this->_is_partial?206:200);
    response.set_reason(this->_is_partial?"Partial Content":"OK");

    if(this->_type == odil::webservices::Type::DICOM)
    {
        if(this->_representation == odil::webservices::Representation::DICOM)
        {
            // PS 3.18, 6.1.1.8
            auto const default_transfer_syntax =
                odil::registry::ExplicitVRLittleEndian;

            auto const accumulator =
                [&default_transfer_syntax](DataSet const & data_set)
                {
                    std::ostringstream stream(
                        std::ios_base::out | std::ios_base::binary);
                    auto const transfer_syntax =
                        data_set.get_transfer_syntax().empty()
                            ?default_transfer_syntax
                            :data_set.get_transfer_syntax();
                    odil::Writer::write_file(
                        data_set, stream, DataSet(), transfer_syntax);

                    return Message(
                        { {
                            "Content-Type",
                            ItemWithParameters(
                                "application/dicom",
                                {{"transfer-syntax", transfer_syntax}}
                            )} }, // TODO: character-set
                        stream.str()
                    );
                };

            auto const boundary = random_boundary();
            std::ostringstream body;
            accumulate_parts(
                this->get_data_sets().begin(), this->get_data_sets().end(),
                accumulator, body, boundary);
            response.set_body(body.str());

            response.set_header(
                "Content-Type",
                ItemWithParameters(
                    "multipart/related", {
                        {"type", "application/dicom"},
                        {"boundary", boundary}}));
        }
        else if(this->_representation == odil::webservices::Representation::DICOM_XML)
        {
            auto const accumulator =
                [](DataSet const & data_set)
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
                        { { "Content-Type", "application/dicom+xml" } },
                        stream.str()
                    );
                };

            auto const boundary = random_boundary();
            std::ostringstream body;
            accumulate_parts(
                this->get_data_sets().begin(), this->get_data_sets().end(),
                accumulator, body, boundary);
            response.set_body(body.str());

            response.set_header(
                "Content-Type",
                ItemWithParameters(
                    "multipart/related", {
                        {"type", "application/dicom+xml"},
                        {"boundary", boundary}}));
        }
        else if(this->_representation == odil::webservices::Representation::DICOM_JSON)
        {
            Json::Value json;
            json.resize(this->_data_sets.size());
            for(unsigned int i=0; i<this->_data_sets.size(); ++i)
            {
                json[i] = as_json(this->_data_sets[i]);
            }

            Json::FastWriter writer;
            response.set_body(writer.write(json));

            response.set_header("Content-Type", "application/dicom+json");
        }
        else
        {
            throw Exception("Unknown representation");
        }
    }
    else if(this->_type == odil::webservices::Type::BulkData)
    {
        auto const accumulator =
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
        accumulate_parts(
            this->get_bulk_data().begin(), this->get_bulk_data().end(),
            accumulator, body, boundary);
        response.set_body(body.str());

        response.set_header(
            "Content-Type",
            ItemWithParameters(
                "multipart/related", {
                    {"type", "application/octet-stream"},
                    {"boundary", boundary}}));
    }
    else if(this->_type == odil::webservices::Type::PixelData)
    {
        auto const accumulator =
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
        accumulate_parts(
            this->get_bulk_data().begin(), this->get_bulk_data().end(),
            accumulator, body, boundary);
        response.set_body(body.str());

        response.set_header(
            "Content-Type",
            ItemWithParameters(
                "multipart/related", {
                    {"type", this->_media_type},
                    {"boundary", boundary}}));
    }
    else
    {
        throw Exception("Unknown type");
    }

    return response;
}

}

}
