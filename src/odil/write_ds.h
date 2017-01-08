/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1fe89041_9f3b_4536_a55a_81f045984a62
#define _1fe89041_9f3b_4536_a55a_81f045984a62

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "odil/odil.h"

namespace odil
{

/// @brief Write a double as a DS to the buffer.
ODIL_API void write_ds(double f, char * buffer, int size=16);

}

#endif // _1fe89041_9f3b_4536_a55a_81f045984a62
