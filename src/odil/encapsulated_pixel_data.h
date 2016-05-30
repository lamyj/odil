/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _0dfb93b3_b0a6_4309_8172_09147c72c0c7
#define _0dfb93b3_b0a6_4309_8172_09147c72c0c7

#include <functional>
#include <map>
#include <string>

#include <boost/any.hpp>

#include "odil/DataSet.h"
#include "odil/Value.h"

namespace odil
{

namespace encapsulated_pixel_data
{

/**
 * @brief A callable object that encodes non-encapsulated pixel data to one of
 * the encapsulated transfer syntaxes.
 *
 * An encoder takes two parameters: the data set to encode (since the encoding
 * might depend on elements other than Pixel Data), and implementation-dependent
 * parameters (e.g. the quality parameter for lossy JPEG). It returns the 
 * encapsulated form of the Pixel Data.
 */
typedef 
    std::function<
        Value::Binary(DataSet const &, std::map<std::string, boost::any> const &)
    > Encoder;

/**
 * @brief A callable object that decodes encapsulated pixel data to its 
 * non-encapsulated form.
 */
typedef std::function<Value::Binary(DataSet const &)> Decoder;

/// @brief Registry of encoders for encapsulated transfer syntaxes.
extern std::map<std::string, Encoder> encoders;

/// @brief Registry of decoders for encapsulated transfer syntaxes.
extern std::map<std::string, Decoder> decoders;

/**
 * @brief Return the encoded Pixel Data of a non-encapsulated data set in the 
 * specified encapsulated transfer syntax.
 *
 * If no encoder is registered for the transfer syntax, throw an exception.
 */
Value::Binary 
encode(
    DataSet const & data_set, std::string const & transfer_syntax, 
    std::map<std::string, boost::any> const & parameters);

/**
 * @brief Return the decoded Pixel Data of a encapsulated data set in the 
 * specified encapsulated transfer syntax.
 *
 * If no decoder is registered for the transfer syntax, throw an exception.
 */
Value::Binary
decode(DataSet const & data_set, std::string const & transfer_syntax);

}

}

#endif // _0dfb93b3_b0a6_4309_8172_09147c72c0c7
