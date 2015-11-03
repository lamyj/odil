/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _3980566c_9185_40a2_8e7d_6286c2cd1959
#define _3980566c_9185_40a2_8e7d_6286c2cd1959

#include "dcmtkpp/ProtocolDataUnit.h"

namespace dcmtkpp
{

/// @brief A-ASSOCIATE-RJ PDU, cf. PS 3.8, 9.3.4.
class AAssociateRJPDU: public ProtocolDataUnit
{
public:
    /// @brief Constructor.
    AAssociateRJPDU(unsigned char source, unsigned char reason);

    /// @brief Constructor for binary data.
    AAssociateRJPDU(Data const & data);

    /// @brief Destructor.
    virtual ~AAssociateRJPDU();

    /// @brief Return the source.
    unsigned char get_source() const;

    /// @brief Set the source, must be 1, 2 or 3.
    void set_source(unsigned char source);

    /// @brief Return the reason.
    unsigned char get_reason() const;

    /// @brief Set the reason.
    void set_reason(unsigned char reason);

    /// @brief Return the binary representation of the PDU.
    virtual Data as_binary() const;

private:
    unsigned char _source;
    unsigned char _reason;
};

}

#endif // _3980566c_9185_40a2_8e7d_6286c2cd1959
