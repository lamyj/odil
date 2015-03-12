/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b9607695_cb3b_4188_8caa_bc8bb051ef28
#define _b9607695_cb3b_4188_8caa_bc8bb051ef28

#include <exception>
#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/ofcond.h>

namespace dcmtkpp
{

class Exception: public std::exception
{
public: 
    Exception(std::string const & message);
    Exception(OFCondition const & condition);
    
    virtual ~Exception() throw();
    
    virtual const char* what() const throw();
private:
    std::string _message;
};

}

#endif // _b9607695_cb3b_4188_8caa_bc8bb051ef28
