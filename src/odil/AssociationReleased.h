/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7eee187d_a0c6_4423_aafb_4061271d72c5
#define _7eee187d_a0c6_4423_aafb_4061271d72c5

#include "odil/odil.h"
#include "odil/Exception.h"

namespace odil
{

/** 
 * @brief Exception reported when receiving a message after the association was
 * released.
 */
class ODIL_API AssociationReleased: public Exception
{
public:
    AssociationReleased();
    virtual ~AssociationReleased() noexcept;
};

}

#endif // _7eee187d_a0c6_4423_aafb_4061271d72c5
