/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _37346dec_0ab4_46d2_a54f_e349e79cd27d
#define _37346dec_0ab4_46d2_a54f_e349e79cd27d

#include <string>

namespace odil
{

namespace webservices
{

/// @brief Uniform resource locator
struct URL
{
    std::string scheme;
    std::string authority;
    std::string path;
    std::string query;
    std::string fragment;

    bool operator==(URL const & other) const;
    bool operator!=(URL const & other) const;

    /// @brief Recompose the components.
    operator std::string() const;

    /// @brief Parse an URL into its five components.
    static URL parse(std::string const & string);
};

}

}

#endif // _37346dec_0ab4_46d2_a54f_e349e79cd27d
