/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _da2270e3_d393_415a_9c5c_6253152ed9da
#define _da2270e3_d393_415a_9c5c_6253152ed9da

#include <ostream>

#include "odil/odil.h"
#include "odil/dul/Item.h"

namespace odil
{

namespace dul
{

/**
 * @brief Base class for all PDU-related high-level objects (PDU, items and
 * sub-items).
 */
class ODIL_API Object
{
public:
    /// @brief Destructor, makes the type polymorphic.
    virtual ~Object();

    /// @brief Get the underlying item.
    Item const & get_item() const;

protected:
    Item _item;

    /// @brief Compute the value of the length field of the object.
    uint32_t _compute_length() const;

    /// @brief Compute the full size of an item.
    uint32_t _compute_length(Item const & item) const;

    /// @brief Compute the full size of a field.
    uint32_t _compute_length(Item::Field const & field) const;
};

/// @brief Dump the PDU-object in its binary form.
ODIL_API
std::ostream &
operator<<(std::ostream & stream, Object const & object);

}

}

#endif // _da2270e3_d393_415a_9c5c_6253152ed9da
