/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f4b88e07_d515_41be_ad1b_37899ec6451e
#define _f4b88e07_d515_41be_ad1b_37899ec6451e

#include <map>
#include <string>

#include <odil/Tag.h>

namespace odil
{

    /// @brief Key of a dictionary of DICOM elements.
    class ElementsDictionaryKey
    {
    public:
        /// @brief Type of the key.
        enum class Type
        {
            Tag,
            String,
            None
        };

        /// @brief Create a key with type equal to None.
        ElementsDictionaryKey();

        /// @brief Create a key with type equal to Tag.
        ElementsDictionaryKey(Tag const & value);

        /// @brief Create a key with type equal to String.
        ElementsDictionaryKey(std::string const & value);

        /// @brief Return the type.
        Type const & get_type() const;

        /// @brief Return the tag value or raise an exception if type is not Tag.
        Tag const & get_tag() const;

        /// @brief Return the string value or raise an exception if type is not String.
        std::string const & get_string() const;

        /// @brief Set the type to Tag.
        void set(Tag const value);

        /// @brief Set the type to String.
        void set(std::string const & value);

        /// @brief Comparator.
        bool operator<(ElementsDictionaryKey const & other) const;

    private:
        Type _type;
        Tag _tag;
        std::string _string;
    };

/**
 * @brief Entry in a dictionary of DICOM elements.
 */
struct ElementsDictionaryEntry
{
    std::string name;
    std::string keyword;
    std::string vr;
    std::string vm;

    ElementsDictionaryEntry(
        std::string const & name, std::string const & keyword,
        std::string const & vr, std::string const & vm);
};

typedef
    std::map<ElementsDictionaryKey, ElementsDictionaryEntry> ElementsDictionary;

}

#endif // _f4b88e07_d515_41be_ad1b_37899ec6451e
