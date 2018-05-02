/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/property_tree/xml_parser.hpp>
#include <pybind11/pybind11.h>
#include <boost/version.hpp>

#include "odil/DataSet.h"
#include "odil/StringStream.h"
#include "odil/xml_converter.h"

#include "opaque_types.h"
#include "type_casters.h"

namespace
{

std::string as_xml(std::shared_ptr<odil::DataSet> data_set, bool pretty_print)
{
    auto const xml = odil::as_xml(data_set);
    std::ostringstream stream;

#if BOOST_VERSION >= 105600
    typedef boost::property_tree::xml_writer_settings<std::string> SettingsType;
#else
    typedef boost::property_tree::xml_writer_settings<char> SettingsType;
#endif

    SettingsType settings;
    if(pretty_print)
    {
        settings = SettingsType('\t', 1);
    }
    boost::property_tree::write_xml(stream, xml, settings);
    return stream.str();
}

}

void wrap_xml_converter(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    m.def(
        "as_xml",
        [](std::shared_ptr<odil::DataSet> data_set, bool pretty_print)
        {
            auto const xml = odil::as_xml(data_set);
            std::string data;
            OStringStream stream(data);

#if BOOST_VERSION >= 105600
            typedef boost::property_tree::xml_writer_settings<std::string> SettingsType;
#else
            typedef boost::property_tree::xml_writer_settings<char> SettingsType;
#endif

            SettingsType settings;
            if(pretty_print)
            {
                settings = SettingsType('\t', 1);
            }
            boost::property_tree::write_xml(stream, xml, settings);
            return data;
        });
    m.def(
        "from_xml",
        [](std::string const & xml_string)
        {
            IStringStream stream(&xml_string[0], xml_string.size());
            boost::property_tree::ptree xml;
            boost::property_tree::read_xml(stream, xml);
            return as_dataset(xml);
        }
    );
}
