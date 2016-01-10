/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _87f54a57_5741_4fde_871b_ea9c774795ad
#define _87f54a57_5741_4fde_871b_ea9c774795ad

#include <istream>

#include "odil/pdu/Object.h"

namespace odil
{

namespace pdu
{

/// @brief A-RELEASE-RQ PDU, cf. PS 3.8, 9.3.6.
class AReleaseRQ: public Object
{
public:
    /// @brief Constructor.
    AReleaseRQ();

    /// @brief Constructor from stream.
    AReleaseRQ(std::istream & stream);
};

}

}

#endif // _87f54a57_5741_4fde_871b_ea9c774795ad
