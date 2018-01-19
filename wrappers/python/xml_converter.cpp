/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/python.hpp>
#include <boost/version.hpp>

#include "odil/DataSet.h"
#include "odil/xml_converter.h"

namespace
{

std::string as_xml(odil::DataSet const & data_set, bool pretty_print)
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

void wrap_xml_converter()
{
    using namespace boost::python;

    def("as_xml", &as_xml);
}
