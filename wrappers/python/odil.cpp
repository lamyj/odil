/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "opaque_types.h"
#include "type_casters.h"

//void wrap_std_map();
//void wrap_std_vector();

//void wrap_Association();
//void wrap_AssociationParameters();
void wrap_BasicDirectoryCreator(pybind11::module &);
void wrap_DataSet(pybind11::module &);
//void wrap_EchoSCP();
//void wrap_EchoSCU();
void wrap_Element(pybind11::module &);
void wrap_ElementsDictionary(pybind11::module &);
void wrap_endian(pybind11::module &);
void wrap_Exception(pybind11::module &);
//void wrap_FindSCP();
//void wrap_FindSCU();
//void wrap_GetSCP();
//void wrap_GetSCU();
void wrap_json_converter(pybind11::module &);
//void wrap_MoveSCP();
//void wrap_MoveSCU();
//void wrap_NCreateSCP();
//void wrap_NSetSCP();
//void wrap_NSetSCU();
void wrap_Reader(pybind11::module &);
void wrap_registry(pybind11::module &);
//void wrap_SCPDispatcher();
//void wrap_StoreSCU();
//void wrap_StoreSCP();
void wrap_Tag(pybind11::module &);
void wrap_uid(pybind11::module &);
void wrap_unicode(pybind11::module &);
void wrap_UIDsDictionary(pybind11::module &);
void wrap_Value(pybind11::module &);
void wrap_VR(pybind11::module &);
void wrap_VRFinder(pybind11::module &);
void wrap_Writer(pybind11::module &);
void wrap_xml_converter(pybind11::module &);

void wrap_Message(pybind11::module &);
void wrap_CommandTypeEnum(pybind11::module &);
void wrap_ResponseStatus(pybind11::module &);
void wrap_Request(pybind11::module &);
void wrap_Response(pybind11::module &);
void wrap_CEchoRequest(pybind11::module &);
void wrap_CFindRequest(pybind11::module &);
void wrap_CGetRequest(pybind11::module &);
void wrap_CGetResponse(pybind11::module &);
void wrap_CMoveRequest(pybind11::module &);
void wrap_CMoveResponse(pybind11::module &);
void wrap_CStoreRequest(pybind11::module &);
void wrap_CStoreResponse(pybind11::module &);
void wrap_NSetRequest(pybind11::module &);
void wrap_NCreateRequest(pybind11::module &);

//void wrap_webservices();

void wrap_iostream(pybind11::module &);

PYBIND11_MODULE(_odil, _odil)
{
//    wrap_std_map();
//    wrap_std_vector();

    wrap_endian(_odil);
    wrap_uid(_odil);

    wrap_Exception(_odil);

    wrap_Tag(_odil);
    wrap_Value(_odil);
    wrap_VR(_odil);
    wrap_VRFinder(_odil);

    wrap_unicode(_odil);

    wrap_Element(_odil);

    wrap_DataSet(_odil);

    wrap_ElementsDictionary(_odil);
    wrap_UIDsDictionary(_odil);
    wrap_registry(_odil);

    wrap_BasicDirectoryCreator(_odil);

    wrap_iostream(_odil);
    wrap_Reader(_odil);
    wrap_Writer(_odil);

    wrap_json_converter(_odil);
    wrap_xml_converter(_odil);

//    wrap_Association();
//    wrap_AssociationParameters();
//    wrap_EchoSCP();
//    wrap_EchoSCU();

//    wrap_FindSCP();
//    wrap_FindSCU();
//    wrap_GetSCP();
//    wrap_GetSCU();

//    wrap_MoveSCP();
//    wrap_MoveSCU();
//    wrap_NCreateSCP();
//    wrap_NSetSCP();
//    wrap_NSetSCU();
//    wrap_SCPDispatcher();
//    wrap_StoreSCP();
//    wrap_StoreSCU();

    wrap_Message(_odil);
    wrap_CommandTypeEnum(_odil);
    wrap_ResponseStatus(_odil);
    wrap_Request(_odil);
    wrap_Response(_odil);
    wrap_CEchoRequest(_odil);
    wrap_CFindRequest(_odil);
    wrap_CGetRequest(_odil);
    wrap_CGetResponse(_odil);
    wrap_CMoveRequest(_odil);
    wrap_CMoveResponse(_odil);
    wrap_CStoreRequest(_odil);
    wrap_CStoreResponse(_odil);
    wrap_NSetRequest(_odil);
    wrap_NCreateRequest(_odil);

//    wrap_webservices();
}
