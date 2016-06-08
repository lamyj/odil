/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <iostream>

#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Priority.hh>

namespace odil
{

namespace logging
{

bool configure()
{
    auto * appender = new log4cpp::OstreamAppender("console", &std::cout);
    appender->setLayout(new log4cpp::BasicLayout());

    auto & root = log4cpp::Category::getRoot();
    root.setPriority(log4cpp::Priority::WARN);
    root.addAppender(appender);

    return true;
}

static bool const configured = configure();

}

}
