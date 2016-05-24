/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/uid.h"

#include <random>
#include <string>

#include "odil/Exception.h"

#define ODIL_STRINGIFY_HELPER(s) #s
#define ODIL_STRINGIFY(s) ODIL_STRINGIFY_HELPER(s)

namespace odil
{

#ifdef ODIL_MAJOR_VERSION
std::string const implementation_class_uid=uid_prefix+"0." ODIL_STRINGIFY(ODIL_MAJOR_VERSION);
std::string const implementation_version_name="Odil " ODIL_STRINGIFY(ODIL_MAJOR_VERSION);
#else
#error ODIL_MAJOR_VERSION must be defined
#endif

void set_implementation_class_uid(std::string const & implementation_class_uid)
{
    const_cast<std::string&>(odil::implementation_class_uid) = implementation_class_uid;
}


void set_implementation_version_name(std::string const & implementation_version_name)
{
    const_cast<std::string&>(odil::implementation_version_name) = implementation_version_name;
}

std::string generate_uid()
{
    static std::random_device generator;
    std::uniform_int_distribution<> non_zero(1, 9);
    std::uniform_int_distribution<> digits(0, 9);

    std::string result = uid_prefix + "." + std::to_string(non_zero(generator));
    while(result.size()<64)
    {
        result += std::to_string(digits(generator));
    }
    return result;
}

}
