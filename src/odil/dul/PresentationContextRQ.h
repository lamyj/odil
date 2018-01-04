/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _e6e42ffd_7318_48f5_b35a_d44093564044
#define _e6e42ffd_7318_48f5_b35a_d44093564044

#include <cstdint>
#include <istream>
#include <string>
#include <vector>

#include "odil/odil.h"
#include "odil/dul/PresentationContext.h"

namespace odil
{

namespace dul
{

/// @brief Presentation Context item for a A-ASSOCIATE-RQ PDU (PS 3.8, 9.3.2.2).
class ODIL_API PresentationContextRQ: public PresentationContext
{
public:
    /// @brief Constructor.
    PresentationContextRQ(
        uint8_t id, std::string const & abstract_syntax,
        std::vector<std::string> const & transfer_syntaxes);

    /// @brief Read a Presentation Context from a stream.
    PresentationContextRQ(std::istream & stream);

    /// @brief Destructor.
    ~PresentationContextRQ();

    /// @brief Return the Abstract Syntax.
    std::string get_abstract_syntax() const;

    /// @brief Set the Abstract Syntax.
    void set_abstract_syntax(std::string const & abstract_syntax);

    /// @brief Return the Transfer Syntaxes.
    std::vector<std::string> get_transfer_syntaxes() const;

    /// @brief Set the Transfer Syntax sub-items.
    void set_transfer_syntaxes(
        std::vector<std::string> const & transfer_syntaxes);
};

}

}

#endif // _e6e42ffd_7318_48f5_b35a_d44093564044
