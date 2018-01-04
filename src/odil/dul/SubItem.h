/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _aa7c3a9f_fd12_4cfb_ba22_0a8c8627acf9
#define _aa7c3a9f_fd12_4cfb_ba22_0a8c8627acf9

#include <cstdint>
#include <istream>

#include "odil/odil.h"
#include "odil/dul/Object.h"

namespace odil
{

namespace dul
{

/// @brief Base class for all sub-items of PDUs.
class ODIL_API SubItem: public Object
{
public:
    SubItem(uint8_t type);
    SubItem(uint8_t type, std::istream & stream);

    SubItem(SubItem const &) =default;
    SubItem(SubItem &&) =default;

    SubItem & operator=(SubItem const &) =default;
    SubItem & operator=(SubItem &&) =default;

    ~SubItem() =default;

    uint8_t get_sub_item_type() const;
    uint16_t get_sub_item_length() const;

protected:
    void _set_sub_item_length(uint16_t length);
};

}

}

#endif // _aa7c3a9f_fd12_4cfb_ba22_0a8c8627acf9
