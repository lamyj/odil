/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/base64.h"

#include <string>

namespace odil
{

namespace base64
{

std::string const symbols =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Assume ASCII encoding
std::string const reversed_symbols(
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" // Not used: 00-0F
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" // Not used: 10-1F
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x3e\x00\x00\x00\x3f" // Not used: 20-2A, 2C-2E
    "\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x00\x00\x00\x00\x00\x00" // 0-9
    "\x00\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e" // A-O
    "\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x00\x00\x00\x00\x00" // P-Z
    "\x00\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28" // a-o
    "\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\x00\x00\x00\x00\x00" // p-z
    , 0x80);

}

}
