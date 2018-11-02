/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/webservices/URL.h"

#include <string>
#include <utility>
#include <vector>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>

#include "odil/Exception.h"
#include "odil/StringStream.h"

namespace odil
{

namespace webservices
{

bool
URL
::operator==(URL const & other) const
{
    return (
        this->scheme == other.scheme
        && this->authority == other.authority
        && this->path == other.path
        && this->query == other.query
        && this->fragment == other.fragment);
}

bool
URL
::operator!=(URL const & other) const
{
    return !(*this == other);
}

URL
::operator std::string() const
{
    std::string result;
    OStringStream stream(result);

    if(!this->scheme.empty())
    {
        stream << this->scheme << ":";
    }

    if(!this->authority.empty())
    {
        stream << "//" << this->authority;
    }

    stream << this->path;

    if(!this->query.empty())
    {
        stream << "?" << this->query;
    }

    if(!this->fragment.empty())
    {
        stream << "#" << this->fragment;
    }

    return result;
}

std::vector<std::pair<std::string, std::string>>
URL
::parse_query(std::string const & separator) const
{
    namespace qi = boost::spirit::qi;
    typedef std::string::const_iterator Iterator;
    typedef std::vector<std::pair<std::string, std::string>> PairContainer;

    qi::rule<Iterator, std::string()> name = +~qi::char_("="+separator);
    qi::rule<Iterator, std::string()> value = +~qi::char_(separator);
    qi::rule<Iterator, PairContainer()> retrieve_key_val =
            (name  >> qi::omit["="] >> value)%separator;

    auto iterator = this->query.begin();
    PairContainer pair_container;
    auto const parsed = qi::phrase_parse(
        iterator, this->query.end(), retrieve_key_val, qi::ascii::space,
        pair_container);
    if(!this->query.empty() && (!parsed || iterator != this->query.end()))
    {
        throw Exception("Could not parse query string");
    }

    return pair_container;
}

URL
URL
::parse(std::string const & string)
{
    namespace qi = boost::spirit::qi;
    typedef std::string::const_iterator Iterator;
    
    qi::rule<Iterator, std::string()> scheme = +~qi::char_(":/?#");
    qi::rule<Iterator, std::string()> authority = +~qi::char_("/?#");
    qi::rule<Iterator, std::string()> path = *~qi::char_("?#");
    qi::rule<Iterator, std::string()> query = +~qi::char_("#");
    qi::rule<Iterator, std::string()> fragment = +qi::char_;
    
    // RFC 3986, Appendix B 
    boost::fusion::vector<
        std::string, std::string, std::string, std::string, std::string> url_value;

    auto const ok = qi::parse(
        string.begin(), string.end(), 
            -(scheme >> ":") >> -("//" >> authority)
            >> path >> -( "?" >> query) >> -( "#" >> fragment), 
        url_value);

    if(!ok)
    {
        throw Exception("Could not parse URL");
    }

    return URL{
        boost::fusion::at_c<0>(url_value),
        boost::fusion::at_c<1>(url_value),
        boost::fusion::at_c<2>(url_value),
        boost::fusion::at_c<3>(url_value),
        boost::fusion::at_c<4>(url_value)
    };
}

}

}
