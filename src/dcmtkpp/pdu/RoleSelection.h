/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _8a990556_f9c3_49f3_bb84_6e604ec9b8f4
#define _8a990556_f9c3_49f3_bb84_6e604ec9b8f4

#include <cstdint>
#include <istream>
#include <string>

#include "odil/pdu/Object.h"

namespace odil
{

namespace pdu
{

/// @brief SCU/SCP Role Selection Sub-Item (PS 3.7, D.3.3.4.1 and D.3.3.4.2).
class RoleSelection: public Object
{
public:
    /// @brief Item type.
    static uint8_t const type=0x54;

    /// @brief Create a Role Selection Sub-Item.
    RoleSelection(
        std::string const & sop_class_uid="",
        bool scu_role_support=false, bool scp_role_support=false);

    /// @brief Read a Role Selection Sub-Item from a stream.
    RoleSelection(std::istream & stream);

    /**
     * @brief Return the SOP class uid identifying the abstract syntax,
     * defaults to "".
     */
    std::string const & get_sop_class_uid() const;

    /// @brief Set the SOP class uid identifying the abstract syntax.
    void set_sop_class_uid(std::string const & value);

    /// @brief Return whether the SCU role is supported, defaults to false.
    bool get_scu_role_support() const;

    /// @brief Set whether the SCP role is supported.
    void set_scu_role_support(bool value);

    /// @brief Return whether the SCP role is supported, defaults to false.
    bool get_scp_role_support() const;

    /// @brief Set whether the SCP role is supported.
    void set_scp_role_support(bool value);
};

}

}

#endif // _8a990556_f9c3_49f3_bb84_6e604ec9b8f4
