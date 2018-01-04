/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _6e3d351d_e5dc_4ab6_9c2d_8582e4fe2aa5
#define _6e3d351d_e5dc_4ab6_9c2d_8582e4fe2aa5

#include <cstdint>
#include <istream>
#include <string>
#include <vector>

#include "odil/odil.h"
#include "odil/dul/Object.h"

namespace odil
{

namespace dul
{

/// @brief SOP Class Extended Negotiation sub-item (PS 3.7, D.3.3.5).
class ODIL_API SOPClassExtendedNegotiation: public Object
{
public:
    /// @brief Item type.
    static uint8_t const type=0x56;

    /// @brief Constructor.
    SOPClassExtendedNegotiation(
        std::string const & sop_class_uid,
        std::vector<uint8_t> const & service_class_application_information);

    /// @brief Read a SOP Class Common Extended Negotiation from a stream.
    SOPClassExtendedNegotiation(std::istream & stream);

    /// @brief Comparison.
    bool operator==(SOPClassExtendedNegotiation const & other) const;

    /// @brief Return the SOP Class UID.
    std::string const & get_sop_class_uid() const;

    /// @brief Set the SOP Class UID.
    void set_sop_class_uid(std::string const & value);

    /// @brief Return the Service Class Application Information.
    std::vector<uint8_t> get_service_class_application_information() const;

    /// @brief Set the Service Class Application Information.
    void set_service_class_application_information(
        std::vector<uint8_t> const & value);


};

}

}

#endif // _6e3d351d_e5dc_4ab6_9c2d_8582e4fe2aa5
