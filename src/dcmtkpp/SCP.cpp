/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "SCP.h"

namespace dcmtkpp
{

SCP
::SCP()
: ServiceRole()
{
    // Nothing else.
}

SCP
::~SCP()
{
    // Nothing to do.
}

void
SCP
::_send_echo_response(T_DIMSE_C_EchoRQ request) const
{
    T_DIMSE_C_EchoRSP response;
    memset(&response, 0, sizeof(response));
    response.MessageIDBeingRespondedTo = request.MessageID;
    response.DimseStatus = 0;
    response.DataSetType = DIMSE_DATASET_NULL;
    OFStandard::strlcpy(
        response.AffectedSOPClassUID, request.AffectedSOPClassUID, 
        sizeof(response.AffectedSOPClassUID));
        
    this->_send<DIMSE_C_ECHO_RSP>(response, request.AffectedSOPClassUID);
}

}
