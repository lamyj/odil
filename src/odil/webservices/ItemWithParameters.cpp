/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/webservices/ItemWithParameters.h"

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

std::istream & operator>>(std::istream & stream, ItemWithParameters & item)
{
    typedef boost::spirit::istream_iterator Iterator;

    namespace qi = boost::spirit::qi;

    using boost::spirit::qi::char_;
    using boost::spirit::qi::omit;

    using boost::spirit::ascii::space;

    typedef std::map<std::string, std::string> Map;
    typedef boost::fusion::vector<std::string, Map, Map> Value;

    qi::rule<Iterator, std::string()> token =
        +char_("\"/!#$%&'*+-.^_`|~0-9a-zA-Z");
    qi::rule<Iterator, std::string()> non_q = token-"q";
    qi::rule<Iterator> separator = omit[-space] >> ";" >> omit[-space];
    qi::rule<Iterator, Map()> name_parameters =
        (non_q >> "=" >> token)%separator;
    qi::rule<Iterator, Map()> extension_parameters =
        (token >> "=" >> token)%separator;

    qi::rule<Iterator, Value()> item_rule =
        token
        >> -(separator >> name_parameters)
        >> -(separator >> extension_parameters);

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

    Value item_value;

    auto const ok = boost::spirit::qi::phrase_parse(
        begin, end, item_rule, boost::spirit::ascii::space, item_value);

    if(reset_skipws)
    {
        stream.setf(std::ios::skipws);
    }

    if(!ok)
    {
        throw Exception("Could not parse Message");
    }

    item.name = boost::fusion::at_c<0>(item_value);
    item.name_parameters = boost::fusion::at_c<1>(item_value);
    item.extension_parameters = boost::fusion::at_c<2>(item_value);

    return stream;
}

std::ostream & operator<<(std::ostream & stream, ItemWithParameters const & item)
{
    stream << item.name;

    for(auto const & it: item.name_parameters)
    {
        stream << ";" << it.first << "=" << it.second;
    }

    auto const weight_iterator = item.extension_parameters.find("q");
    if(weight_iterator != item.extension_parameters.end())
    {
        stream
            << ";"
            << weight_iterator->first << "=" << weight_iterator->second;
    }

    for(auto const & it: item.extension_parameters)
    {
        if(it.first != "q")
        {
            stream << ";" << it.first << "=" << it.second;
        }
    }
    return stream;
}

}

}
