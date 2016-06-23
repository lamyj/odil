/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a24346ab_a585_4412_9237_5b2142f2d6eb
#define _a24346ab_a585_4412_9237_5b2142f2d6eb

#include <cstdint>
#include <istream>

#include "odil/pdu/Object.h"

namespace odil
{

namespace pdu
{

/// @brief Asynchronous Operations Window Sub-Item (PS 3.7, D.3.3.3.1 and D.3.3.3.2).
class AsynchronousOperationsWindow: public Object
{
public:
    /// @brief Item type.
    static uint8_t const type=0x53;

    /// @brief Create a Asynchronous Operations Window item.
    AsynchronousOperationsWindow(
        uint16_t maximum_number_operations_invoked,
        uint16_t maximum_number_operations_performed);

    /// @brief Read a Asynchronous Operations Window item from a stream.
    AsynchronousOperationsWindow(std::istream & stream);

    /// @brief Return the Maximum-number-operations-invoked.
    uint16_t get_maximum_number_operations_invoked() const;

    /// @brief Set the Maximum-number-operations-invoked.
    void set_maximum_number_operations_invoked(uint16_t value);
    
    /// @brief Return the Maximum-number-operations-performed.
    uint16_t get_maximum_number_operations_performed() const;

    /// @brief Set the Maximum-number-operations-performed.
    void set_maximum_number_operations_performed(uint16_t value);
};

}

}

#endif // _a24346ab_a585_4412_9237_5b2142f2d6eb
