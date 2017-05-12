/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/webservices/STOWRSResponse.h"

#include <sstream>

#include <json/json.h>

#include <boost/lexical_cast.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/version.hpp>

#include "odil/DataSet.h"
#include "odil/json_converter.h"
#include "odil/webservices/HTTPResponse.h"
#include "odil/webservices/multipart_related.h"
#include "odil/webservices/Utils.h"
#include "odil/xml_converter.h"

namespace odil
{

namespace webservices
{

STOWRSResponse
::STOWRSResponse()
    :_store_instance_responses(), _representation(odil::webservices::Representation::DICOM_XML),
     _reason(""), _warning(false), _failure_code(0), _media_type("")
{
    // Nothing else.
}


STOWRSResponse
::STOWRSResponse(HTTPResponse const &response)
    :_store_instance_responses(), _representation(odil::webservices::Representation::DICOM_XML),
     _reason(""), _warning(false), _failure_code(0), _media_type("")
{
    if (response.get_status() == 200)
    {
        this->set_reason("OK");
        // query is ok
    }
    else if (response.get_status() == 202)
    {
        this->set_reason("Accepted");
        this->_warning = true;
        // The Service stored some of the instances but warnings or failures exist for the others
    }
    else if (response.get_status() == 400 || response.get_status() == 401 || response.get_status() == 403 ||
             response.get_status() == 409 || response.get_status() == 415 || response.get_status() == 503 )
    {
        // Failure found
        this->set_failure_code(response.get_status());
        this->set_reason(response.get_reason());
        return;
    }
    else
    {
        throw Exception("Invalid status : "+ std::to_string(response.get_status()));
    }

    // Find the media type.
    if(!response.has_header("Content-Type"))
    {
        throw Exception("Cannot parse request: Content-Type header missing");
    }
    auto const & content_type = boost::lexical_cast<ItemWithParameters>(
        response.get_header("Content-Type"));

    if(content_type.name == "application/dicom+xml")
    {
        this->_media_type = content_type.name;
        this->_representation = Representation::DICOM_XML;
    }
    else if (content_type.name == "application/dicom+json")
    {
        this->_media_type = content_type.name;
        this->_representation = Representation::DICOM_JSON;
    }
    else
    {
        throw Exception("Unrecognize response representation");
    }

    if (this->_media_type == "application/dicom+xml")
    {
        std::stringstream stream(response.get_body());
        boost::property_tree::ptree xml;
        boost::property_tree::read_xml(stream, xml);
        this->_store_instance_responses = as_dataset(xml);
    }
    else // if (this->_media_type == "application/dicom+json")
    {
        std::istringstream stream(response.get_body());
        Json::Value array;
        stream >> array;
        if (!array.isArray())
        {
            throw Exception("Body must be an array");
        }
        this->_store_instance_responses  = as_dataset(array);
    }
}


bool
STOWRSResponse
::operator ==(STOWRSResponse const & other) const
{
    return (this->_failure_code == other._failure_code
            && this->_media_type == other._media_type
            && this->_reason == other._reason
            && this->_representation == other._representation
            && this->_warning == other._warning
            && this->_store_instance_responses == other._store_instance_responses);
}

bool
STOWRSResponse
::operator !=(STOWRSResponse const & other) const
{
    return !(*this == other);
}

void
STOWRSResponse
::set_store_instance_responses(DataSet const & responses)
{
    this->_store_instance_responses = responses;
}

DataSet const &
STOWRSResponse
::get_store_instance_reponses() const
{
    return this->_store_instance_responses;
}

std::string const &
STOWRSResponse
::get_media_type() const
{
    return this->_media_type;
}

void
STOWRSResponse
::set_representation(odil::webservices::Representation const &representation)
{
    this->_representation = representation;
    if (representation == odil::webservices::Representation::DICOM_JSON)
    {
        this->_media_type = "application/dicom+json";
    }
    else if (representation == odil::webservices::Representation::DICOM_XML)
    {
        this->_media_type = "application/dicom+xml";
    }
    else
    {
        throw Exception("Invalid representation");
    }
}

odil::webservices::Representation const &
STOWRSResponse
::get_representation() const
{
    return this->_representation;
}

void
STOWRSResponse
::set_warning(bool warn)
{
    this->_warning = warn;
}

bool
STOWRSResponse
::is_status_warning() const
{
    return this->_warning;
}

void
STOWRSResponse
::set_failure_code(unsigned int failure_code)
{
    const std::array<int,6> available_failure_codes = {400, 401, 403, 409, 415, 503};
    if (std::find(available_failure_codes.begin(),
                  available_failure_codes.end(),
                  failure_code) != available_failure_codes.end())
    {
        this->_failure_code = failure_code;
    }
    else
    {
        throw Exception("Unknown reason");
    }
}

unsigned int
STOWRSResponse
::get_failure_code() const
{
    return this->_failure_code;
}

void
STOWRSResponse
::set_reason(std::string reason)
{
    const std::array<std::string,8> available_reasons = {"OK", "Bad Request", "Unauthorized",
                                                         "Forbidden", "Conflict", "Unsupported Media Type",
                                                         "Busy", "Accepted"};
    if (std::find(available_reasons.begin(), available_reasons.end(), reason) != available_reasons.end())
    {
        this->_reason = reason;
    }
    else
    {
        throw Exception("Unknown reason");
    }
}

std::string const &
STOWRSResponse
::get_reason() const
{
    return this->_reason;
}

HTTPResponse
STOWRSResponse
::get_http_response() const
{
    HTTPResponse response;
    response.set_status(this->_failure_code==0?(this->is_status_warning()?202:200):this->_failure_code);
    response.set_reason(this->_reason);

    if(this->_representation == odil::webservices::Representation::DICOM_XML)
    {
        auto const xml = as_xml(this->get_store_instance_reponses());
        std::ostringstream body;
#if BOOST_VERSION >= 105600
        typedef boost::property_tree::xml_writer_settings<std::string> SettingsType;
#else
        typedef boost::property_tree::xml_writer_settings<char> SettingsType;
#endif
        boost::property_tree::write_xml(body, xml, SettingsType());
        response.set_body(body.str());

        response.set_header("Content-Type","application/dicom+xml");
    }
    else if (this->_representation == odil::webservices::Representation::DICOM_JSON)
    {
        Json::Value json;
        json.resize(1);
        json[0] = as_json(this->get_store_instance_reponses());

        Json::FastWriter writer;
        response.set_body(writer.write(json));

        response.set_header("Content-Type","application/dicom+json");
    }
    else
    {
        throw Exception("Unknown representation");
    }
    return response;
}


}


}
