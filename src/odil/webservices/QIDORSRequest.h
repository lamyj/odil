/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1cd2d27d_2d97_405b_b9d5_4104210e543a
#define _1cd2d27d_2d97_405b_b9d5_4104210e543a

#include <string>

#include "odil/DataSet.h"
#include "odil/odil.h"
#include "odil/webservices/QIDORS.h"
#include "odil/webservices/URL.h"

namespace odil
{

namespace webservices
{


/// @brief QIDO-RS request generator and parser
class ODIL_API QIDORSRequest
{
public:
    /// @brief Constructor
    QIDORSRequest(
        URL const & base_url);
    /// @brief Destructor
    ~QIDORSRequest() = default;


private:
    URL _base_url;

    std::string _media_type;
    DataSet _query;
    QIDORS::Representation _representation;
    URL _url;


};

}

}


#endif // _1cd2d27d_2d97_405b_b9d5_4104210e543a
