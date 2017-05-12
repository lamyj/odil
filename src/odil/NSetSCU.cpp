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

    this->SCU::set_affected_sop_class(sop_class_uid);
}

void 
NSetSCU
::set( DataSet const & dataset) const
{

    message::NSetRequest const request(
        this->_association.next_message_id(),
        this->_affected_sop_class,
        dataset.as_string(registry::RequestedSOPInstanceUID, 0),
        dataset);

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
