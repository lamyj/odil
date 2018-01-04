/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7449339a_913f_4545_9846_311f055632c1
#define _7449339a_913f_4545_9846_311f055632c1

#include <initializer_list>
#include <istream>
#include <vector>

#include "odil/odil.h"
#include "odil/dul/MaximumLength.h"
#include "odil/dul/SubItem.h"
#include "odil/dul/UserIdentityAC.h"
#include "odil/dul/UserIdentityRQ.h"

namespace odil
{

namespace dul
{

/// @brief User Information Item Structure (PS 3.8, 9.3.2.3 and 9.3.3.3).
class ODIL_API UserInformation: public SubItem
{
public:
    /// @brief Item type.
    static uint8_t const type=0x50;

    /// @brief Create a User Information item with no sub-items.
    UserInformation();

    /// @brief Read a User Information item from a stream.
    UserInformation(std::istream & stream);

    /// @brief Return sub-items of given type.
    template<typename TObject>
    std::vector<TObject> get_sub_items() const;

    /// @brief Set a sequence of sub-items.
    template<typename TObject>
    void set_sub_items(std::vector<TObject> const & sub_item);

    /// @brief Delete sub-items of given type.
    template<typename TObject>
    void delete_sub_items();
private:
    typedef std::vector<Item> Items;

    /// @brief Return the iterators to the sub items of given type.
    template<typename TObject>
    std::vector<Items::const_iterator> _find_sub_items() const;

    /// @brief Return the iterators to the sub items of given type.
    template<typename TObject>
    std::vector<Items::iterator> _find_sub_items();
};

}

}

#include "odil/dul/UserInformation.txx"

#endif // _7449339a_913f_4545_9846_311f055632c1
