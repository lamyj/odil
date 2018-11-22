/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _9bd08c07_3afd_4d51_93c7_55d010d62bb3
#define _9bd08c07_3afd_4d51_93c7_55d010d62bb3

#include "odil/odil.h"
#include "odil/Exception.h"

namespace odil
{

/** 
 * @brief Exception reported when receiving a message after the association was
 * aborted.
 */
class ODIL_API AssociationAborted: public Exception
{
public:
    /// @brief Source of the error.
    uint8_t source;
    
    /// @brief Reason of the error.
    uint8_t reason;
    
    AssociationAborted(unsigned char source, unsigned char reason);
    virtual ~AssociationAborted() noexcept;
};

}

#endif // _9bd08c07_3afd_4d51_93c7_55d010d62bb3
