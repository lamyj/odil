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

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

typedef boost::iostreams::stream<
        boost::iostreams::back_insert_device<std::string>
    > StringStream;

#endif // _dadc5c51_56d9_417e_9a96_100ed2838c2a
