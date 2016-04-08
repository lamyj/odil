/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

void wrap_Association();
void wrap_AssociationParameters();
void wrap_DataSet();
void wrap_EchoSCU();
void wrap_Element();
void wrap_ElementsDictionary();
void wrap_Exception();
void wrap_FindSCU();
void wrap_GetSCU();
void wrap_json_converter();
void wrap_MoveSCU();
void wrap_read();
void wrap_StoreSCU();
void wrap_Tag();
void wrap_uid();
void wrap_UIDsDictionary();
void wrap_Value();
void wrap_VR();
void wrap_write();
void wrap_xml_converter();

void wrap_registry();

BOOST_PYTHON_MODULE(odil)
{
    wrap_Association();
    wrap_AssociationParameters();
    wrap_DataSet();
    wrap_EchoSCU();
    wrap_Element();
    wrap_ElementsDictionary();
    wrap_Exception();
    wrap_FindSCU();
    wrap_GetSCU();
    wrap_json_converter();
    wrap_MoveSCU();
    wrap_read();
    wrap_StoreSCU();
    wrap_Tag();
    wrap_uid();
    wrap_UIDsDictionary();
    wrap_Value();
    wrap_VR();
    wrap_write();
    wrap_xml_converter();

    wrap_registry();
}
