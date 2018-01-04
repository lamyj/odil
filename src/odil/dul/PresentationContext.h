/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _30f1a581_9ae6_4a02_a455_bf2b6ea58bc6
#define _30f1a581_9ae6_4a02_a455_bf2b6ea58bc6

#include <cstdint>
#include <istream>
#include <string>
#include <vector>

#include "odil/odil.h"
#include "odil/pdu/Object.h"

namespace odil
{

namespace pdu
{

/**
 * @brief Presentation Context item, either for a A-ASSOCIATE-RQ PDU (PS 3.8,
 * 9.3.2.2) or for a A-ASSOCIATE-AC PDU (PS 3.8, 9.3.3.2).
 */
class ODIL_API PresentationContext: public Object
{
public:
    /// @brief Constructor
    PresentationContext();

    /// @brief Read from a stream.
    PresentationContext(std::istream & stream);

    /// @brief Destructor, make the class pure virtual.
    virtual ~PresentationContext() =0;

    /// @brief Return the Item-type.
    uint8_t get_item_type() const;

    /// @brief Return the Presentation context id.
    uint8_t get_id() const;

    /// @brief Set the Presentation context id.
    void set_id(uint8_t id);

protected:
    /// @brief Create an Abstract Syntax or Transfer Syntax sub-item.
    static Item _make_string_item(
        std::string const & type, std::string const & value);

    /// @brief Add common fields.
    void _add_fields();

    /// @brief Return the Abstract or Transfer syntaxes.
    std::vector<std::string> _get_syntaxes(std::string const & type) const;

    /// @brief Set the Abstract or Transfer syntaxes.
    void _set_syntaxes(
        std::string const & type, std::vector<std::string> const & syntaxes);
};

}

}

#endif // _30f1a581_9ae6_4a02_a455_bf2b6ea58bc6
