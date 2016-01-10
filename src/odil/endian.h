/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _05d00816_25d0_41d1_9768_afd39f0503da
#define _05d00816_25d0_41d1_9768_afd39f0503da

#include <boost/detail/endian.hpp>

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

enum class ByteOrdering
{
    LittleEndian,
    BigEndian
};

template<typename T>
T host_to_big_endian(T const & value)
{
#ifdef BOOST_LITTLE_ENDIAN
    ODIL_SWAP

    return result;
#else
    return value;
#endif
}

template<typename T>
T host_to_little_endian(T const & value)
{
#ifdef BOOST_BIG_ENDIAN
    ODIL_SWAP

    return result;
#else
    return value;
#endif
}

template<typename T>
T big_endian_to_host(T const & value)
{
#ifdef BOOST_LITTLE_ENDIAN
    ODIL_SWAP

    return result;
#else
    return value;
#endif
}

template<typename T>
T little_endian_to_host(T const & value)
{
#ifdef BOOST_BIG_ENDIAN
    ODIL_SWAP

    return result;
#else
    return value;
#endif
}

}

#undef ODIL_SWAP

#endif // _05d00816_25d0_41d1_9768_afd39f0503da
