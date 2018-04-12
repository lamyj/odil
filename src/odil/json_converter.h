/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _6f5dc463_a89a_4f77_a0ed_36dca74b9e59
#define _6f5dc463_a89a_4f77_a0ed_36dca74b9e59

#include <json/json.h>

#include "odil/DataSet.h"
#include "odil/odil.h"
#include "odil/Value.h"

namespace odil
{

/// @brief Convert a data set to its JSON representation.
ODIL_API Json::Value as_json(
    std::shared_ptr<DataSet const> data_set,
    Value::Strings const & specific_character_set={});

/// @brief Create a data set from its JSON representation.
ODIL_API std::shared_ptr<DataSet> as_dataset(Json::Value const & json);

}

#endif // _6f5dc463_a89a_4f77_a0ed_36dca74b9e59
