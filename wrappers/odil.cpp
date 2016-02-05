/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

void wrap_DataSet();
void wrap_Element();
void wrap_Exception();
void wrap_read();
void wrap_Tag();
void wrap_uid();
void wrap_Value();
void wrap_VR();

BOOST_PYTHON_MODULE(_odil)
{
    wrap_DataSet();
    wrap_Element();
    wrap_Exception();
    wrap_read();
    wrap_Tag();
    wrap_uid();
    wrap_Value();
    wrap_VR();
}
