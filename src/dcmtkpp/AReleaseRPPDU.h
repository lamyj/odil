/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a70fb011_8d69_4768_a84d_7f535621c335
#define _a70fb011_8d69_4768_a84d_7f535621c335

#include "dcmtkpp/ProtocolDataUnit.h"

namespace dcmtkpp
{

/// @brief A-RELEASE-RP PDU, cf. PS 3.8, 9.3.7.
class AReleaseRPPDU: public ProtocolDataUnit
{
public:
    /// @brief Constructor.
    AReleaseRPPDU();

    /// @brief Constructor for binary data.
    AReleaseRPPDU(Data const & data);

    /// @brief Destructor.
    virtual ~AReleaseRPPDU();

    /// @brief Return the binary representation of the PDU.
    virtual Data as_binary() const;
};

}

#endif // _a70fb011_8d69_4768_a84d_7f535621c335
