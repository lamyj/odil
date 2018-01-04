/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _87f54a57_5741_4fde_871b_ea9c774795ad
#define _87f54a57_5741_4fde_871b_ea9c774795ad

#include <istream>

#include "odil/odil.h"
#include "odil/dul/PDU.h"

namespace odil
{

namespace dul
{

/// @brief A-RELEASE-RQ PDU, cf. PS 3.8, 9.3.6.
class ODIL_API AReleaseRQ: public PDU
{
public:
    /// @brief PDU type.
    static uint8_t const type=0x05;

    /// @brief Constructor.
    AReleaseRQ();

    /// @brief Constructor from stream.
    AReleaseRQ(std::istream & stream);
};

}

}

#endif // _87f54a57_5741_4fde_871b_ea9c774795ad
