/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

void wrap_webservices_BulkData(pybind11::module &);
void wrap_webservices_HTTPRequest(pybind11::module &);
void wrap_webservices_HTTPResponse(pybind11::module &);
void wrap_webservices_Message(pybind11::module &);
void wrap_webservices_QIDORSRequest(pybind11::module &);
void wrap_webservices_QIDORSResponse(pybind11::module &);
void wrap_webservices_Selector(pybind11::module &);
void wrap_webservices_STOWRSRequest(pybind11::module &);
void wrap_webservices_STOWRSResponse(pybind11::module &);
void wrap_webservices_URL(pybind11::module &);
void wrap_webservices_Utils(pybind11::module &);
void wrap_webservices_WADORSRequest(pybind11::module &);
void wrap_webservices_WADORSResponse(pybind11::module &);

namespace
{
    class webservices_namespace {};
}

void wrap_webservices(pybind11::module & m)
{
    using namespace pybind11;

    auto webservices = m.def_submodule("webservices");

    wrap_webservices_Message(webservices);
    wrap_webservices_URL(webservices);

    wrap_webservices_BulkData(webservices);

    wrap_webservices_HTTPRequest(webservices);
    wrap_webservices_HTTPResponse(webservices);

    wrap_webservices_Selector(webservices);
    wrap_webservices_Utils(webservices);

    wrap_webservices_WADORSRequest(webservices);
    wrap_webservices_WADORSResponse(webservices);

    wrap_webservices_QIDORSRequest(webservices);
    wrap_webservices_QIDORSResponse(webservices);

    wrap_webservices_STOWRSRequest(webservices);
    wrap_webservices_STOWRSResponse(webservices);
}
