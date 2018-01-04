/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _973ae1d9_c41c_4518_9c35_df13b2253369
#define _973ae1d9_c41c_4518_9c35_df13b2253369

#include <vector>

#include "odil/odil.h"
#include "odil/dul/AAssociate.h"
#include "odil/dul/PresentationContextAC.h"

namespace odil
{

namespace dul
{

/// @brief A-ASSOCIATE-AC PDU, cf. PS 3.8, 9.3.3.
class ODIL_API AAssociateAC: public AAssociate
{
public:
    /// @brief Constructor.
    AAssociateAC();

    /// @brief Constructor for binary data.
    AAssociateAC(std::istream & stream);

    /// @brief Destructor.
    ~AAssociateAC();

    /// @brief Return the Presentation Context sub-items.
    std::vector<PresentationContextAC> get_presentation_contexts() const;

    /// @brief Set the Presentation Context sub-items.
    void set_presentation_contexts(std::vector<PresentationContextAC> const & value);
};

}

}

#endif // _973ae1d9_c41c_4518_9c35_df13b2253369
