/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _66a57cbb_d910_4156_af54_611e301622df
#define _66a57cbb_d910_4156_af54_611e301622df

#include <map>
#include <string>

#include <boost/any.hpp>

#include "odil/DataSet.h"
#include "odil/Value.h"

namespace odil
{

namespace rle_lossless
{

/**
 * @brief Encode the Pixel Data to RLE Lossless (1.2.840.10008.1.2.5).
 *
 * See PS 3.5 A.4.2 for details. No parameter is defined for this encoder.
 * This encoder is automatically registered.
 */
Value::Binary
encode(DataSet const & data_set, std::map<std::string, boost::any> const &);

/**
 * @brief Decode the Pixel Data from RLE Lossless (1.2.840.10008.1.2.5).
 * 
 * This decoder is automatically registered.
 */
Value::Binary decode(DataSet const & data_set);

}

}

#endif // _66a57cbb_d910_4156_af54_611e301622df
