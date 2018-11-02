/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/webservices/Message.h"

#include <algorithm>
#include <ctype.h>
#include <istream>
#include <map>
#include <ostream>
#include <string>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include "odil/Exception.h"

namespace odil
{

namespace webservices
{

Message
::Message(Headers const & headers, std::string const & body)
: _headers(headers), _body(body)
{
    // Nothing else.
}

Message::Headers const &
Message
::get_headers() const
{
    return this->_headers;
}

void
Message
::set_headers(Headers const & headers)
{
    this->_headers = headers;
}

bool
Message
::has_header(std::string const & name) const
{
    auto const iterator = this->_find_header(name);
    return (iterator != this->_headers.end());
}

std::string const &
Message
::get_header(std::string const & name) const
{
    auto const iterator = this->_find_header(name);
    if(iterator == this->_headers.end())
    {
        throw Exception("No such header: "+name);
    }

    return iterator->second;
}

void
Message
::set_header(std::string const & name, std::string const & value)
{
    this->_headers[name] = value;
}

std::string const &
Message
::get_body() const
{
    return this->_body;
}

void
Message
::set_body(std::string const & body)
{
    this->_body = body;
}

Message::Headers::const_iterator
Message
::_find_header(std::string const & name) const
{
    auto const iterator = std::find_if(
        this->_headers.begin(), this->_headers.end(),
        [&name](Headers::value_type const & x)
        {
            std::string name_lower(name.size(), ' ');
            std::transform(name.begin(), name.end(), name_lower.begin(), ::tolower);

            std::string x_lower(x.first.size(), ' ');
            std::transform(x.first.begin(), x.first.end(), x_lower.begin(), ::tolower);

            return (name_lower == x_lower);
        }
    );

    return iterator;
}

std::istream & operator>>(std::istream & stream, Message & message)
{
    typedef boost::spirit::istream_iterator Iterator;

    namespace qi = boost::spirit::qi;

    using boost::spirit::qi::char_;
    using boost::spirit::qi::lit;
    using boost::spirit::qi::string;
    using boost::spirit::qi::omit;

    using boost::spirit::ascii::space;

    qi::rule<Iterator, std::string()> token = +char_("!#$%&'*+-.^_`|~0-9a-zA-Z");
    qi::rule<Iterator, std::string()> crlf = -lit("\r") >> lit("\n");

    qi::rule<Iterator, std::string()> field_name = token;
    qi::rule<Iterator, std::string()> field_value = +~char_("\r\n");
    qi::rule<Iterator, Message::Headers()> headers =
        *(field_name >> omit[-space >> ":" >> -space] >> field_value >> omit[crlf]);

    qi::rule<Iterator, std::string()> body = +char_;

    qi::rule<Iterator, boost::fusion::vector<Message::Headers, std::string>()>
        message_rule = headers >> -(omit[crlf] >> body);

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

    boost::fusion::vector<Message::Headers, std::string> message_value;

    auto const ok = boost::spirit::qi::phrase_parse(
        begin, end,
        message_rule, boost::spirit::ascii::space, message_value
    );

    if(reset_skipws)
    {
        stream.setf(std::ios::skipws);
    }

    if(!ok)
    {
        throw Exception("Could not parse Message");
    }
    else if(begin != end)
    {
        throw Exception("Incomplete parsing");
    }

    message.set_headers(boost::fusion::at_c<0>(message_value));
    message.set_body(boost::fusion::at_c<1>(message_value));

    return stream;
}

std::ostream & operator<<(std::ostream & stream, Message const & message)
{
    for(auto const & header: message.get_headers())
    {
        stream << header.first << ": " << header.second << "\r\n";
    }
    stream << "\r\n";
    stream << message.get_body();

    return stream;
}

}

}
