/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _4182d886_9654_4ec2_8cd6_7f334f290e56
#define _4182d886_9654_4ec2_8cd6_7f334f290e56

#include <istream>
#include <string>
#include <vector>

#include "odil/odil.h"
#include "odil/dul/SubItem.h"

namespace odil
{

namespace dul
{

/// @brief SOP Class Common Extended Negotiation sub-item (PS 3.7, D.3.3.6).
class ODIL_API SOPClassCommonExtendedNegotiation: public SubItem
{
public:
    /// @brief Item type.
    static uint8_t const type=0x57;

    /// @brief Constructor.
    SOPClassCommonExtendedNegotiation(
        std::string const & sop_class_uid,
        std::string const & service_class_uid="",
        std::vector<std::string> const &
            related_general_sop_class_uids=std::vector<std::string>());

    /// @brief Read a SOP Class Common Extended Negotiation from a stream.
    SOPClassCommonExtendedNegotiation(std::istream & stream);

    /// @brief Comparison.
    bool operator==(SOPClassCommonExtendedNegotiation const & other) const;

    /// @brief Return the SOP Class UID.
    std::string const & get_sop_class_uid() const;

    /// @brief Set the SOP Class UID.
    void set_sop_class_uid(std::string const & value);

    /// @brief Return the Service Class UID.
    std::string const & get_service_class_uid() const;

    /// @brief Set the Service Class UID (default to "").
    void set_service_class_uid(std::string const & value);

    /// @brief Return the Related General SOP Class UIDs.
    std::vector<std::string> get_related_general_sop_class_uids() const;

    /// @brief Set the Related General SOP Class UIDs (default to empty).
    void set_related_general_sop_class_uids(
        std::vector<std::string> const & value);

};

}

}

#endif // _4182d886_9654_4ec2_8cd6_7f334f290e56
