/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d8ae0008_075b_4a28_a241_1c6fb1a6c79b
#define _d8ae0008_075b_4a28_a241_1c6fb1a6c79b

#include <string>

namespace dcmtkpp
{

/// @brief UID prefix of DCMTK++.
std::string const uid_prefix="1.2.826.0.1.3680043.9.5560";

#ifdef DCMTKPP_MAJOR_VERSION
#define DCMTKPP_STRINGIFY_HELPER(s) #s
#define DCMTKPP_STRINGIFY(s) DCMTKPP_STRINGIFY_HELPER(s)
/// @brief Implementation class UID of DCMTK++.
std::string const implementation_class_uid=uid_prefix+"0." DCMTKPP_STRINGIFY(DCMTKPP_MAJOR_VERSION);
#else
#error DCMTKPP_MAJOR_VERSION must be defined
#endif

/// @brief Generate a UID under the UID prefix.
std::string generate_uid();

}

#endif // _d8ae0008_075b_4a28_a241_1c6fb1a6c79b
