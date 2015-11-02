/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b3062f12_8a06_46a8_9dda_8a7edf96e4a6
#define _b3062f12_8a06_46a8_9dda_8a7edf96e4a6

#include <cstdint>
#include <vector>

#include "dcmtkpp/ProtocolDataUnit.h"

namespace dcmtkpp
{

/// @brief P-DATA-TF PDU, cf. PS 3.8, 9.3.5.
class PDataTFPDU: public ProtocolDataUnit
{
public:
    struct PresentationDataValue
    {
        bool is_command;
        bool is_last_fragment;
        Data fragment;

        bool operator==(PresentationDataValue const & other) const;
        bool operator!=(PresentationDataValue const & other) const;
    };

    struct PresentationDataValueItem
    {
        uint8_t presentation_context_id;
        PresentationDataValue pdv;

        bool operator==(PresentationDataValueItem const & other) const;
        bool operator!=(PresentationDataValueItem const & other) const;
    };

    /// @brief Constructor.
    PDataTFPDU(std::vector<PresentationDataValueItem> const & pdv_items);

    /// @brief Constructor for binary data.
    PDataTFPDU(Data const & data);

    /// @brief Destructor.
    virtual ~PDataTFPDU();

    /// @brief Return the Presentation Data Value Items.
    std::vector<PresentationDataValueItem> const & get_pdv_items() const;

    /// @brief Set the Presentation Data Value Items.
    void set_pdv_items(std::vector<PresentationDataValueItem> const &pdv_items);

    /// @brief Return the binary representation of the PDU.
    virtual Data as_binary() const;

private:
    std::vector<PresentationDataValueItem> _pdv_items;
};

}

#endif // _b3062f12_8a06_46a8_9dda_8a7edf96e4a6
