/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b9607695_cb3b_4188_8caa_bc8bb051ef28
#define _b9607695_cb3b_4188_8caa_bc8bb051ef28

#include <exception>
#include <string>

namespace odil
{

/// @brief Base class for odil exceptions.
class Exception: public std::exception
{
public: 
    /// @brief Message string constructor.
    Exception(std::string const & message="");

    /// @brief Destructor.
    virtual ~Exception() throw();
    
    /// @brief Return the reason for the exception.
    virtual const char* what() const throw();

protected:
    /// @brief Message of the exception.
    std::string _message;
};

}

#endif // _b9607695_cb3b_4188_8caa_bc8bb051ef28
