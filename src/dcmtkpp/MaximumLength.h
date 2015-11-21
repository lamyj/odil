/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b2091b0b_1a6e_435c_b927_e5c54aff89c5
#define _b2091b0b_1a6e_435c_b927_e5c54aff89c5

#include <cstdint>
#include <istream>

#include "dcmtkpp/ProtocolDataUnitObjectBase.h"

namespace dcmtkpp
{

/// @brief Maximum Length Sub-Item Structure (PS 3.8, D.1).
class MaximumLength: public ProtocolDataUnitObjectBase
{
public:
    /// @brief Create a Maximum Length item.
    MaximumLength(uint32_t maximum_length=0);

    /// @brief Read a Maximum Length item from a stream.
    MaximumLength(std::istream & stream);

    /// @brief Return the maximum length.
    uint32_t get_maximum_length() const;

    /// @brief Set the maximum length.
    void set_maximum_length(uint32_t value);
};

}

#endif // _b2091b0b_1a6e_435c_b927_e5c54aff89c5
