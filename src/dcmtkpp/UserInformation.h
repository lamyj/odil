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

#include "dcmtkpp/MaximumLength.h"
#include "dcmtkpp/ProtocolDataUnitObjectBase.h"
#include "dcmtkpp/UserIdentityAC.h"
#include "dcmtkpp/UserIdentityRQ.h"

namespace dcmtkpp
{

/// @brief User Information Item Structure (PS 3.8, 9.3.2.3 and 9.3.3.3).
class UserInformation: public ProtocolDataUnitObjectBase
{
public:
    /// @brief Create a User Information item with no sub-items.
    UserInformation();

    /// @brief Read a User Information item from a stream.
    UserInformation(std::istream & stream);

    /// @brief Test whether the Maximum Length sub-item is set.
    bool has_maximum_length() const;

    /// @brief Return the Maximum Length sub-item or throw an exception if not set.
    MaximumLength get_maximum_length() const;

    /// @brief Set the Maximum Length sub-item.
    void set_maximum_length(MaximumLength const & item);

    /// @brief Delete the Maximum Length sub-item.
    void delete_maximum_length();

    /// @brief Test whether the User Identity (A-ASSOCIATE-RQ) sub-item is set.
    bool has_user_identity_rq() const;

    /// @brief Return the User Identity (A-ASSOCIATE-RQ) sub-item.
    UserIdentityRQ get_user_identity_rq() const;

    /// @brief Set the User Identity (A-ASSOCIATE-RQ) sub-item.
    void set_user_identity_rq(UserIdentityRQ const & item);

    /// @brief Delete the User Identity (A-ASSOCIATE-RQ) sub-item.
    void delete_user_identity_rq();

    /// @brief Test whether the User Identity (A-ASSOCIATE-AC) sub-item is set.
    bool has_user_identity_ac() const;

    /// @brief Return the User Identity (A-ASSOCIATE-AC) sub-item.
    UserIdentityAC get_user_identity_ac() const;

    /// @brief Set the User Identity (A-ASSOCIATE-AC) sub-item.
    void set_user_identity_ac(UserIdentityAC const & item);

    /// @brief Delete the User Identity (A-ASSOCIATE-AC) sub-item.
    void delete_user_identity_ac();
private:
    typedef std::vector<ProtocolDataUnitItem> Items;

    /// @brief Return the iterator to a sub-item or end.
    Items::const_iterator _find_sub_item(uint8_t type) const;

    /// @brief Return the iterator to a sub-item or end.
    Items::iterator _find_sub_item(uint8_t type);

    /// @brief Update the item length field.
    void _update_length();
};

}

#endif // _7449339a_913f_4545_9846_311f055632c1
