/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _69f1f7a9_d252_4ccd_a2d5_5df0ac4fb054
#define _69f1f7a9_d252_4ccd_a2d5_5df0ac4fb054

#include <cstdint>
#include <istream>
#include <string>

#include "odil/odil.h"
#include "odil/pdu/PresentationContext.h"

namespace odil
{

namespace pdu
{

/// @brief Presentation Context item for a A-ASSOCIATE-AC PDU (PS 3.8, 9.3.3.2).
class ODIL_API PresentationContextAC: public PresentationContext
{
public:
    /// @brief Constructor.
    PresentationContextAC(
        uint8_t id, std::string const & transfer_syntax, uint8_t result_reason);

    /// @brief Read a Presentation Context from a stream.
    PresentationContextAC(std::istream & stream);

    /// @brief Destructor.
    ~PresentationContextAC();

    /// @brief Return the Result/Reason.
    uint8_t get_result_reason() const;

    /// @brief Set the Result/Reason.
    void set_result_reason(uint8_t result_reason);

    /// @brief Return the Transfer Syntax.
    std::string get_transfer_syntax() const;

    /// @brief Set the Transfer Syntax.
    void set_transfer_syntax(std::string const & transfer_syntax);
};

}

}

#endif // _69f1f7a9_d252_4ccd_a2d5_5df0ac4fb054
