/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _87f54a57_5741_4fde_871b_ea9c774795ad
#define _87f54a57_5741_4fde_871b_ea9c774795ad

#include "dcmtkpp/ProtocolDataUnit.h"

namespace dcmtkpp
{

/// @brief A-RELEASE-RQ PDU, cf. PS 3.8, 9.3.6.
class AReleaseRQPDU: public ProtocolDataUnit
{
public:
    /// @brief Constructor.
    AReleaseRQPDU();

    /// @brief Constructor for binary data.
    AReleaseRQPDU(Data const & data);

    /// @brief Destructor.
    virtual ~AReleaseRQPDU();

    /// @brief Return the binary representation of the PDU.
    virtual Data as_binary() const;
};

}

#endif // _87f54a57_5741_4fde_871b_ea9c774795ad
