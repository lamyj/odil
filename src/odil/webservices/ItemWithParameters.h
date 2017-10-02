/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _64665a37_223c_4b0c_b0c2_7be9111d9bdd
#define _64665a37_223c_4b0c_b0c2_7be9111d9bdd

#include <istream>
#include <map>
#include <ostream>
#include <string>

#include "odil/odil.h"

namespace odil
{

namespace webservices
{

/**
 * @brief This container encapsulates the item with parameters as found in
 * varied HTTP headers (Accept, Accept-Charset, Accept-Encoding,
 * Accept-Language, Content-Type).
 *
 * name_parameters are used to store the parameters up to and excluding "q" (the
 * weight of this item), while extension_parameters will store the optional
 * weight and subsequent parameters.
 */
struct ODIL_API ItemWithParameters
{
    std::string name;
    std::map<std::string, std::string> name_parameters;
    std::map<std::string, std::string> extension_parameters;

    ItemWithParameters(
        std::string const & name="",
        std::map<std::string, std::string> const & name_parameters={},
        std::map<std::string, std::string> const & extension_parameters={});

    ~ItemWithParameters() =default;
    ItemWithParameters(ItemWithParameters const &) =default;
    ItemWithParameters(ItemWithParameters &&) =default;
    ItemWithParameters & operator=(ItemWithParameters const &) =default;
    ItemWithParameters & operator=(ItemWithParameters &&) =default;

    operator std::string() const;
};

/// @brief Input an AcceptableItem from a stream.
ODIL_API
std::istream &
operator>>(std::istream & stream, ItemWithParameters & item);

/// @brief Output an AcceptableItem to a stream.
ODIL_API
std::ostream &
operator<<(std::ostream & stream, ItemWithParameters const & item);

}

}

#endif // _64665a37_223c_4b0c_b0c2_7be9111d9bdd
