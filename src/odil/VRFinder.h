/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b7afd80f_327e_4d9a_b0fa_88c565add7b3
#define _b7afd80f_327e_4d9a_b0fa_88c565add7b3

#include <functional>
#include <string>
#include <vector>

#include "odil/DataSet.h"
#include "odil/Tag.h"
#include "odil/VR.h"

namespace odil
{

/// @brief Find the VR of elements in an implicit VR data set.
class VRFinder
{
public:
    /**
     * @brief Prototype of finder functions.
     *
     * Finder functions must raise an exception if they are not applicable.
     */
    typedef
        std::function<VR(Tag const &, DataSet const &, std::string const &)>
        Finder;

    /// @brief Default finder functions.
    static std::vector<Finder> const default_finders;

    /// @brief User-defined finder functions, empty by default.
    std::vector<Finder> finders;

    /// @brief Constructor.
    VRFinder();

    /**
     * @brief Return a VR for the given tag, partially-constructed data set and
     * transfer-syntax. If no VR can be found, raise an exception.
     *
     * The user-defined finders are tried first, then the default_finders.
     */
    VR operator()(
        Tag const & tag, DataSet const & data_set,
        std::string const & transfer_syntax) const;

    /// @brief Return the VR from the public dictionary.
    static VR public_dictionary(
        Tag const & tag, DataSet const &, std::string const &);

    /// @brief Return the VR of group-length (gggg,0000) elements.
    static VR group_length(
        Tag const & tag, DataSet const &, std::string const &);

    /// @brief Return a default VR (UN) for private tags.
    static VR private_tag(
        Tag const & tag, DataSet const &, std::string const &);

    /// @brief Return the VR of elements defined in PS3.5, A.1 (c).
    static VR implicit_vr_little_endian(
        Tag const & tag, DataSet const & data_set,
        std::string const & transfer_syntax);
    
    /// @brief Return the VR of elements defined in PS3.5, A.2 (c).
    static VR explicit_vr_little_endian(
        Tag const & tag, DataSet const & data_set,
        std::string const & transfer_syntax);

private:
    static std::vector<Finder> _get_default_finders();
};

}

#endif // _b7afd80f_327e_4d9a_b0fa_88c565add7b3
