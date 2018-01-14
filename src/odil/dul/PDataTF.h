/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b3062f12_8a06_46a8_9dda_8a7edf96e4a6
#define _b3062f12_8a06_46a8_9dda_8a7edf96e4a6

#include <cstdint>
#include <istream>
#include <memory>
#include <vector>

#include "odil/odil.h"
#include "odil/dul/PDU.h"

namespace odil
{

namespace dul
{

/// @brief P-DATA-TF PDU, cf. PS 3.8, 9.3.5.
class ODIL_API PDataTF: public PDU
{
public:
    class ODIL_API PresentationDataValueItem: public Object
    {
    public:
        PresentationDataValueItem(
            uint8_t presentation_context_id, uint8_t control_header,
            std::string const & fragment);

        PresentationDataValueItem(std::istream & stream);

        uint8_t get_presentation_context_id() const;
        void set_presentation_context_id(uint8_t value);

        uint8_t get_control_header() const;
        void set_control_header(uint8_t value);

        bool is_command() const;
        bool is_last_fragment() const;

        std::string const & get_fragment() const;
        void set_fragment(std::string const & fragment);
    };

    typedef std::shared_ptr<PDataTF> Pointer;

    /// @brief PDU type.
    static uint8_t const type=0x04;

    /// @brief Constructor.
    PDataTF(std::vector<PresentationDataValueItem> const & pdv_items);

    /// @brief Constructor from stream.
    PDataTF(std::istream & stream);

    /// @brief Return the Presentation Data Value Items.
    std::vector<PresentationDataValueItem> get_pdv_items() const;

    /// @brief Set the Presentation Data Value Items.
    void set_pdv_items(std::vector<PresentationDataValueItem> const &pdv_items);
};

}

}

#endif // _b3062f12_8a06_46a8_9dda_8a7edf96e4a6
