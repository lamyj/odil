    /*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

void wrap_std_map();
void wrap_std_vector();

void wrap_Association();
void wrap_AssociationParameters();
void wrap_BasicDirectoryCreator();
void wrap_DataSet();
void wrap_EchoSCP();
void wrap_EchoSCU();
void wrap_Element();
void wrap_ElementsDictionary();
void wrap_endian();
void wrap_Exception();
void wrap_FindSCP();
void wrap_FindSCU();
void wrap_GetSCP();
void wrap_GetSCU();
void wrap_json_converter();
void wrap_MoveSCP();
void wrap_MoveSCU();
void wrap_NCreateSCP();
void wrap_NSetSCP();
void wrap_NSetSCU();
void wrap_read();
void wrap_Reader();
void wrap_SCPDispatcher();
void wrap_StoreSCU();
void wrap_StoreSCP();
void wrap_Tag();
void wrap_uid();
void wrap_UIDsDictionary();
void wrap_Value();
void wrap_VR();
void wrap_VRFinder();
void wrap_write();
void wrap_Writer();
void wrap_xml_converter();

void wrap_registry();

void wrap_Message();
void wrap_CommandTypeEnum();
void wrap_ResponseStatus();
void wrap_Request();
void wrap_Response();
void wrap_CEchoRequest();
void wrap_CFindRequest();
void wrap_CGetRequest();
void wrap_CGetResponse();
void wrap_CMoveRequest();
void wrap_CMoveResponse();
void wrap_CStoreRequest();
void wrap_CStoreResponse();
void wrap_NSetRequest();

void wrap_webservices();

void wrap_iostream();

BOOST_PYTHON_MODULE(odil)
{
    wrap_std_map();
    wrap_std_vector();

    wrap_Exception();

    wrap_Association();
    wrap_AssociationParameters();
    wrap_BasicDirectoryCreator();
    wrap_DataSet();
    wrap_EchoSCP();
    wrap_EchoSCU();
    wrap_Element();
    wrap_ElementsDictionary();
    wrap_endian();
    wrap_FindSCP();
    wrap_FindSCU();
    wrap_GetSCP();
    wrap_GetSCU();
    wrap_json_converter();
    wrap_MoveSCP();
    wrap_MoveSCU();
    wrap_NCreateSCP();
    wrap_NSetSCP();
    wrap_NSetSCU();
    wrap_SCPDispatcher();
    wrap_StoreSCP();
    wrap_StoreSCU();
    wrap_Tag();
    wrap_uid();
    wrap_UIDsDictionary();
    wrap_Value();
    wrap_VR();
    wrap_VRFinder();
    wrap_xml_converter();

    wrap_iostream();

    wrap_Reader();
    wrap_Writer();
    wrap_registry();

    wrap_read();
    wrap_write();

    wrap_Message();
    wrap_CommandTypeEnum();
    wrap_ResponseStatus();
    wrap_Request();
    wrap_Response();
    wrap_CEchoRequest();
    wrap_CFindRequest();
    wrap_CGetRequest();
    wrap_CGetResponse();
    wrap_CMoveRequest();
    wrap_CMoveResponse();
    wrap_CStoreRequest();
    wrap_CStoreResponse();
    wrap_NSetRequest();

    wrap_webservices();
}
