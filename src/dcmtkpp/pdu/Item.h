/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1c7b57cc_79f5_497c_815c_920e0711a864
#define _1c7b57cc_79f5_497c_815c_920e0711a864

#include <cstdint>
#include <istream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace dcmtkpp
{

namespace pdu
{

/// @brief A sequence of fields forming a full PDU or a part of it.
class Item
{
public:
    /// @brief Generic field.
    class Field
    {
    public:
        /// @brief Possible types stored in the field.
        enum class Type
        {
            unsigned_int_8,
            unsigned_int_16,
            unsigned_int_32,
            string,
            items
        };

        /// @brief Constructor.
        Field(uint8_t value);

        /// @brief Constructor.
        Field(uint16_t value);

        /// @brief Constructor.
        Field(uint32_t value);

        /// @brief Constructor.
        Field(std::string const & value);

        /// @brief Constructor.
        Field(std::vector<Item> const & value);

        /// @brief Return the concrete type stored in the field.
        Type get_type() const;

        /**
         * @brief Return the uint8_t stored in the field.
         *
         * If the field does not contain an uint8_t, a dcmtkpp::Exception is raised.
         */
        uint8_t as_unsigned_int_8() const;

        /**
         * @brief Return the uint8_t stored in the field.
         *
         * If the field does not contain an uint8_t, a dcmtkpp::Exception is raised.
         */
        uint8_t & as_unsigned_int_8();

        /**
         * @brief Return the uint16_t stored in the field.
         *
         * If the field does not contain an uint16_t, a dcmtkpp::Exception is raised.
         */
        uint16_t as_unsigned_int_16() const;

        /**
         * @brief Return the uint16_t stored in the field.
         *
         * If the field does not contain an uint16_t, a dcmtkpp::Exception is raised.
         */
        uint16_t & as_unsigned_int_16();

        /**
         * @brief Return the uint32_t stored in the field.
         *
         * If the field does not contain an uint32_t, a dcmtkpp::Exception is raised.
         */
        uint32_t as_unsigned_int_32() const;

        /**
         * @brief Return the uint32_t stored in the field.
         *
         * If the field does not contain an uint32_t, a dcmtkpp::Exception is raised.
         */
        uint32_t & as_unsigned_int_32();

        /**
         * @brief Return the string stored in the field.
         *
         * If the field does not contain an string, a dcmtkpp::Exception is raised.
         */
        std::string const & as_string() const;

        /**
         * @brief Return the string stored in the field.
         *
         * If the field does not contain an string, a dcmtkpp::Exception is raised.
         */
        std::string & as_string();

        /**
         * @brief Return the items stored in the field.
         *
         * If the field does not contain items, a dcmtkpp::Exception is raised.
         */
        std::vector<Item> const & as_items() const;

        /**
         * @brief Return the items stored in the field.
         *
         * If the field does not contain items, a dcmtkpp::Exception is raised.
         */
        std::vector<Item> & as_items();

    private:
        Type _type;
        uint8_t _uint8;
        uint16_t _uint16;
        uint32_t _uint32;
        std::string _string;
        std::vector<Item> _items;
    };

    typedef std::vector<std::pair<std::string, Field>> Container;

    /// @brief Create an empty PDU item.
    Item();

    /// @brief Create an initialized PDU item.
    Item(std::vector<std::pair<std::string, Field>> const & fields);

    /// @brief Add a new field to the PDU item.
    Item & add(std::string const & name, Field const & field);

    /// @brief Return the number of fields.
    Container::size_type size() const;

    /// @brief Test whether the container is empty.
    bool empty() const;

    /// @brief Test whether the PDU item contains a field with a given name.
    bool has_field(std::string const & name) const;

    /// @brief Return the named field. Raise an exception if no such field exists.
    Field const & operator[](std::string const & name) const;

    /// @brief Return the named field. Raise an exception if no such field exists.
    Field & operator[](std::string const & name);

    /**
     * @brief Return the named field as an uint8_t.
     *
     * Raise an exception if no such field exists or if the field does not
     * contain an uint8_t.
     */
    uint8_t as_unsigned_int_8(std::string const & name) const;

    /**
     * @brief Return the named field as an uint8_t.
     *
     * Raise an exception if no such field exists or if the field does not
     * contain an uint8_t.
     */
    uint8_t & as_unsigned_int_8(std::string const & name);

    /**
     * @brief Return the named field as an uint16_t.
     *
     * Raise an exception if no such field exists or if the field does not
     * contain an uint16_t.
     */
    uint16_t as_unsigned_int_16(std::string const & name) const;

    /**
     * @brief Return the named field as an uint16_t.
     *
     * Raise an exception if no such field exists or if the field does not
     * contain an uint16_t.
     */
    uint16_t & as_unsigned_int_16(std::string const & name);

    /**
     * @brief Return the named field as an uint32_t.
     *
     * Raise an exception if no such field exists or if the field does not
     * contain an uint32_t.
     */
    uint32_t as_unsigned_int_32(std::string const & name) const;

    /**
     * @brief Return the named field as an uint32_t.
     *
     * Raise an exception if no such field exists or if the field does not
     * contain an uint32_t.
     */
    uint32_t & as_unsigned_int_32(std::string const & name);

    /**
     * @brief Return the named field as a string.
     *
     * Raise an exception if no such field exists or if the field does not
     * contain a string.
     */
    std::string const & as_string(std::string const & name) const;

    /**
     * @brief Return the named field as a sequence of items.
     *
     * Raise an exception if no such field exists or if the field does not
     * contain a sequence of items.
     */
    std::string & as_string(std::string const & name);

    std::vector<Item> const & as_items(std::string const & name) const;

    /**
     * @brief Return the named field as a sequence of items.
     *
     * Raise an exception if no such field exists or if the field does not
     * contain a sequence of items.
     */
    std::vector<Item> & as_items(std::string const & name);

    typedef Container::const_iterator const_iterator;
    const_iterator begin() const;
    const_iterator end() const;

    /**
     * @brief Read a field from a stream.
     *
     * The size parameter is ignored for non-string types.
     */
    void read(
        std::istream & stream,std::string const & name, Field::Type type,
        std::streamsize size=0);

private:
    std::vector<std::pair<std::string, Field>> _fields;
};

// No operator>> since we need explicit names and types.

std::ostream &
operator<<(std::ostream & stream, Item const & item);

}

}

#endif // _1c7b57cc_79f5_497c_815c_920e0711a864
