/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/webservices/QIDORSResponse.h"

#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/version.hpp>

#include <json/json.h>

#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/json_converter.h"
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

QIDORSResponse
::QIDORSResponse()
    :_data_sets(), _representation(odil::webservices::Representation::DICOM_XML),
     _media_type("")
{
    // Nothing else.
}

QIDORSResponse
::QIDORSResponse(HTTPResponse const & response)
    :_data_sets(), _representation(odil::webservices::Representation::DICOM_XML),
     _media_type("")
{
    // Manage response status
    if(response.get_status() == 200)
    {
        // Query is ok and matching results are returned in the message body
    }
    else if(response.get_status() == 204)
    {
        // No matches found
        return;
    }
    else
    {
        throw Exception(
            "Invalid status: "+std::to_string(response.get_status()));
    }


    // Find the media type.
    if(!response.has_header("Content-Type"))
    {
        throw Exception("Cannot parse request: Accept header missing");
    }
    auto const & content_type = boost::lexical_cast<ItemWithParameters>(
        response.get_header("Content-Type"));

    if(content_type.name == "multipart/related")
    {
        auto const it = content_type.name_parameters.find("type");
        // check if the type is not found
        if(it == content_type.name_parameters.end())
        {
            std::ostringstream message;
            message
                << "Missing type in Content-Type header: "
                << response.get_header("Content-Type");
            throw Exception(message.str());
        }
        // check if type is different from the only available type
        if (it->second != "application/dicom+xml")
        {
            throw Exception("Unrecognize response representation");
        }
        this->_media_type = it->second;
        this->_representation = Representation::DICOM_XML;
    }
    else
    {
        if (content_type.name != "application/dicom+json")
        {
            throw Exception("Unrecognize response representation");
        }
        this->_media_type = content_type.name;
        this->_representation = Representation::DICOM_JSON;
    }

    if (this->_media_type == "application/dicom+xml")
    {
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
    else
    {
        // WARNING if body is empty -> next Exception will be raised
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
}

bool
QIDORSResponse
::operator ==(QIDORSResponse const & other) const
{
    return(
        this->_data_sets == other._data_sets
        && this->_representation == other._representation
        && this->_media_type == other._media_type);
}

bool
QIDORSResponse
::operator !=(QIDORSResponse const & other) const
{
    return !(*this == other);
}

std::vector<DataSet> const &
QIDORSResponse
::get_data_sets() const
{
    return this->_data_sets;
}

std::vector<DataSet> &
QIDORSResponse
::get_data_sets()
{
    return this->_data_sets;
}

void
QIDORSResponse
::set_data_sets(std::vector<DataSet> const & data_sets)
{
    this->_data_sets = data_sets;
}

odil::webservices::Representation const &
QIDORSResponse
::get_representation() const
{
    return this->_representation;
}

void
QIDORSResponse
::set_representation(Representation const & representation)
{
    if (representation == odil::webservices::Representation::DICOM_JSON)
    {
        this->_representation = representation;
        this->_media_type = "application/dicom+json";
    }
    else if (representation == odil::webservices::Representation::DICOM_XML)
    {
        this->_representation = representation;
        this->_media_type = "application/dicom+xml";
    }
    else
    {
        throw Exception("Uknown representation");
    }
}

std::string const &
QIDORSResponse
::get_media_type() const
{
    return this->_media_type;
}

HTTPResponse
QIDORSResponse
::get_http_response() const
{
    HTTPResponse response;
    response.set_status(this->_data_sets.empty()?204:200);
    response.set_reason(this->_data_sets.empty()?"No Content":"OK");

    if(this->_representation == odil::webservices::Representation::DICOM_XML)
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
    return response;
}

}

}
