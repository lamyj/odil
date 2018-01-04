/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1c3d6b3c_09a0_4452_9263_aa010ee1d973
#define _1c3d6b3c_09a0_4452_9263_aa010ee1d973

#include <istream>
#include <string>

#include "odil/odil.h"
#include "odil/dul/Object.h"

namespace odil
{

namespace dul
{

/// @brief User Identity Sub-Item Structure (A-ASSOCIATE-AC) (PS 3.7, D.3.3.7.2).
class ODIL_API UserIdentityAC: public Object
{
public:
    /// @brief Item type.
    static uint8_t const type=0x59;

    /// @brief Create an User Identity.
    UserIdentityAC(std::string const & server_response="");

    /// @brief Read an User Identity from a stream.
    UserIdentityAC(std::istream & stream);

    /// @brief Return the server response.
    std::string const & get_server_response() const;

    /// @brief Set the server response.
    void set_server_response(std::string const & value);
};

}

}

#endif // _1c3d6b3c_09a0_4452_9263_aa010ee1d973
