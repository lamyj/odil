/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _12bdb8f1_48c2_44d0_957a_bc1fb6f6733a
#define _12bdb8f1_48c2_44d0_957a_bc1fb6f6733a

#include <istream>
#include <string>

#include "odil/pdu/Object.h"

namespace odil
{

namespace pdu
{

/**
 * @brief Application Context item, (PS 3.8, 9.3.2.1).
 */
class ApplicationContext: public Object
{
public:
    /// @brief Create an Application Context.
    ApplicationContext(std::string const & name);

    /// @brief Read an Application Context from a stream.
    ApplicationContext(std::istream & stream);

    /// @brief Return the name of the Application Context.
    std::string get_name() const;

    /// @brief Set the name of the Application Context.
    void set_name(std::string const & name);
};

}

}

#endif // _12bdb8f1_48c2_44d0_957a_bc1fb6f6733a
