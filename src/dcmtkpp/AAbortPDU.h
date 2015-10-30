/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _536f93f0_914e_40ff_8917_36644acbc4b1
#define _536f93f0_914e_40ff_8917_36644acbc4b1

#include "dcmtkpp/ProtocolDataUnit.h"

namespace dcmtkpp
{

/// @brief A-ABORT PDU, cf. PS 3.8, 9.3.8.
class AAbortPDU: public ProtocolDataUnit
{
public:
    /// @brief Constructor.
    AAbortPDU(unsigned char source, unsigned char reason);

    /// @brief Constructor for binary data.
    AAbortPDU(Data const & data);

    /// @brief Destructor.
    virtual ~AAbortPDU();

    /// @brief Return the source.
    unsigned char get_source() const;

    /// @brief Set the source, must be 0, 1 or 2.
    void set_source(unsigned char source);

    /// @brief Return the reason.
    unsigned char get_reason() const;

    /// @brief Set the reason, must be between 0 and 6.
    void set_reason(unsigned char reason);

    /// @brief Return the binary representation of the PDU.
    virtual Data as_binary() const;

private:
    unsigned char _source;
    unsigned char _reason;
};

}

#endif // _536f93f0_914e_40ff_8917_36644acbc4b1
