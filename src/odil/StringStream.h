/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _dadc5c51_56d9_417e_9a96_100ed2838c2a
#define _dadc5c51_56d9_417e_9a96_100ed2838c2a

#include <string>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

namespace odil
{

/// @brief Source stringstream which does not copy its buffer.
typedef boost::iostreams::stream<boost::iostreams::array_source> IStringStream;

template<typename T>
T as(std::string const & string)
{
    T result;
    IStringStream stream(&string[0], string.size());
    stream >> result;
    return result;
}

/// @brief Sink stringstream which does not copy its buffer.
typedef boost::iostreams::stream<
        boost::iostreams::back_insert_device<std::string>
    > OStringStream;

}

#endif // _dadc5c51_56d9_417e_9a96_100ed2838c2a
