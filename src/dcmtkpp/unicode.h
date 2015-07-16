/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _4a178325_e3d6_4f6f_9a18_ba6a983ee396
#define _4a178325_e3d6_4f6f_9a18_ba6a983ee396

#include <string>
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

/// @brief Convert a string to its UTF-8 representation
std::string as_utf8(
    std::string const & input, Value::Strings const & specific_character_set,
    bool is_pn=false);

}

#endif // _4a178325_e3d6_4f6f_9a18_ba6a983ee396
