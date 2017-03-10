/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/webservices/QIDORSRequest.h"

namespace odil
{

namespace webservices
{

QIDORSRequest
::QIDORSRequest(const URL &base_url)
    : _base_url(base_url), _url(), _representation(QIDORS::Representation::DICOM_JSON),
      _media_type(), _query()
{
    // Nothing else
}

}

}
