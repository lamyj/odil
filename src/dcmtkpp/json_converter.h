/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _6f5dc463_a89a_4f77_a0ed_36dca74b9e59
#define _6f5dc463_a89a_4f77_a0ed_36dca74b9e59

#include <json/json.h>
#include "dcmtkpp/DataSet.h"

namespace dcmtkpp
{

/// @brief Convert a data set to its JSON representation.
Json::Value as_json(DataSet const & data_set);

/// @brief Create a data set from its JSON representation.
DataSet as_dataset(Json::Value const & json);

}

#endif // _6f5dc463_a89a_4f77_a0ed_36dca74b9e59
