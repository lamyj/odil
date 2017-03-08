/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _2e568ec2_62fc_43e5_8342_b4511db705e3
#define _2e568ec2_62fc_43e5_8342_b4511db705e3

#include "odil/Writer.h"

#include <ostream>
#include <string>

#include "odil/DataSet.h"
#include "odil/Element.h"
#include "odil/endian.h"
#include "odil/registry.h"
#include "odil/Tag.h"
#include "odil/Value.h"
#include "odil/VR.h"

namespace odil
{

template<typename T>
void
Writer
::write_binary(
    T const & value, std::ostream & stream, ByteOrdering byte_ordering)
{
    auto raw = value;
    if(byte_ordering == ByteOrdering::LittleEndian)
    {
        raw = host_to_little_endian(raw);
    }
    else if(byte_ordering == ByteOrdering::BigEndian)
    {
        raw = host_to_big_endian(raw);
    }
    else
    {
        throw Exception("Unknown endianness");
    }
    stream.write(reinterpret_cast<char const*>(&raw), sizeof(raw));
    if(!stream)
    {
        throw Exception("Could not write to stream");
    }
}

}

#endif // _2e568ec2_62fc_43e5_8342_b4511db705e3
