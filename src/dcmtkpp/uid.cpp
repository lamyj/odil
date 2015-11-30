/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/uid.h"

#include <string>

#include <uuid/uuid.h>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

#ifdef DCMTKPP_MAJOR_VERSION
/// @brief Implementation class UID of DCMTK++.
std::string const implementation_class_uid=uid_prefix+"0." DCMTKPP_STRINGIFY(DCMTKPP_MAJOR_VERSION);
#else
#error DCMTKPP_MAJOR_VERSION must be defined
#endif

std::string generate_uid()
{
    if(uid_prefix.size() > 26)
    {
        throw Exception("UID prefix is too long");
    }

    // Our prefix is 26 characters long. With the "." for separation, 37
    // characters remain. Since a random UUID has 122 random bits and since
    // 2^122-1 is 37 decimal digits long, the UID can be generated from a UUID.
    uuid_t uuid;
    uuid_generate(uuid);

    // Convert the UUID to two 61 bits integers
    uint64_t first=0;
    // time-high-and-version: 12 bits random, 4 bits version (2 bytes)
    first = (first + (uuid[7]>>4)) << 8;
    first = (first + ((uuid[7]&0xf)<<4)+(uuid[6]&0xf)) << 8;
    // time-mid: random (2 bytes)
    first = (first + uuid[5]) << 8;
    first = (first + uuid[4]) << 8;
    // time-low: random (4 bytes)
    first = (first + uuid[3]) << 8;
    first = (first + uuid[2]) << 8;
    first = (first + uuid[1]) << 8;
    first = (first + uuid[0]);

    uint64_t second=0;
    // node: 48 bits random (6 bytes)
    second = (second + uuid[15]) << 8;
    second = (second + uuid[14]) << 8;
    second = (second + uuid[13]) << 8;
    second = (second + uuid[12]) << 8;
    second = (second + uuid[11]) << 8;
    second = (second + uuid[10]) << 8;
    // clock_seq_low: 8 bits random (1 byte)
    second = (second + uuid[9]) << 8;
    // clock_seq_hi_and_reserved: 4 bits random, 4 bits variant (1 byte)
    second = (second + ((uuid[8]&0xf) << 4)) >> 4;

    std::string suffix;
    int remainder = 0;
    while(first != 0)
    {
        int digit = first%10;
        first = (first-digit)/10;
        if(first != 0)
        {
            suffix = std::to_string(digit)+suffix;
        }
        else
        {
            remainder = digit;
        }
    }

    second += remainder;
    while(second != 0)
    {
        int digit = second%10;
        second = (second-digit)/10;

        suffix = std::to_string(digit)+suffix;
    }

    return uid_prefix+"."+suffix;
}

}
