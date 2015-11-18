/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _30f1a581_9ae6_4a02_a455_bf2b6ea58bc6
#define _30f1a581_9ae6_4a02_a455_bf2b6ea58bc6

#include <cstdint>
#include <string>
#include <vector>

#include "dcmtkpp/ProtocolDataUnitObjectBase.h"

namespace dcmtkpp
{

/**
 * @brief Presentation Context item, either for a A-ASSOCIATE-RQ PDU (PS 3.8,
 * 9.3.2.2) or for a A-ASSOCIATE-AC PDU (PS 3.8, 9.3.3.2).
 */
class PresentationContext: public ProtocolDataUnitObjectBase
{
public:
    /// @brief Create a Presentation Context for a A-ASSOCIATE-RQ PDU.
    PresentationContext(
        std::string const & abstract_syntax,
        std::vector<std::string> const & transfer_syntaxes);

    /// @brief Create a Presentation Context for a A-ASSOCIATE-AC PDU.
    PresentationContext(std::string const & transfer_syntax);

    /// @brief Read a Presentation Context from a stream.
    PresentationContext(std::istream & stream, uint16_t length);

    /// @brief Return the Item-type.
    uint8_t get_item_type() const;

    /// @brief Return the Presentation context id.
    uint8_t get_id() const;

    /// @brief Set the Presentation context id.
    void set_id(u_int8_t id);

    /// @brief Return the Result/Reason (only for A-ASSOCIATE-AC PDU).
    uint8_t get_result_reason() const;

    /// @brief Set the Result/Reason (only for A-ASSOCIATE-AC PDU).
    void set_result_reason(u_int8_t result_reason);

    /// @brief Return the Abstract Syntax (only for A-ASSOCIATE-RQ PDU).
    std::string get_abstract_syntax() const;

    /// @brief Set the Abstract Syntax sub-item (only for A-ASSOCIATE-RQ PDU).
    void set_abstract_syntax(std::string const & abstract_syntax);

    /// @brief Return the Transfer Syntaxes (only for A-ASSOCIATE-RQ PDU).
    std::vector<std::string> get_transfer_syntaxes() const;

    /// @brief Set the Transfer Syntax sub-items (only for A-ASSOCIATE-RQ PDU).
    void set_transfer_syntaxes(
        std::vector<std::string> const & transfer_syntaxes);

    /// @brief Return the Transfer Syntax (only for A-ASSOCIATE-AC PDU).
    std::string get_transfer_syntax() const;

    /// @brief Set the Transfer Syntax sub-item (only for A-ASSOCIATE-AC PDU).
    void set_transfer_syntax(std::string const & transfer_syntax);

private:
    /// @brief Create an Abstract Syntax or Transfer Syntax sub-item.
    static ProtocolDataUnitItem _make_string_item(
        std::string const & type, std::string const & value);

    /// @brief Add the fields to the PDU item.
    void _add_fields();

    /// @brief Update the size field.
    void _update_size();
};

}

#endif // _30f1a581_9ae6_4a02_a455_bf2b6ea58bc6
