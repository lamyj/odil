/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _5faf4691_e936_476e_8ad3_40f36a167a74
#define _5faf4691_e936_476e_8ad3_40f36a167a74

#include <cstddef>
#include <string>

namespace dcmtkpp
{

/**
 * @brief A DICOM element tag.
 */
class Tag
{
public:
    /// @brief Create a tag based on its group and element as two 16-bits words.
    Tag(uint16_t group, uint16_t element);

    /// @brief Create a tag based on its group and element as one 32-bits word.
    Tag(uint32_t tag);

    /**
     * @brief Create a tag based on its name.
     *
     * If the name cannot be found in the public data dictionary,
     * a dcmtkpp::Exception is raised.
     */
    Tag(std::string const & name);

    /// @brief Group of the tag.
    uint16_t group;

    /// @brief Element of the tag.
    uint16_t element;

    /**
     * @brief Return the name of the tag.
     *
     * If the tag cannot be found in the public data dictionary,
     * a dcmtkpp::Exception is raised.
     */
    std::string get_name() const;
};

}

#endif // _5faf4691_e936_476e_8ad3_40f36a167a74
