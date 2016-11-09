/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/webservices/HTTPResponse.h"

#include <string>

#include <boost/spirit/include/qi.hpp>

#include "odil/Exception.h"
#include "odil/webservices/Message.h"

namespace odil
{

namespace webservices
{

HTTPResponse
::HTTPResponse(
    std::string const & http_version, unsigned int status,
    std::string const & reason,
    Headers const & headers, std::string const & body)
: Message(headers, body),
  _http_version(http_version), _status(status), _reason(reason)
{
    // Nothing else.
}

HTTPResponse
::~HTTPResponse()
{
    // Nothing to do.
}

std::string const &
HTTPResponse
::get_http_version() const
{
    return this->_http_version;
}

void
HTTPResponse
::set_http_version(std::string const & http_version)
{
    this->_http_version = http_version;
}

unsigned int
HTTPResponse
::get_status() const
{
    return this->_status;
}

void
HTTPResponse
::set_status(unsigned int status)
{
    this->_status = status;
}

std::string const &
HTTPResponse
::get_reason() const
{
    return this->_reason;
}

void
HTTPResponse
::set_reason(std::string const & reason)
{
    this->_reason = reason;
}

std::istream & operator>>(std::istream & stream, HTTPResponse & response)
{
    typedef boost::spirit::istream_iterator Iterator;

    namespace qi = boost::spirit::qi;

    using boost::spirit::qi::as_string;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::digit;
    using boost::spirit::qi::int_;
    using boost::spirit::qi::lit;
    using boost::spirit::qi::string;
    using boost::spirit::qi::omit;

    using boost::spirit::ascii::space;

    qi::rule<Iterator, std::string()> crlf = lit("\r\n");

    qi::rule<Iterator, std::string()> http_version =
        as_string[string("HTTP/") >> digit >> string(".") >> digit];
    qi::rule<Iterator, unsigned int()> status = int_;
    qi::rule<Iterator, std::string()> reason = +~char_("\n\r");

    qi::rule<Iterator, boost::fusion::vector<std::string, unsigned int, std::string>()>
        start_line =
            http_version >> omit[space] >> status >> omit[space] >> reason
            >> omit[crlf];

    // CAUTION: if the stream skips white space, disable it and restore it
    // after parsing.
    bool reset_skipws = false;
    if(stream.flags() & std::ios::skipws)
    {
        stream.unsetf(std::ios::skipws);
        reset_skipws = true;
    }

    Iterator begin(stream);
    Iterator end;

    boost::fusion::vector<std::string, unsigned int, std::string> start_line_value;

    auto const ok = boost::spirit::qi::phrase_parse(
        begin, end,
        start_line, boost::spirit::ascii::space, start_line_value
    );

    if(reset_skipws)
    {
        stream.setf(std::ios::skipws);
    }

    if(!ok)
    {
        throw Exception("Could not parse HTTPResponse");
    }

    // begin is too far and has already eaten the first character of headers
    stream.putback(*begin);

    response.set_http_version(boost::fusion::at_c<0>(start_line_value));
    response.set_status(boost::fusion::at_c<1>(start_line_value));
    response.set_reason(boost::fusion::at_c<2>(start_line_value));

    stream >> static_cast<Message&>(response);
    return stream;
}

std::ostream & operator<<(std::ostream & stream, HTTPResponse const & response)
{
    stream
        << response.get_http_version() << " "
        << response.get_status() << " "
        << response.get_reason() << "\r\n";
    stream << static_cast<Message const &>(response);

    return stream;
}

}

}
