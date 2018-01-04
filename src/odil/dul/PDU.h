/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _dbd94ed9_4400_44c8_a411_ae22c2ef7310
#define _dbd94ed9_4400_44c8_a411_ae22c2ef7310

#include <cstdint>
#include <istream>

#include "odil/odil.h"
#include "odil/dul/Object.h"

namespace odil
{

namespace dul
{

/// @brief Base class for all PDUs
class PDU: public Object
{
public:
    PDU(uint8_t type);
    PDU(uint8_t type, std::istream & stream);

    PDU(PDU const &) =default;
    PDU(PDU &&) =default;

    PDU & operator=(PDU const &) =default;
    PDU & operator=(PDU &&) =default;

    ~PDU() =default;

    uint8_t get_pdu_type() const;
    uint32_t get_pdu_length() const;

protected:
    void _set_pdu_length(uint32_t length);
};

}

}

#endif // _dbd94ed9_4400_44c8_a411_ae22c2ef7310
