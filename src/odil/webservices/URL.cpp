/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/webservices/URL.h"

#include <sstream>
#include <string>

#include <boost/regex.hpp>

#include "odil/Exception.h"

namespace odil
{

namespace webservices
{

URL
::operator std::string() const
{
    std::stringstream result;

    if(!this->scheme.empty())
    {
        result << this->scheme << ":";
    }

    if(!this->authority.empty())
    {
        result << "//" << this->authority;
    }

    result << this->path;

    if(!this->query.empty())
    {
        result << "?" << this->query;
    }

    if(!this->fragment.empty())
    {
        result << "#" << this->fragment;
    }

    return result.str();
}

URL
URL
::parse(std::string const & string)
{
    // RFC 3986, Appendix B
    boost::regex const regex(
        "^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?");
    boost::smatch match;
    auto const matched = boost::regex_match(string, match, regex);

    if(!matched)
    {
        throw odil::Exception("Invalid URL");
    }

    URL url;

    if(match[2].matched)
    {
        url.scheme = std::string(match[2].first, match[2].second);
    }
    if(match[4].matched)
    {
        url.authority = std::string(match[4].first, match[4].second);
    }
    if(match[5].matched)
    {
        url.path = std::string(match[5].first, match[5].second);
    }
    if(match[7].matched)
    {
        url.query = std::string(match[7].first, match[7].second);
    }
    if(match[9].matched)
    {
        url.fragment = std::string(match[9].first, match[9].second);
    }

    return url;
}

}

}
