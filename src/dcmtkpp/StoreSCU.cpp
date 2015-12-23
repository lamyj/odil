/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "StoreSCU.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include "dcmtkpp/message/CStoreRequest.h"
#include "dcmtkpp/message/CStoreResponse.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/SCU.h"

namespace dcmtkpp
{

StoreSCU
::StoreSCU(Association & association)
: SCU(association)
{
    // Nothing else.
}

StoreSCU
::~StoreSCU()
{
    // Nothing to do.
}

void 
StoreSCU
::set_affected_sop_class(DataSet const & dataset)
{
    auto const & sop_class_uid = dataset.as_string(registry::SOPClassUID, 0);
    
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
StoreSCU
::store(DataSet const & dataset) const
{
    message::CStoreRequest const request(
        this->_association.next_message_id(),
        this->_affected_sop_class,
        dataset.as_string(registry::SOPInstanceUID, 0),
        message::Message::Priority::MEDIUM,
        dataset);
    this->_association.send_message(request, this->_affected_sop_class);
    
    message::CStoreResponse const response = this->_association.receive_message();

    if(response.get_message_id_being_responded_to() != request.get_message_id())
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response MsgId: "
                << response.get_message_id_being_responded_to()
                << "(expected: " << request.get_message_id() << ")";
        throw Exception(message.str());
    }

    if(response.has_affected_sop_class_uid() &&
       response.get_affected_sop_class_uid() != request.get_affected_sop_class_uid())
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response Affected SOP Class UID: "
                << response.get_affected_sop_class_uid()
                << " (expected: " << request.get_affected_sop_class_uid() << ")";
        throw Exception(message.str());
    }
    if(response.has_affected_sop_instance_uid() &&
       response.get_affected_sop_instance_uid() != request.get_affected_sop_instance_uid())
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response Affected SOP Instance UID: "
                << response.get_affected_sop_instance_uid()
                << " (expected: " << request.get_affected_sop_instance_uid() << ")";
        throw Exception(message.str());
    }
}

}
