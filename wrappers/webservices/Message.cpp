/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include "odil/webservices/Message.h"

namespace
{

boost::python::dict
convert_headers(odil::webservices::Message::Headers const & headers)
{
    using namespace boost::python;

    dict result;
    for(auto const & item: headers)
    {
        result[item.first] = item.second;
    }

    return result;
}

odil::webservices::Message::Headers
convert_headers(boost::python::dict const & headers)
{
    using namespace boost::python;
    using namespace odil::webservices;

    Message::Headers result;

    auto items = headers.items();
    for(int item_index=0; item_index<len(items); ++item_index)
    {
        auto item = items[item_index];

        auto key_python = item[0];
        std::string const key_cpp = extract<std::string>(key_python);

        auto value_python = item[1];
        std::string const value_cpp = extract<std::string>(value_python);

        result.insert(std::make_pair(key_cpp, value_cpp));
    }

    return result;
}

boost::shared_ptr<odil::webservices::Message>
constructor(
    boost::python::dict const & headers=boost::python::dict(),
    std::string const & body=std::string())
{
    using namespace odil::webservices;

    // Old versions of Boost.Python (Debian 7, Ubuntu 12.04) do not like
    // std::shared_ptr
    auto message = new Message(convert_headers(headers), body);
    return boost::shared_ptr<Message>(message);
}

boost::python::dict get_headers(odil::webservices::Message const & message)
{
    return convert_headers(message.get_headers());
}

void set_headers(
    odil::webservices::Message & message, boost::python::dict const & headers)
{
    message.set_headers(convert_headers(headers));
}

}

void wrap_webservices_Message()
{
    using namespace boost::python;
    using namespace odil::webservices;

    scope message_scope = class_<Message>("Message", no_init)
        .def(
            "__init__",
            make_constructor(
                constructor, default_call_policies(),
                (arg("headers")=dict(), arg("body")=std::string())))
        .def("get_headers", &get_headers)
        .def("set_headers", &set_headers)
        .def("has_header", &Message::has_header)
        .def(
            "get_header", &Message::get_header,
            return_value_policy<copy_const_reference>())
        .def("set_header", &Message::set_header)
        .def(
            "get_body", &Message::get_body,
            return_value_policy<copy_const_reference>())
        .def("set_body", &Message::set_body)
    ;
}
