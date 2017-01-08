/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _94f3b347_1f95_49ab_83f6_8710f5a3ad67
#define _94f3b347_1f95_49ab_83f6_8710f5a3ad67

#include "odil/Association.h"
#include "odil/odil.h"
#include "odil/SCU.h"

namespace odil
{

/// @brief SCU for the C-ECHO services.
class ODIL_API EchoSCU: public SCU
{
public:
    /// @brief Constructor
    EchoSCU(Association & association);

    /// @brief Destructor.
    virtual ~EchoSCU();
    
    /// @brief Perform DICOM ping
    void echo() const;
};

}

#endif // _94f3b347_1f95_49ab_83f6_8710f5a3ad67

