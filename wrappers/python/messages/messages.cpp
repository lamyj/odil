/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

void wrap_Message(pybind11::module &);
void wrap_CommandTypeEnum(pybind11::module &);
void wrap_ResponseStatus(pybind11::module &);
void wrap_Request(pybind11::module &);
void wrap_Response(pybind11::module &);
void wrap_CEchoRequest(pybind11::module &);
void wrap_CEchoResponse(pybind11::module &);
void wrap_CFindRequest(pybind11::module &);
void wrap_CFindResponse(pybind11::module &);
void wrap_CGetRequest(pybind11::module &);
void wrap_CGetResponse(pybind11::module &);
void wrap_CMoveRequest(pybind11::module &);
void wrap_CMoveResponse(pybind11::module &);
void wrap_CStoreRequest(pybind11::module &);
void wrap_CStoreResponse(pybind11::module &);
void wrap_NSetRequest(pybind11::module &);
void wrap_NCreateRequest(pybind11::module &);

void wrap_messages(pybind11::module & m)
{
    auto messages = m.def_submodule("messages");
    wrap_Message(messages);
    wrap_ResponseStatus(messages);
    wrap_Request(messages);
    wrap_Response(messages);
    wrap_CEchoRequest(messages);
    wrap_CEchoResponse(messages);
    wrap_CFindRequest(messages);
    wrap_CFindResponse(messages);
    wrap_CGetRequest(messages);
    wrap_CGetResponse(messages);
    wrap_CMoveRequest(messages);
    wrap_CMoveResponse(messages);
    wrap_CStoreRequest(messages);
    wrap_CStoreResponse(messages);
    wrap_NSetRequest(messages);
    wrap_NCreateRequest(messages);
}
