/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _079f344d_090b_445c_9019_bcd2e5fe503e
#define _079f344d_090b_445c_9019_bcd2e5fe503e

#include "odil/webservices/multipart_related.h"

#include <ostream>
#include <sstream>
#include <string>

#include "odil/webservices/ItemWithParameters.h"
#include "odil/webservices/Message.h"

namespace odil
{

namespace webservices
{

template<typename Iterator, typename UnaryFunctor>
void transform_parts(
    Message const & message, Iterator destination, UnaryFunctor functor)
{
    if(!is_multipart_related(message))
    {
        return;
    }

    std::stringstream stream(message.get_header("Content-Type"));
    ItemWithParameters content_type;
    stream >> content_type;

    std::string const & boundary = content_type.name_parameters["boundary"];

    auto const & body = message.get_body();

    auto begin = body.find("--"+boundary+"\r\n");
    while(begin < body.size() && begin != std::string::npos)
    {
        auto end = body.find("\r\n--"+boundary+"\r\n", begin+1);
        if(end == std::string::npos)
        {
            end = body.find("\r\n--"+boundary+"--\r\n", begin+1);
        }

        std::string part;

        if(end != std::string::npos)
        {
            auto const part_content = body.substr(
                begin+boundary.size()+4, end-(begin+boundary.size()+4));

            std::istringstream stream(part_content);
            Message sub_message;
            stream >> sub_message;
            *destination = functor(sub_message);
            ++destination;
        }

        begin = end;
    }
}

template<typename UnaryFunctor>
void for_each_part(Message const & message, UnaryFunctor functor)
{
    if(!is_multipart_related(message))
    {
        return;
    }

    std::stringstream stream(message.get_header("Content-Type"));
    ItemWithParameters content_type;
    stream >> content_type;

    std::string const & boundary = content_type.name_parameters["boundary"];

    auto const & body = message.get_body();

    auto begin = body.find("--"+boundary+"\r\n");
    while(begin < body.size() && begin != std::string::npos)
    {
        auto end = body.find("\r\n--"+boundary+"\r\n", begin+1);
        if(end == std::string::npos)
        {
            end = body.find("\r\n--"+boundary+"--\r\n", begin+1);
        }

        std::string part;
        if(end != std::string::npos)
        {
            auto const part_content = body.substr(
                begin+boundary.size()+4, end-(begin+boundary.size()+4));

            std::istringstream stream(part_content);
            Message sub_message;
            stream >> sub_message;
            functor(sub_message);
        }

        begin = end;
    }
}

template<typename Iterator, typename UnaryFunction>
std::ostream & accumulate_parts(
    Iterator begin, Iterator end, UnaryFunction serialize, std::ostream & stream,
    std::string const & boundary)
{
    for(/* no initialization */; begin != end; ++begin)
    {
        auto const part = serialize(*begin);
        stream << "--" << boundary << "\r\n" << part << "\r\n";
    }

    stream << "--" << boundary << "--" << "\r\n";

    return stream;
}

}

}

#endif // _079f344d_090b_445c_9019_bcd2e5fe503e
