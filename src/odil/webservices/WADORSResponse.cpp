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
#include "odil/StringStream.h"
#include "odil/webservices/BulkData.h"
#include "odil/webservices/HTTPResponse.h"
#include "odil/webservices/ItemWithParameters.h"
#include "odil/webservices/multipart_related.h"
#include "odil/webservices/Utils.h"
#include "odil/Writer.h"
#include "odil/xml_converter.h"

namespace odil
{

namespace webservices
{

WADORSResponse
::WADORSResponse()
: _data_sets(), _is_partial(false), _type(Type::None),
  _representation(Representation::DICOM), _media_type("")
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
    auto const & content_type = as<ItemWithParameters>(
        response.get_header("Content-Type"));
    if(content_type.name == "multipart/related")
    {
        this->_media_type = content_type.name_parameters.at("type");
    }
    else
    {
        this->_media_type = content_type.name;
    }

    if(this->_media_type == "application/dicom")
    {
        this->_type = Type::DICOM;
        this->_representation = Representation::DICOM;

        std::string transfer_syntax = registry::ExplicitVRLittleEndian;
        auto const transfer_syntax_it = content_type.name_parameters.find(
            "transfer-syntax");
        if(transfer_syntax_it != content_type.name_parameters.end())
        {
            transfer_syntax = transfer_syntax_it->second;
        }

        transform_parts(
            response, std::back_inserter(this->get_data_sets()),
            [](Message const & part)
            {
                IStringStream stream{
                    &part.get_body()[0], part.get_body().size()};
                auto const data_set_and_header = Reader::read_file(stream);
                return data_set_and_header.second;
            });
    }
    else if(this->_media_type == "application/dicom+xml")
    {
        this->_type = Type::DICOM;
        this->_representation = Representation::DICOM_XML;

        transform_parts(
            response, std::back_inserter(this->get_data_sets()),
            [](Message const & part)
            {
                IStringStream stream{
                    &part.get_body()[0], part.get_body().size()};
                boost::property_tree::ptree xml;
                boost::property_tree::read_xml(stream, xml);
                return as_dataset(xml);
            });
    }
    else if(this->_media_type == "application/dicom+json")
    {
        this->_type = Type::DICOM;
        this->_representation = Representation::DICOM_JSON;

        IStringStream stream{
            &response.get_body()[0], response.get_body().size()};
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
            static_cast<std::shared_ptr<DataSet>(*)(Json::Value const &)>(as_dataset));
    }
    else if(this->_media_type == "application/octet-stream")
    {
        // This could be a non-compressed pixel data or a non-pixel
        // bulk data. Since we cannot distinguish, assume the most generic
        // one
        this->_type = Type::BulkData;

        transform_parts(
            response, std::back_inserter(this->get_bulk_data()),
            [](Message const & part)
            {
                auto const & body = part.get_body();
                return BulkData{
                    {body.begin(), body.end()},
                    part.get_header("Content-Type"),
                    part.get_header("Content-Location")};
            });
    }
    else
    {
        // Specific media type: compressed pixel data
        this->_type = Type::PixelData;

        transform_parts(
            response, std::back_inserter(this->get_bulk_data()),
            [](Message const & part)
            {
                auto const & body = part.get_body();
                return BulkData{
                    {body.begin(), body.end()},
                    part.get_header("Content-Type"),
                    part.get_header("Content-Location")};
            });
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

Value::DataSets const &
WADORSResponse
::get_data_sets() const
{
    return this->_data_sets;
}

Value::DataSets &
WADORSResponse
::get_data_sets()
{
    return this->_data_sets;
}

void 
WADORSResponse
::set_data_sets(Value::DataSets const & data_sets)
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

Type
WADORSResponse
::get_type() const
{
    return this->_type;
}

Representation const &
WADORSResponse
::get_representation() const
{
    return this->_representation;
}

void 
WADORSResponse
::respond_dicom(Representation representation)
{
    this->_type = Type::DICOM;
    this->_representation = representation;
}

void 
WADORSResponse
::respond_bulk_data()
{
    this->_type = Type::BulkData;
}

void 
WADORSResponse
::respond_pixel_data(std::string const & media_type)
{
    this->_type = Type::PixelData;
    this->_media_type = media_type;
}

template<typename Iterator, typename Accumulator>
void
create_multipart(
    Iterator begin, Iterator end, Accumulator accumulator,
    std::string const & media_type, HTTPResponse & response)
{
    auto const boundary = random_boundary();
    std::string body;
    OStringStream stream(body);
    accumulate_parts(begin, end, accumulator, stream, boundary);
    stream.flush();
    response.set_body(body);

    response.set_header(
        "Content-Type",
        ItemWithParameters(
            "multipart/related", {{"type", media_type}, {"boundary", boundary}}
    ));
}

HTTPResponse 
WADORSResponse
::get_http_response() const
{
    HTTPResponse response;
    response.set_status(this->_is_partial?206:200);
    response.set_reason(this->_is_partial?"Partial Content":"OK");

    if(this->_type == Type::DICOM)
    {
        if(this->_representation == Representation::DICOM)
        {
            create_multipart(
                this->_data_sets.begin(), this->_data_sets.end(),
                [](std::shared_ptr<DataSet const> data_set)
                {
                    std::string part_body;
                    OStringStream stream(part_body);
                    auto const transfer_syntax =
                        data_set->get_transfer_syntax().empty()
                            // PS 3.18, 6.1.1.8
                            ?registry::ExplicitVRLittleEndian
                            :data_set->get_transfer_syntax();
                    Writer::write_file(
                        data_set, stream, std::make_shared<DataSet>(),
                        transfer_syntax);
                    stream.flush();

                    return Message(
                        { {
                            "Content-Type",
                            ItemWithParameters(
                                "application/dicom",
                                { {"transfer-syntax", transfer_syntax} }
                            )} }, // TODO: character-set
                        part_body
                    );
                },
                "application/dicom", response);
        }
        else if(this->_representation == Representation::DICOM_XML)
        {
            create_multipart(
                this->get_data_sets().begin(), this->get_data_sets().end(),
                [](std::shared_ptr<DataSet const> data_set)
                {
                    auto const xml = as_xml(data_set);
                    std::string part_body;
                    OStringStream stream(part_body);

#if BOOST_VERSION >= 105600
                    typedef boost::property_tree::xml_writer_settings<std::string> SettingsType;
#else
                    typedef boost::property_tree::xml_writer_settings<char> SettingsType;
#endif

                    boost::property_tree::write_xml(stream, xml, SettingsType());
                    stream.flush();

                    return Message(
                        { { "Content-Type", "application/dicom+xml" } },
                        part_body
                    );
                },
                "application/dicom+xml", response);
        }
        else if(this->_representation == Representation::DICOM_JSON)
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
    else if(this->_type == Type::BulkData)
    {
        create_multipart(
            this->get_bulk_data().begin(), this->get_bulk_data().end(),
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
            "application/octet-stream", response);
    }
    else if(this->_type == Type::PixelData)
    {
        create_multipart(
            this->get_bulk_data().begin(), this->get_bulk_data().end(),
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
            this->_media_type, response);
    }
    else
    {
        throw Exception("Unknown type");
    }

    return response;
}

}

}
