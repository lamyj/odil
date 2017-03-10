/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b1a6d333_684d_4b50_a9b9_68af24027a10
#define _b1a6d333_684d_4b50_a9b9_68af24027a10

#include <string>
#include <vector>

#include "odil/odil.h"
#include "odil/Exception.h"

namespace odil
{

namespace webservices
{

/// @brief Target (in the DICOM data model) of the request.
class ODIL_API Selector
{
public:
    /// @brief Constructor.
    Selector(
        std::string const & study="", std::string const & series="",
        std::string const & instance="", std::vector<int> const & frames={});

    /// @brief Equality operator.
    bool operator==(Selector const & other) const;

    /// @brief Difference operator.
    bool operator!=(Selector const & other) const;

    /**
     * @brief Return the associated URL path, with the optional "frames"
     * component.
     */
    std::string get_path(bool include_frames) const;

    std::string study;
    std::string series;
    std::string instance;
    std::vector<int> frames;

};

}

}


#endif // _b1a6d333_684d_4b50_a9b9_68af24027a10
