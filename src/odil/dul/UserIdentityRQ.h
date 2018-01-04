/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b935542d_12c9_4c81_963c_32b7996af777
#define _b935542d_12c9_4c81_963c_32b7996af777

#include <cstdint>
#include <istream>
#include <string>

#include "odil/odil.h"
#include "odil/pdu/Object.h"

namespace odil
{

namespace pdu
{

/// @brief User Identity Sub-Item Structure (A-ASSOCIATE-RQ) (PS 3.7, D.3.3.7.1).
class ODIL_API UserIdentityRQ: public Object
{
public:
    /// @brief Item type.
    static uint8_t const type=0x58;

    /// @brief Create an User Identity.
    UserIdentityRQ();

    /// @brief Read an User Identity from a stream.
    UserIdentityRQ(std::istream & stream);

    /// @brief Return the type of the User Identity.
    uint8_t get_type() const;

    /// @brief Set the type of the User Identity.
    void set_type(uint8_t type);

    /// @brief Return whether a positive response is requested.
    bool get_positive_response_requested() const;

    /// @brief Set whether a positive response is requested.
    void set_positive_response_requested(bool value);

    /// @brief Return the primary identity field.
    std::string const & get_primary_field() const;

    /// @brief Set the primary identity field.
    void set_primary_field(std::string const & value);

    /// @brief Return the secondary identity field.
    std::string const & get_secondary_field() const;

    /// @brief Set the secondary identity field.
    void set_secondary_field(std::string const & value);

    void set_username(std::string const & username);

    void set_username_and_passcode(
        std::string const & username, std::string const & passcode);

    void set_kerberos_service_ticket(std::string const & ticket);

    void set_saml_assertion(std::string const & assertion);
};

}

}

#endif // _b935542d_12c9_4c81_963c_32b7996af777
