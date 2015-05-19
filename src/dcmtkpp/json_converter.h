/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _6f5dc463_a89a_4f77_a0ed_36dca74b9e59
#define _6f5dc463_a89a_4f77_a0ed_36dca74b9e59

#include <jsoncpp/json/json.h>
#include "dcmtkpp/DataSet.h"

namespace dcmtkpp
{

Json::Value to_json(DataSet const & data_set);

}

#endif // _6f5dc463_a89a_4f77_a0ed_36dca74b9e59
