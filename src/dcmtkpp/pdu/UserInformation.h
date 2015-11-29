/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7449339a_913f_4545_9846_311f055632c1
#define _7449339a_913f_4545_9846_311f055632c1

#include <istream>

#include "dcmtkpp/pdu/MaximumLength.h"
#include "dcmtkpp/pdu/Object.h"
#include "dcmtkpp/pdu/UserIdentityAC.h"
#include "dcmtkpp/pdu/UserIdentityRQ.h"

namespace dcmtkpp
{

namespace pdu
{

/// @brief User Information Item Structure (PS 3.8, 9.3.2.3 and 9.3.3.3).
class UserInformation: public Object
{
public:
    /// @brief Create a User Information item with no sub-items.
    UserInformation();

    /// @brief Read a User Information item from a stream.
    UserInformation(std::istream & stream);

    /// @brief Test whether a sub-item is set.
    template<typename TObject>
    bool has_sub_item() const;

    /// @brief Return a sub-item.
    template<typename TObject>
    TObject get_sub_item() const;

    /// @brief Set a sub-item.
    template<typename TObject>
    void set_sub_item(TObject const & sub_item);

    /// @brief Delete a sub-item.
    template<typename TObject>
    void delete_sub_item();
private:
    typedef std::vector<Item> Items;

    /// @brief Return the iterator to a sub-item or end.
    template<typename TObject>
    Items::const_iterator _find_sub_item() const;

    /// @brief Return the iterator to a sub-item or end.
    template<typename TObject>
    Items::iterator _find_sub_item();
};

}

}

#include "dcmtkpp/pdu/UserInformation.txx"

#endif // _7449339a_913f_4545_9846_311f055632c1
