/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _43545543_c8f8_44c4_b3ce_93cf2adfd365
#define _43545543_c8f8_44c4_b3ce_93cf2adfd365

#include <cstdint>
#include <istream>
#include <string>

#include "dcmtkpp/pdu/Object.h"

namespace dcmtkpp
{

namespace pdu
{

/// @brief Implementation Version Name Sub-Item (PS 3.7, D.3.3.2.3 and D.3.3.2.4).
class ImplementationVersionName: public Object
{
public:
    /// @brief Item type.
    static uint8_t const type=0x55;

    /// @brief Create a Implementation Version Name item.
    ImplementationVersionName(std::string const & implementation_version_name);

    /// @brief Read a Implementation Version Name item from a stream.
    ImplementationVersionName(std::istream & stream);

    /// @brief Return the Implementation Version Name.
    std::string get_implementation_version_name() const;

    /// @brief Set the Implementation Version Name.
    void set_implementation_version_name(std::string const & value);
};

}

}

#endif // _43545543_c8f8_44c4_b3ce_93cf2adfd365
