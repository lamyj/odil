/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _05d00816_25d0_41d1_9768_afd39f0503da
#define _05d00816_25d0_41d1_9768_afd39f0503da

#include "odil/odil.h"

#define ODIL_SWAP \
    auto source = reinterpret_cast<char const *>(&value); \
    auto const end = source + sizeof(value); \
    T result; \
    auto destination = reinterpret_cast<char *>(&result) + sizeof(result) - 1; \
    while(source != end) \
    { \
        *destination = *source; \
        ++source; \
        --destination; \
    }

namespace odil
{

enum class ODIL_API ByteOrdering
{
    LittleEndian,
    BigEndian
};

ByteOrdering ODIL_API get_endianness();

extern ODIL_API ByteOrdering const byte_ordering;

template<typename T>
T host_to_big_endian(T const & value)
{
    if(byte_ordering == ByteOrdering::LittleEndian)
    {
        ODIL_SWAP
        return result;
    }
    else
    {
        return value;
    }
}

template<typename T>
T host_to_little_endian(T const & value)
{
    if(byte_ordering == ByteOrdering::BigEndian)
    {
        ODIL_SWAP
        return result;
    }
    else
    {
        return value;
    }
}

template<typename T>
T big_endian_to_host(T const & value)
{
    if(byte_ordering == ByteOrdering::LittleEndian)
    {
        ODIL_SWAP
        return result;
    }
    else
    {
        return value;
    }
}

template<typename T>
T little_endian_to_host(T const & value)
{
    if(byte_ordering == ByteOrdering::BigEndian)
    {
        ODIL_SWAP
        return result;
    }
    else
    {
        return value;
    }
}

}

#undef ODIL_SWAP

#endif // _05d00816_25d0_41d1_9768_afd39f0503da
