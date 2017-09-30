/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/webservices/multipart_related.h"

#include <algorithm>
#include <ctype.h>
#include <ostream>
#include <sstream>
#include <random>
#include <string>

#include "odil/webservices/ItemWithParameters.h"
#include "odil/webservices/Message.h"

namespace odil
{

namespace webservices
{

bool is_multipart_related(Message const & message)
{
    if(!message.has_header("Content-Type"))
    {
        return false;
    }

    std::stringstream stream(message.get_header("Content-Type"));
    ItemWithParameters content_type;
    stream >> content_type;

    std::string name_lower(content_type.name.size(), ' ');
    std::transform(
        content_type.name.begin(), content_type.name.end(), name_lower.begin(),
        ::tolower);

    return name_lower == "multipart/related";
}

std::size_t count_parts(Message const & message)
{
    if(!is_multipart_related(message))
    {
        return 0;
    }

    std::stringstream stream(message.get_header("Content-Type"));
    ItemWithParameters content_type;
    stream >> content_type;

    std::string const & boundary =
        "--"+content_type.name_parameters["boundary"]+"\r\n";

    std::size_t count = 0;
    std::size_t begin = 0;
    while(begin != std::string::npos)
    {
        auto const end = message.get_body().find(boundary, begin);
        if(end != std::string::npos)
        {
            ++count;
            begin = end+boundary.size();
        }
        else
        {
            begin = end;
        }
    }

    return count;
}

std::string random_boundary()
{
    static std::random_device generator;
    static std::string const characters =
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::uniform_int_distribution<> distribution(0, characters.size()-1);

    std::string boundary;
    while(boundary.size()<31)
    {
        boundary += characters[distribution(generator)];
    }
    return boundary;
}

}

}
