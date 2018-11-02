/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/webservices/HTTPRequest.h"

#include <string>

#include <boost/spirit/include/qi.hpp>

#include "odil/Exception.h"
#include "odil/webservices/Message.h"
#include "odil/webservices/URL.h"

namespace odil
{

namespace webservices
{

HTTPRequest
::HTTPRequest(
    std::string const & method, URL const & target,
    std::string const & http_version,
    Headers const & headers, std::string const & body)
: Message(headers, body),
  _method(method), _target(target), _http_version(http_version)
{
    // Nothing else.
}

std::string const &
HTTPRequest
::get_method() const
{
    return this->_method;
}

void
HTTPRequest
::set_method(std::string const & method)
{
    this->_method = method;
}

URL const &
HTTPRequest
::get_target() const
{
    return this->_target;
}

void
HTTPRequest
::set_target(URL const & target)
{
    this->_target = target;
}

std::string const &
HTTPRequest
::get_http_version() const
{
    return this->_http_version;
}

void
HTTPRequest
::set_http_version(std::string const & http_version)
{
    this->_http_version = http_version;
}

std::istream & operator>>(std::istream & stream, HTTPRequest & request)
{
    typedef boost::spirit::istream_iterator Iterator;

    namespace qi = boost::spirit::qi;

    using boost::spirit::qi::as_string;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::digit;
    using boost::spirit::qi::lit;
    using boost::spirit::qi::string;
    using boost::spirit::qi::omit;

    using boost::spirit::ascii::space;

    qi::rule<Iterator, std::string()> crlf = -lit("\r") >> lit("\n");

    qi::rule<Iterator, std::string()> method = +~char_(" ");
    qi::rule<Iterator, std::string()> target = +~char_(" ");
    qi::rule<Iterator, std::string()> http_version =
        as_string[string("HTTP/") >> digit >> string(".") >> digit];
    qi::rule<Iterator, boost::fusion::vector<std::string, std::string, std::string>()>
        start_line =
            method >> omit[space] >> target >> omit[space] >> http_version
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

    boost::fusion::vector<std::string, std::string, std::string> start_line_value;

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
        throw Exception("Could not parse HTTPRequest");
    }

    // begin is too far and has already eaten the first character of headers
    stream.putback(*begin);

    request.set_method(boost::fusion::at_c<0>(start_line_value));
    request.set_target(URL::parse(boost::fusion::at_c<1>(start_line_value)));
    request.set_http_version(boost::fusion::at_c<2>(start_line_value));

    stream >> static_cast<Message&>(request);
    return stream;
}

std::ostream & operator<<(std::ostream & stream, HTTPRequest const & request)
{
    stream << request.get_method() << " ";
    stream << request.get_target().path;
    if(!request.get_target().query.empty())
    {
        stream << "?" << request.get_target().query;
    }
    // RFC 7230, 5.1: the target URI excludes the reference's fragment component
    stream << " " << request.get_http_version() << "\r\n";
    stream << static_cast<Message const &>(request);

    return stream;
}

}

}
