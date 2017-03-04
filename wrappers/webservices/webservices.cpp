/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

void wrap_webservices_Message();

namespace
{
    class webservices_namespace {};
}

void wrap_webservices()
{
    using namespace boost::python;

    scope webservices = class_<webservices_namespace>("webservices");
    wrap_webservices_Message();
}
