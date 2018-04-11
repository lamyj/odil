/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/webservices/WADORSRequest.h"

#include <string>
#include <tuple>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>

#include "odil/Exception.h"
#include "odil/registry.h"
#include "odil/StringStream.h"
#include "odil/webservices/HTTPRequest.h"
#include "odil/webservices/ItemWithParameters.h"
#include "odil/webservices/URL.h"
#include "odil/webservices/Utils.h"

namespace odil
{

namespace webservices
{

WADORSRequest
::WADORSRequest(
    URL const & base_url,
    std::string const & transfer_syntax, std::string const & character_set,
    bool include_media_type_in_query, bool include_character_set_in_query)
: _base_url(base_url),
  _transfer_syntax(transfer_syntax), _character_set(character_set),
  _include_media_type_in_query(include_media_type_in_query),
  _include_character_set_in_query(include_character_set_in_query),
  _url(), _media_type(), _type(Type::None)
{
    // Nothing else
}

WADORSRequest
::WADORSRequest(HTTPRequest const & request)
{
    // Build URL from target and "Host" header
    this->_url = URL::parse(request.get_target());
    if(request.has_header("Host"))
    {
        this->_url.authority = request.get_header("Host");
    }

    // Find the media type.
    auto const header_accept = as<ItemWithParameters>(
        request.get_header("Accept"));
    if(header_accept.name == "multipart/related")
    {
        this->_media_type = header_accept.name_parameters.at("type");
    }
    else
    {
        this->_media_type = header_accept.name;
    }

    // Parse the query string, look for "accept" and "charset" fields
    auto const query = this->_url.parse_query();
    std::string query_accept;
    std::string query_charset;
    std::for_each(
        query.begin(), query.end(),
        [&](std::pair<std::string, std::string> const & item)
        {
            if(item.first == "accept")
            {
                query_accept = item.second;
            }
            if(item.first == "charset")
            {
                query_charset = item.second;
            }
        });

    // PS 3.18, 6.1.1.8 and 6.1.1.8.4
    this->_transfer_syntax = registry::ExplicitVRLittleEndian;
    if(!query_accept.empty())
    {
        this->_include_media_type_in_query = true;
        auto const item = as<ItemWithParameters>(query_accept);
        auto const it = item.name_parameters.find("transfer-syntax");
        if(it != item.name_parameters.end())
        {
            this->_transfer_syntax = it->second;
        }
    }
    else
    {
        this->_include_media_type_in_query = false;
    }

    auto const transfer_syntax_it = header_accept.name_parameters.find(
        "transfer-syntax");
    if(transfer_syntax_it != header_accept.name_parameters.end())
    {
        this->_transfer_syntax = transfer_syntax_it->second;
    }

    this->_character_set = "UTF-8";
    if(request.has_header("AcceptCharset"))
    {
        this->_character_set = request.get_header("AcceptCharset");
    }
    if(!query_charset.empty())
    {
        this->_include_character_set_in_query = true;
        this->_character_set = query_charset;
    }
    else
    {
        this->_include_character_set_in_query = false;
    }

    auto const charset_it = header_accept.name_parameters.find("charset");
    if(charset_it != header_accept.name_parameters.end())
    {
        this->_character_set = charset_it->second;
    }

    this->_base_url.scheme = this->_url.scheme;
    this->_base_url.authority = this->_url.authority;
    std::tie(this->_base_url.path, this->_selector) = Selector::from_path(
        this->_url.path);

    if(!WADORSRequest::_is_selector_valid(this->_selector))
    {
        throw Exception("Invalid selector");
    }

    if(!this->_selector.get_study().empty())
    {
        if(this->_media_type == "application/dicom")
        {
            this->_type = Type::DICOM;
            this->_representation = Representation::DICOM;
        }
        else if(this->_media_type == "application/dicom+xml")
        {
            this->_type = Type::DICOM;
            this->_representation = Representation::DICOM_XML;
        }
        else if(this->_media_type == "application/dicom+json")
        {
            this->_type = Type::DICOM;
            this->_representation = Representation::DICOM_JSON;
        }
        else if(this->_media_type == "application/octet-stream")
        {
            // This could be a non-compressed pixel data or a non-pixel
            // bulk data. Since we cannot distinguish, assume the most generic
            // one
            this->_type = Type::BulkData;
        }
        else
        {
            // Specific media type: compressed pixel data
            this->_type = Type::PixelData;
        }
    }
    else
    {
        this->_type = Type::BulkData;
    }
}

bool
WADORSRequest
::operator==(WADORSRequest const & other) const
{
    return (
        this->_base_url == other._base_url
        && this->_transfer_syntax == other._transfer_syntax
        && this->_character_set == other._character_set
        && this->_include_media_type_in_query == other._include_media_type_in_query
        && this->_include_character_set_in_query == other._include_media_type_in_query
        && this->_url == other._url
        && this->_media_type == other._media_type
        && this->_type == other._type
    );
}

bool
WADORSRequest
::operator!=(WADORSRequest const & other) const
{
    return !(*this == other);
}

URL const &
WADORSRequest
::get_base_url() const
{
    return this->_base_url;
}

void
WADORSRequest
::set_base_url(URL const & url)
{
    this->_base_url = url;
}

std::string const &
WADORSRequest
::get_transfer_syntax() const
{
    return this->_transfer_syntax;
}

void
WADORSRequest
::set_transfer_syntax(std::string const & transfer_syntax)
{
    this->_transfer_syntax = transfer_syntax;
}

std::string const &
WADORSRequest
::get_character_set() const
{
    return this->_character_set;
}

void
WADORSRequest
::set_character_set(std::string const & character_set)
{
    this->_character_set = character_set;
}

bool
WADORSRequest
::get_include_media_type_in_query() const
{
    return this->_include_media_type_in_query;
}

void
WADORSRequest
::set_include_media_type_in_query(bool include_media_type_in_query)
{
    this->_include_media_type_in_query = include_media_type_in_query;
}

bool
WADORSRequest
::get_include_character_set_in_query() const
{
    return this->_include_character_set_in_query;
}

void
WADORSRequest
::set_include_character_set_in_query(bool include_charcter_set_in_query)
{
    this->_include_character_set_in_query = include_charcter_set_in_query;
}

Type
WADORSRequest
::get_type() const
{
    return this->_type;
}

odil::webservices::Selector const &
WADORSRequest
::get_selector() const
{
    return this->_selector;
}

bool
WADORSRequest
::_is_selector_valid(Selector const & selector)
{
    return (
        // /studies/1.2
        (
            selector.is_study_present() && !selector.get_study().empty()
            && !selector.is_series_present() && !selector.is_instance_present()
            && selector.get_frames().empty())
        // /studies/1.2/series/3.4
        || (
            selector.is_study_present() && !selector.get_study().empty()
            && selector.is_series_present() && !selector.get_series().empty()
            && !selector.is_instance_present() && selector.get_frames().empty())
        // /studies/1.2/series/3.4/instances/5.6/
        // /studies/1.2/series/3.4/instances/5.6/frames/7,8,9
        || (
            selector.is_study_present() && !selector.get_study().empty()
            && selector.is_series_present() && !selector.get_series().empty()
            && selector.is_instance_present() && !selector.get_instance().empty())
    );
}

URL const &
WADORSRequest
::get_url() const
{
    return this->_url;
}

std::string const &
WADORSRequest
::get_media_type() const
{
    return this->_media_type;
}

Representation const &
WADORSRequest
::get_representation() const
{
    return this->_representation;
}

void
WADORSRequest
::request_dicom(Representation representation, Selector const & selector)
{
    this->_type = Type::DICOM;
    if(!WADORSRequest::_is_selector_valid(selector))
    {
        throw Exception("Invalid selector");
    }
    this->_selector = selector;
    this->_representation = representation;

    // RetrieveFrames may not return DICOM objects, PS 3.18, 6.4.1
    // RetrieveMetaData may do so.
    auto path = this->_base_url.path + selector.get_path(
        representation != Representation::DICOM);
    if(representation != Representation::DICOM)
    {
        path += "/metadata";
    }
    this->_url = {
        this->_base_url.scheme, this->_base_url.authority, path, "", ""};

    if(representation == Representation::DICOM)
    {
        this->_media_type = "application/dicom";
    }
    else if(representation == Representation::DICOM_XML)
    {
        this->_media_type = "application/dicom+xml";
    }
    else if(representation == Representation::DICOM_JSON)
    {
        this->_media_type = "application/dicom+json";
    }
    else
    {
        throw Exception("Unknown accept type");
    }
}

void
WADORSRequest
::request_bulk_data(Selector const & selector)
{
    this->_type = Type::BulkData;
    if(!_is_selector_valid(selector))
    {
        throw Exception("Invalid selector");
    }
    this->_selector = selector;

    auto path = this->_base_url.path + selector.get_path(true);
    this->_url = {
        this->_base_url.scheme, this->_base_url.authority, path, "", ""};
    this->_media_type = "application/octet-stream";
}

void
WADORSRequest
::request_bulk_data(URL const & url)
{
    this->_type = Type::BulkData;

    this->_url = url;
    this->_media_type = "application/octet-stream";
}

void
WADORSRequest
::request_pixel_data(Selector const & selector, std::string const & media_type)
{
    this->_type = Type::PixelData;
    if (!_is_selector_valid(selector))
    {
        throw Exception("Invalid selector");
    }
    this->_selector = selector;

    auto path = this->_base_url.path + selector.get_path(true);
    this->_url = {
        this->_base_url.scheme, this->_base_url.authority, path, "", ""};
    this->_media_type = media_type;
}

HTTPRequest
WADORSRequest
::get_http_request() const
{
    ItemWithParameters accept;
    if(this->_representation == Representation::DICOM_JSON)
    {
        accept.name = this->_media_type;
    }
    else
    {
        accept.name = "multipart/related";
        accept.name_parameters["type"] = this->_media_type;
    }

    if(!this->_transfer_syntax.empty())
    {
        accept.name_parameters["transfer-syntax"] = this->_transfer_syntax;
    }
    if(!this->_character_set.empty())
    {
        accept.name_parameters["charset"] = this->_character_set;
    }

    HTTPRequest::Headers const headers{
        { "Accept", boost::lexical_cast<std::string>(accept) } };

    // TODO: accept and accept-charset in URL query
    return HTTPRequest("GET", this->_url, "HTTP/1.0", headers);
}

}

}
