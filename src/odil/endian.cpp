/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/endian.h"

#include <cstdint>

namespace odil
{

ByteOrdering get_endianness()
{
    uint16_t const word = 0x0201;
    uint8_t const * bytes = reinterpret_cast<uint8_t const *>(&word);
    return (bytes[0] == 1)?ByteOrdering::LittleEndian:ByteOrdering::BigEndian;
}

}
