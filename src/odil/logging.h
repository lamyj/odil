/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _5382f5e0_e993_4966_9447_542844edb635
#define _5382f5e0_e993_4966_9447_542844edb635

#include <boost/preprocessor/facilities/overload.hpp>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>

#define ODIL_LOG_1(level) \
    log4cpp::Category::getInstance("odil") << log4cpp::Priority::level

#define ODIL_LOG_2(level, sub) \
    log4cpp::Category::getInstance("odil." #sub) << log4cpp::Priority::level

#if !BOOST_PP_VARIADICS_MSVC

#define ODIL_LOG(...) BOOST_PP_OVERLOAD(ODIL_LOG_,__VA_ARGS__)(__VA_ARGS__)

#else


#define ODIL_LOG(...) \
  BOOST_PP_CAT(BOOST_PP_OVERLOAD(ODIL_LOG_,__VA_ARGS__)(__VA_ARGS__),BOOST_PP_EMPTY())

#endif

#endif // _5382f5e0_e993_4966_9447_542844edb635
