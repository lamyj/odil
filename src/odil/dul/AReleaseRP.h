/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a70fb011_8d69_4768_a84d_7f535621c335
#define _a70fb011_8d69_4768_a84d_7f535621c335

#include <istream>
#include <memory>

#include "odil/odil.h"
#include "odil/dul/PDU.h"

namespace odil
{

namespace dul
{

/// @brief A-RELEASE-RP PDU, cf. PS 3.8, 9.3.7.
class ODIL_API AReleaseRP: public PDU
{
public:
    typedef std::shared_ptr<AReleaseRP> Pointer;
    /// @brief PDU type.
    static uint8_t const type=0x06;

    /// @brief Constructor.
    AReleaseRP();

    /// @brief Constructor from stream.
    AReleaseRP(std::istream & stream);
};

}

}

#endif // _a70fb011_8d69_4768_a84d_7f535621c335
