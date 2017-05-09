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
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>

#include "odil/DataSet.h"
#include "odil/Reader.h"
#include "odil/Writer.h"
#include "odil/webservices/ItemWithParameters.h"
#include "odil/webservices/multipart_related.h"
#include "odil/webservices/Selector.h"
#include "odil/webservices/Utils.h"
#include "odil/webservices/URL.h"

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
        // TODO : complete me when understanding XML request body
    }
    else if (this->_media_type == "application/dicom+json")
    {
        this->_representation = Representation::DICOM_JSON;
        // TODO : complete me when understanding JSON request body
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

    Selector selector(study);

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
::request_dicom(std::vector<DataSet> const & data_sets, Selector const & selector)
{
    this->_representation = Representation::DICOM;
    this->_data_sets = data_sets;
    this->_media_type = "application/dicom";
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
    }
    else if(this->_representation == Representation::DICOM_XML)
    {
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


}

}
