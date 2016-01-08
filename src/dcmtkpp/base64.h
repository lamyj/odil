/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _203e7be8_beaa_4d97_94b2_6a0070f158a1
#define _203e7be8_beaa_4d97_94b2_6a0070f158a1

#include <string>

namespace dcmtkpp
{

namespace base64
{

/// @brief Dictionary of symbols for Base64.
extern std::string const symbols;

/// @brief Mapping of ASCII characters to values of Base64 symbols.
extern std::string const reversed_symbols;

/// @brief Encode a sequence of 8 bits data to Base64.
template<typename TInputIterator, typename TOutputIterator>
void encode(
    TInputIterator begin, TInputIterator end, TOutputIterator destination);

/// @brief Decode a sequence of 8 bits data from Base64.
template<typename TInputIterator, typename TOutputIterator>
void decode(
    TInputIterator begin, TInputIterator end, TOutputIterator destination);

}

}

#include "dcmtkpp/base64.txx"

#endif // _203e7be8_beaa_4d97_94b2_6a0070f158a1
