/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _61eb6ed2_447a_43b5_a6ba_ca7c2a5fb492
#define _61eb6ed2_447a_43b5_a6ba_ca7c2a5fb492

#include <boost/property_tree/ptree.hpp>

#include "dcmtkpp/DataSet.h"

namespace dcmtkpp
{

/// @brief Convert a data set to its XML representation.
boost::property_tree::ptree as_xml(DataSet const & data_set);

/// @brief Create a data set from its XML representation.
DataSet as_dataset(boost::property_tree::ptree const & xml);

} // namespace dcmtkpp

#endif // _61eb6ed2_447a_43b5_a6ba_ca7c2a5fb492
