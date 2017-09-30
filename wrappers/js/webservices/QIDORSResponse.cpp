/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <emscripten.h>
#include <emscripten/bind.h>

#include "odil/webservices/QIDORSResponse.h"

void wrap_webservices_QIDORSResponse()
{
    using namespace emscripten;
    using namespace odil::webservices;

    class_<QIDORSResponse>("webservices_QIDORSResponse")
        .constructor<HTTPResponse>()
        .function("equal", &QIDORSResponse::operator==)
        .function("notEqual", &QIDORSResponse::operator!=)
        .function("get_data_sets",
                  select_overload<std::vector<odil::DataSet> const & ()const >(&QIDORSResponse::get_data_sets))
        .function("set_data_sets", &QIDORSResponse::set_data_sets)
        .function("get_representation", &QIDORSResponse::get_representation)
        .function("set_representation", &QIDORSResponse::set_representation)
        .function("get_media_type", &QIDORSResponse::get_media_type)
        .function("get_http_response", &QIDORSResponse::get_http_response)
    ;

    EM_ASM(
        Module["webservices"]["QIDORSResponse"] =
            Module["webservices_QIDORSResponse"];
        delete Module["webservices_QIDORSResponse"];
    );

}
