/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "AssociationReleased.h"

#include "odil/odil.h"
#include "odil/Exception.h"

namespace odil
{

AssociationReleased
::AssociationReleased()
: Exception("Association released")
{
    // Nothing else.
}

AssociationReleased
::~AssociationReleased() noexcept
{
    // Nothing to do.
}

}
