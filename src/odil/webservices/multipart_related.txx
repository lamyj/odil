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

#include <random>
#include <sstream>
#include <string>

#include "odil/Exception.h"
#include "odil/webservices/ItemWithParameters.h"
#include "odil/webservices/Message.h"

namespace odil
{

namespace webservices
{

template<typename Iterator>
void split_parts(Message const & message, Iterator destination)
{
    if(!is_multipart_related(message))
    {
        return;
    }

    std::stringstream stream(message.get_header("Content-Type"));
    ItemWithParameters content_type;
    stream >> content_type;

    std::string const & boundary = content_type.name_parameters["boundary"];

    std::size_t begin = 0;
    while(begin < message.get_body().size() && begin != std::string::npos)
    {
        auto end = message.get_body().find("--"+boundary+"\r\n", begin+1);
        if(end == std::string::npos)
        {
            end = message.get_body().find("--"+boundary+"--\r\n", begin+1);
        }

        std::string part;

        if(end != std::string::npos)
        {
            part = message.get_body().substr(begin, end-begin);
        }

        if(end != std::string::npos)
        {
            std::istringstream stream(part.substr(boundary.size()+4));
            Message sub_message;
            stream >> sub_message;
            *destination = sub_message;
            ++destination;
        }

        begin = end;
    }
}

template<typename Iterator>
Message join_parts(Iterator begin, Iterator end, std::string const & boundary)
{
    auto used_boundary = boundary;
    if(used_boundary.empty())
    {
        static std::random_device generator;
        static std::string const characters =
            "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::uniform_int_distribution<> distribution(0, characters.size()-1);
        while(used_boundary.size()<31)
        {
            used_boundary += characters[distribution(generator)];
        }
    }

    Message result;
    result.set_header(
        "Content-Type", "multipart/related;boundary="+used_boundary);

    std::ostringstream body;
    for(Iterator it=begin; it!=end; ++it)
    {
        body << "--" << used_boundary << "\r\n" << *it;
    }
    body << "--" << used_boundary << "--" << "\r\n";
    result.set_body(body.str());

    return result;
}

}

}

#endif // _079f344d_090b_445c_9019_bcd2e5fe503e
