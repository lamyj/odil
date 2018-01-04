/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _536f93f0_914e_40ff_8917_36644acbc4b1
#define _536f93f0_914e_40ff_8917_36644acbc4b1

#include <istream>

#include "odil/odil.h"
#include "odil/dul/PDU.h"

namespace odil
{

namespace dul
{

/// @brief A-ABORT PDU, cf. PS 3.8, 9.3.8.
class ODIL_API AAbort: public PDU
{
public:
    /// @brief PDU type.
    static uint8_t const type=0x07;

    /// @brief Constructor.
    AAbort(unsigned char source, unsigned char reason);

    /// @brief Constructor for binary data.
    AAbort(std::istream & stream);

    /// @brief Return the source.
    unsigned char get_source() const;

    /// @brief Set the source, must be 0, 1 or 2.
    void set_source(unsigned char source);

    /// @brief Return the reason.
    unsigned char get_reason() const;

    /// @brief Set the reason, must be between 0 and 6.
    void set_reason(unsigned char reason);
};

}

}

#endif // _536f93f0_914e_40ff_8917_36644acbc4b1
