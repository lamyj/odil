/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b5ac563c_c5fd_4dcc_815c_66868a4b9614
#define _b5ac563c_c5fd_4dcc_815c_66868a4b9614

#include "odil/Reader.h"

#include <functional>
#include <istream>
#include <string>
#include <utility>

#include "odil/DataSet.h"
#include "odil/Element.h"
#include "odil/Exception.h"
#include "odil/endian.h"
#include "odil/Tag.h"
#include "odil/Value.h"
#include "odil/VR.h"

namespace odil
{

template<typename T>
T
Reader
::read_binary(std::istream & stream, ByteOrdering byte_ordering)
{
    T value;
    stream.read(reinterpret_cast<char*>(&value), sizeof(value));
    if(!stream)
    {
        throw Exception("Could not read from stream");
    }
    if(byte_ordering == ByteOrdering::LittleEndian)
    {
        value = little_endian_to_host(value);
    }
    else if(byte_ordering == ByteOrdering::BigEndian)
    {
        value = big_endian_to_host(value);
    }
    else
    {
        throw Exception("Unknown endianness");
    }

    return value;
}

}

#endif // _b5ac563c_c5fd_4dcc_815c_66868a4b9614
