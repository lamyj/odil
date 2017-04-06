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
#include <map>

#include "odil/odil.h"
#include "odil/Exception.h"
#include <boost/optional.hpp>

namespace odil
{

namespace webservices
{

/// @brief Target (in the DICOM data model) of the request.
class ODIL_API Selector
{
public:

    /// @brief Default Constructor
    Selector ();

    /// @brief Constructor which takes at least the study arg.
    Selector(
        std::string const & study, std::string const & series="",
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

    /// @brief return if study field is present in the selector
    bool is_study_present() const;
    /// @brief return if series field is present in the selector
    bool is_series_present() const;
    /// @brief return if instance field is present in the selector
    bool is_instance_present() const;

    /// @brief return the wanted study
    std::string const & get_study() const;
    /// @brief return the wanted series
    std::string const & get_series() const;
    /// @brief return the wanted instance
    std::string const & get_instance() const;
    /// @brief return the wanted frames
    std::vector<int> const & get_frames() const;

    /// @brief set the wanted study
    Selector& set_study(std::string const & study);
    /// @brief set the wanted series
    Selector& set_series(std::string const & series);
    /// @brief set the wanted instance
    Selector& set_instance(std::string const & instance);
    /// @brief set the wanted frames
    Selector& set_frames(std::vector<int> const & frames);

private:
    std::string _study;
    std::string _series;
    std::string _instance;
    std::vector<int> _frames;
    bool _study_present;
    bool _series_present;
    bool _instance_present;


};

}

}


#endif // _b1a6d333_684d_4b50_a9b9_68af24027a10
