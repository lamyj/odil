/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/uid.h"

#include <string>

#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/random_device.hpp>

#include "dcmtkpp/Exception.h"

#define DCMTKPP_STRINGIFY_HELPER(s) #s
#define DCMTKPP_STRINGIFY(s) DCMTKPP_STRINGIFY_HELPER(s)

namespace dcmtkpp
{

#ifdef DCMTKPP_MAJOR_VERSION
std::string const implementation_class_uid=uid_prefix+"0." DCMTKPP_STRINGIFY(DCMTKPP_MAJOR_VERSION);
std::string const implementation_version_name="DCMTK++ " DCMTKPP_STRINGIFY(DCMTKPP_MAJOR_VERSION);
#else
#error DCMTKPP_MAJOR_VERSION must be defined
#endif

std::string generate_uid()
{
    boost::random::random_device generator;
    boost::random::uniform_int_distribution<> non_zero(1, 9);
    boost::random::uniform_int_distribution<> digits(0, 9);

    std::string result = uid_prefix + "." + std::to_string(non_zero(generator));
    while(result.size()<64)
    {
        result += std::to_string(digits(generator));
    }
    return result;
}

}
