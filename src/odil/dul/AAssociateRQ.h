/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _22fc6fe5_f7d1_461b_932f_cedfcae13897
#define _22fc6fe5_f7d1_461b_932f_cedfcae13897

#include <vector>

#include "odil/odil.h"
#include "odil/dul/AAssociate.h"
#include "odil/dul/PresentationContextRQ.h"

namespace odil
{

namespace dul
{

/// @brief A-ASSOCIATE-RQ, cf. PS 3.8, 9.3.2
class ODIL_API AAssociateRQ: public AAssociate
{
public:
    /// @brief Constructor.
    AAssociateRQ();

    /// @brief Constructor for binary data.
    AAssociateRQ(std::istream & stream);

    /// @brief Destructor.
    ~AAssociateRQ();

    /// @brief Return the Presentation Context sub-items.
    std::vector<PresentationContextRQ> get_presentation_contexts() const;

    /// @brief Set the Presentation Context sub-items.
    void set_presentation_contexts(std::vector<PresentationContextRQ> const & value);
};

}

}

#endif // _22fc6fe5_f7d1_461b_932f_cedfcae13897
