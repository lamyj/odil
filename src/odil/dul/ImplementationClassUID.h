/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _6b085e0c_afd5_4ed7_ab4d_6bdb9b28ca67
#define _6b085e0c_afd5_4ed7_ab4d_6bdb9b28ca67

#include <cstdint>
#include <istream>
#include <string>

#include "odil/odil.h"
#include "odil/dul/Object.h"

namespace odil
{

namespace dul
{

/// @brief Implementation Class UID Sub-Item (PS 3.7, D.3.3.2.1 and D.3.3.2.2).
class ODIL_API ImplementationClassUID: public Object
{
public:
    /// @brief Item type.
    static uint8_t const type=0x52;

    /// @brief Create a Implementation Class UID item.
    ImplementationClassUID(std::string const & implementation_class_uid);

    /// @brief Read a Implementation Class UID item from a stream.
    ImplementationClassUID(std::istream & stream);

    /// @brief Return the Implementation Class UID.
    std::string get_implementation_class_uid() const;

    /// @brief Set the Implementation Class UID.
    void set_implementation_class_uid(std::string const & value);
};

}

}

#endif // _6b085e0c_afd5_4ed7_ab4d_6bdb9b28ca67
