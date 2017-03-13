/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a63ad009_f45b_4e22_b750_ad1b12ba7f13
#define _a63ad009_f45b_4e22_b750_ad1b12ba7f13

#include <cstdint>
#include <string>
#include <vector>

namespace odil
{

namespace webservices
{

/// @brief Bulk data transmitted by web services (WADO-RS, STOW, etc.)
struct BulkData
{
    std::vector<uint8_t> data;
    std::string type;
    std::string location;
};

}

}

#endif // _a63ad009_f45b_4e22_b750_ad1b12ba7f13
