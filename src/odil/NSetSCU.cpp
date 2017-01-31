/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "NSetSCU.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include "odil/message/NSetRequest.h"
#include "odil/message/NSetResponse.h"
#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/registry.h"
#include "odil/SCU.h"

namespace odil
{

NSetSCU
::NSetSCU(Association & association)
: SCU(association)
{
    // Nothing else.
}

NSetSCU
::~NSetSCU()
{
    // Nothing to do.
}

void 
NSetSCU
::set_affected_sop_class(DataSet const & dataset)
{
    auto const & sop_class_uid = dataset.as_string(registry::RequestedSOPClassUID, 0);
    
    std::vector<std::string> storage;
    for(auto const & uids_it: registry::uids_dictionary)
    {
        auto const & name = uids_it.second.name;
        if(name.find("Storage") != std::string::npos)
        {
            storage.push_back(uids_it.first);
        }
    }

    if(std::find(storage.begin(), storage.end(), sop_class_uid) != storage.end())
    {
        this->SCU::set_affected_sop_class(sop_class_uid);
    }
    else
    {
        throw Exception("Could not guess affected SOP class from dataset");
    }
}

void 
NSetSCU
::set( DataSet const & dataset) const
{

    message::NSetRequest const request(
        this->_association.next_message_id(),
        this->_affected_sop_class,
        dataset.as_string(registry::RequestedSOPInstanceUID, 0),
        dataset
        );

    this->_association.send_message(request, this->_affected_sop_class);
    
    message::NSetResponse const response = this->_association.receive_message();

    if(response.get_message_id_being_responded_to() != request.get_message_id())
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response MsgId: "
                << response.get_message_id_being_responded_to()
                << "(expected: " << request.get_message_id() << ")";
        throw Exception(message.str());
    }
}

}
