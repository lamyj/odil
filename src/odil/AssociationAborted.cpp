/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "AssociationAborted.h"

#include "odil/odil.h"
#include "odil/Exception.h"

namespace odil
{

AssociationAborted
::AssociationAborted(unsigned char source, unsigned char reason)
: Exception("Association aborted"), source(source), reason(reason)
{
    // Nothing else.
}

AssociationAborted
::~AssociationAborted() noexcept
{
    // Nothing to do.
}

}
