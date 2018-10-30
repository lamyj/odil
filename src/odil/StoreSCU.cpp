/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
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

#include "odil/message/CStoreRequest.h"
#include "odil/message/CStoreResponse.h"
#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/logging.h"
#include "odil/registry.h"
#include "odil/SCU.h"

namespace odil
{

StoreSCU
::StoreSCU(Association & association)
: SCU(association)
{
    // Nothing else.
}

void 
StoreSCU
::set_affected_sop_class(std::shared_ptr<DataSet const> dataset)
{
    auto const & sop_class_uid = dataset->as_string(registry::SOPClassUID, 0);
    
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
::store(
    std::shared_ptr<DataSet> dataset,
    Value::String const & move_originator_ae_title ,
    Value::Integer move_originator_message_id ) const
{
    auto request = std::make_shared<message::CStoreRequest const>(
        this->_association.next_message_id(),
        this->_affected_sop_class,
        dataset->as_string(registry::SOPInstanceUID, 0),
        message::Message::Priority::MEDIUM,
        dataset, move_originator_ae_title,
        move_originator_message_id);
    this->_store(request);
}

void
StoreSCU
::_store(std::shared_ptr<message::CStoreRequest const> request) const
{
    this->_association.send_message(request, this->_affected_sop_class);
    
    auto response = std::make_shared<message::CStoreResponse const>(
        this->_association.receive_message());

    if(response->get_message_id_being_responded_to() != request->get_message_id())
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response MsgId: "
                << response->get_message_id_being_responded_to()
                << "(expected: " << request->get_message_id() << ")";
        throw Exception(message.str());
    }

    if(response->has_affected_sop_class_uid() &&
       response->get_affected_sop_class_uid() != request->get_affected_sop_class_uid())
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response Affected SOP Class UID: "
                << response->get_affected_sop_class_uid()
                << " (expected: " << request->get_affected_sop_class_uid() << ")";
        throw Exception(message.str());
    }
    if(response->has_affected_sop_instance_uid() &&
       response->get_affected_sop_instance_uid() != request->get_affected_sop_instance_uid())
    {
        std::ostringstream message;
        message << "DIMSE: Unexpected Response Affected SOP Instance UID: "
                << response->get_affected_sop_instance_uid()
                << " (expected: " << request->get_affected_sop_instance_uid() << ")";
        throw Exception(message.str());
    }

    if(message::Response::is_warning(response->get_status()))
    {
        ODIL_LOG(warning) << "C-STORE response status: " << response->get_status();
    }
    else if(message::Response::is_failure(response->get_status()))
    {
        ODIL_LOG(error) << "C-STORE response status: " << response->get_status();
    }
}

}
