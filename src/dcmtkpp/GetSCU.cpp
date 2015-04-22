/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/GetSCU.h"

#include <functional>
#include <sstream>
#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CGetRequest.h"
#include "dcmtkpp/CGetResponse.h"
#include "dcmtkpp/CStoreRequest.h"
#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

GetSCU
::~GetSCU()
{
    // Nothing to do
}

void 
GetSCU
::get(DcmDataset const & query, Callback callback) const
{
    // Send the request
    CGetRequest request(this->_association->get_association()->nextMsgID++,
        this->_affected_sop_class, DIMSE_PRIORITY_MEDIUM, &query);
    this->_send(request, this->_affected_sop_class);
    
    // Receive the responses
    bool done = false;
    while(!done)
    {
        Message const message = this->_receive();

        if(message.get_command_field() == DIMSE_C_GET_RSP)
        {
            done = this->_get_response(CGetResponse(message));
        }
        else if(message.get_command_field() == DIMSE_C_STORE_RQ)
        {
            try
            {
                this->_store_request(CStoreRequest(message), callback);
            }
            catch(...)
            {
                // FIXME: logging
                done = true;
            }
        }
        else
        {
            std::ostringstream exception_message;
            exception_message << "DIMSE: Unexpected Response Command Field: 0x"
                              << std::hex << message.get_command_field();
            throw Exception(exception_message.str());
        }
    }
}

std::vector<DcmDataset *>
GetSCU
::get(DcmDataset const & query) const
{
    std::vector<DcmDataset*> result;
    auto callback = [&result](DcmDataset const * dataset) {
        // We do not manage the allocation of dataset: clone it
        result.push_back(static_cast<DcmDataset*>(dataset->clone())); 
    };
    this->get(query, callback);
    
    return result;
}

bool
GetSCU
::_get_response(CGetResponse const & response) const
{
    bool const done = (response.get_status() != STATUS_Pending);
    return done;
}

void
GetSCU
::_store_request(CStoreRequest const & request, Callback callback) const
{
    StoreSCP scp;
    scp.set_network(this->get_network());
    scp.set_association(this->get_association());
    scp.store(request, callback);
}

}
