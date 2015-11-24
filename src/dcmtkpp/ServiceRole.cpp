/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ServiceRole.h"

#include <unistd.h>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Reader.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Writer.h"

namespace dcmtkpp
{

ServiceRole
::ServiceRole()
: _network(NULL), _association(NULL)
{
    // Nothing else
}

ServiceRole
::ServiceRole(Network * network, Association * association)
{
    this->set_network(network);
    this->set_association(association);
}

ServiceRole
::ServiceRole(ServiceRole const & other)
: _network(other._network), _association(other._association)
{
    // Nothing else
}

ServiceRole &
ServiceRole
::operator=(ServiceRole const & other)
{
    if(this != &other)
    {
        this->set_association(other.get_association());
        this->set_network(other.get_network());
    }
    
    return *this;
}

ServiceRole
::~ServiceRole()
{
    // Nothing to do.
}

Network *
ServiceRole
::get_network() const
{
    return this->_network;
}

void
ServiceRole
::set_network(Network * network)
{
    this->_network = network;
}

Association *
ServiceRole
::get_association() const
{
    return this->_association;
}

void
ServiceRole
::set_association(Association * association)
{
    this->_association = association;
}

void 
ServiceRole
::_progress_callback_wrapper(void * data, unsigned long bytes_count)
{
    ProgressCallbackData * encapsulated = 
        reinterpret_cast<ProgressCallbackData*>(data);
    encapsulated->callback(encapsulated->data, bytes_count);
}

T_ASC_PresentationContextID
ServiceRole
::_find_presentation_context(std::string const & abstract_syntax) const
{
    T_ASC_PresentationContextID const presentation_id = 
        ASC_findAcceptedPresentationContextID(
            this->_association->get_association(), 
            abstract_syntax.c_str());
    if(presentation_id == 0) 
    {
        throw Exception("No Presentation Context for Get Operation");
    }
    
    return presentation_id;
}

void
ServiceRole
::_send(
    message::Message const & message, std::string const & abstract_syntax,
    ProgressCallback callback, void* callback_data) const
{
    T_ASC_PresentationContextID const presentation_context = 
        this->_find_presentation_context(abstract_syntax);

    this->_send(
        message.get_command_set(),
        presentation_context, registry::ImplicitVRLittleEndian,
        DUL_COMMANDPDV, NULL, NULL);
    if(message.has_data_set() && !message.get_data_set().empty())
    {
        // FIXME: transfer syntax
        this->_send(
            message.get_data_set(),
            presentation_context, registry::ImplicitVRLittleEndian,
            DUL_DATASETPDV, callback, callback_data);
    }
}

message::Message
ServiceRole
::_receive(ProgressCallback callback, void* callback_data) const
{
    // Receive command set
    auto const command = this->_receive_dataset(callback, callback_data);
    if(command.second != DUL_COMMANDPDV)
    {
        throw Exception("Did not receive command set");
    }
    DataSet const & command_set = command.first;
    
    // Receive potential data set
    DataSet data_set;
    bool has_data_set;
    if(command_set.as_int(registry::CommandDataSetType, 0) != DIMSE_DATASET_NULL)
    {
        auto const data = this->_receive_dataset(callback, callback_data);
        if(data.second != DUL_DATASETPDV)
        {
            throw Exception("Did not receive data set");
        }
        data_set = data.first;
        has_data_set = true;
    }
    else
    {
        has_data_set = false;
    }
    
    return (
        has_data_set?
        message::Message(command_set, data_set):message::Message(command_set));
}

void
ServiceRole
::_send(
    DataSet const & obj, T_ASC_PresentationContextID presID,
    std::string const & transfer_syntax, DUL_DATAPDV pdvType,
    ProgressCallback callback, void *callbackContext) const
    /*
     * This function sends all information which is included in a DcmDataset object over
     * the network which is provided in assoc.
     *
     * Parameters:
     *   obj             - [in] Contains the information which shall be sent over the network.
     *   presId          - [in] The ID of the presentation context which shall be used
     *   xferSyntax      - [in] The transfer syntax which shall be used.
     *   pdvType         - [in] Specifies if the information in this DcmDataset object belongs to
     *                          a DIMSE command (as for example C-STORE) (DUL_COMMANDPDV) or if
     *                          the information is actual instance information (DUL_DATASETPDV).
     *   callback        - [in] Pointer to a function which shall be called to indicate progress.
     *   callbackContext - []
     */
{
    bool const use_group_length = (pdvType == DUL_COMMANDPDV);
    std::stringstream stream;
    Writer writer(
        stream, transfer_syntax, Writer::ItemEncoding::ExplicitLength,
        use_group_length);
    writer.write_data_set(obj);
    std::string const data = stream.str();

    /* we may wish to restrict output PDU size */
    /* max PDV size is max PDU size minus 12 bytes PDU/PDV header */
    unsigned long bufLen = this->_association->get_association()->sendPDVLength;
    if (bufLen + 12 > dcmMaxOutgoingPDUSize.get())
    {
        bufLen = dcmMaxOutgoingPDUSize.get() - 12;
    }

    bool done = false;
    unsigned long bytesTransmitted=0;
    while(!done)
    {
        std::string const buffer = data.substr(bytesTransmitted, bufLen);

        /* count the bytes and the amount of PDVs which were transmitted */
        bytesTransmitted += buffer.size();
        done = (bytesTransmitted>=data.size());

        /* initialize a DUL_PDV variable with the buffer's data */
        DUL_PDV pdv;
        pdv.fragmentLength = buffer.size();
        pdv.presentationContextID = presID;
        pdv.pdvType = pdvType;
        pdv.lastPDV = done;
        pdv.data = reinterpret_cast<void*>(const_cast<char*>(&buffer[0]));

        /* append this PDV to a PDV list structure, set the counter variable */
        /* to 1 since this structure contains only 1 element */
        DUL_PDVLIST pdvList;
        pdvList.count = 1;
        pdvList.pdv = &pdv;

        /* send information over the network to the other DICOM application */
        OFCondition const dulCond = DUL_WritePDVs(
            &this->_association->get_association()->DULassociation, &pdvList);
        if (dulCond.bad())
        {
            throw Exception(
                makeDcmnetSubCondition(
                    DIMSEC_SENDFAILED, OF_error, "DIMSE Failed to send message",
                    dulCond));
        }

        /* execute callback function to indicate progress */
        if(callback)
        {
            callback(callbackContext, bytesTransmitted);
        }
    }
}


std::pair<DataSet, DUL_DATAPDV>
ServiceRole::_receive_dataset(
    ProgressCallback callback, void *callbackContext) const
{
    DataSet data_set;

    std::stringstream stream;

    /* start a loop in which we want to read a DIMSE command from the incoming socket stream. */
    /* Since the command could stretch over more than one PDU, the use of a loop is mandatory. */
    DUL_DATAPDV type;
    bool last = false;
    DIC_UL pdvCount = 0;
    T_ASC_PresentationContextID pid = 0;
    while(!last)
    {
        DUL_PDV const pdv = this->_read_next_pdv();

        /* if this is the first loop iteration, get the presentation context ID
         * which is captured in the current PDV. If this is not the first loop
         * iteration, check if the presentation context IDs in the current PDV
         * and in the last PDV are identical. If they are not, return an error.
         */
        if (pdvCount == 0)
        {
            pid = pdv.presentationContextID;
        }
        else if (pdv.presentationContextID != pid)
        {
            std::ostringstream message;
            message << "Different presentation IDs inside Command Set: "
                    << pid << " != " << pdv.presentationContextID;
            throw Exception(message.str());
        }

        /* check if the fragment length of the current PDV is odd. This should */
        /* never happen (see DICOM standard (year 2000) part 7, annex F) (or */
        /* the corresponding section in a later version of the standard.) */
        if ((pdv.fragmentLength % 2) != 0)
        {
            /* This should NEVER happen.  See Part 7, Annex F. */
            std::ostringstream message;
            message << "Odd fragment length: " << pdv.fragmentLength;
            throw Exception(message.str());
        }

        /* if information is contained the PDVs fragment, we want to insert
         * this information into the buffer
         */
        stream.write(reinterpret_cast<char *>(pdv.data), pdv.fragmentLength);

        std::string transfer_syntax;
        bool keep_group_length;
        if(pdv.pdvType == DUL_COMMANDPDV)
        {
            /* DIMSE commands are always specified in the little endian implicit
             * transfer syntax. Additionally, we want to remove group length
             * tags.
             */
            transfer_syntax = registry::ImplicitVRLittleEndian;
            keep_group_length = false;
        }
        else if(pdv.pdvType == DUL_DATASETPDV)
        {
            /* figure out if is this a valid presentation context */
            T_ASC_PresentationContext pc;
            OFCondition const cond =
                ASC_findAcceptedPresentationContext(
                    this->_association->get_association()->params, pid, &pc);
            if (cond.bad())
            {
                throw Exception("No valid presentation context");
            }

            /* determine the transfer syntax which is specified in the presentation context */
            transfer_syntax = pc.acceptedTransferSyntax;
            keep_group_length = true;
        }
        else
        {
            throw Exception("Unknown PDV type");
        }

        Reader reader(stream, transfer_syntax, keep_group_length);
        data_set = reader.read_data_set();

        /* update the following variables which will be evaluated at the beginning of each loop iteration. */
        last = pdv.lastPDV;
        type = pdv.pdvType;

        /* update the counter that counts how many PDVs were received on the incoming */
        /* socket stream. This variable will be used for determining the first */
        /* loop iteration and dumping general information. */
        pdvCount++;
    }

    return std::make_pair(data_set, type);
}

DUL_PDV
ServiceRole
::_read_next_pdv() const
    /*
     * This function returns the next PDV which was (earlier or just now) received on the incoming
     * socket stream. If there are no PDVs (which were already received earlier) waiting to be picked
     * up, this function will go ahead and read a new PDU (containing one or more new PDVs) from the
     * incoming socket stream.
     */
{
    /* get the next PDV from the association, in case there are still some PDVs waiting to be picked up */
    DUL_PDV pdv;
    OFCondition cond = DUL_NextPDV(
        &this->_association->get_association()->DULassociation, &pdv);

    if (cond.bad())
    {
        /* in case DUL_NextPDV(...) did not return DUL_NORMAL, the association */
        /* did not contain any more PDVs that are waiting to be picked up. Hence, */
        /* we need to read new PDVs from the incoming socket stream. */

        /* if the blocking mode is DIMSE_NONBLOCKING and there is no data waiting after timeout seconds, report an error */
        if(!ASC_dataWaiting(
            this->_association->get_association(), this->_network->get_timeout()))
        {
            throw Exception(DIMSE_NODATAAVAILABLE);
        }

        /* try to receive new PDVs on the incoming socket stream (in detail, try to receive one PDU) */
        cond = DUL_ReadPDVs(
            &this->_association->get_association()->DULassociation, NULL,
            DUL_BLOCK, this->_network->get_timeout());

        /* check return value, if it is different from DUL_PDATAPDUARRIVED, an error occurred */
        if (cond != DUL_PDATAPDUARRIVED)
        {
            if (cond == DUL_NULLKEY || cond == DUL_ILLEGALKEY)
            {
                throw Exception(DIMSE_ILLEGALASSOCIATION);
            }
            else if (cond == DUL_PEERREQUESTEDRELEASE ||
                cond == DUL_PEERABORTEDASSOCIATION)
            {
                throw Exception(cond);
            }
            else
            {
                throw Exception(
                    makeDcmnetSubCondition(
                        DIMSEC_READPDVFAILED, OF_error,
                        "DIMSE Read PDV failed", cond));
            }
        }

        /* get the next PDV, assign it to pdv */
        cond = DUL_NextPDV(
            &this->_association->get_association()->DULassociation, &pdv);
        if (cond.bad())
        {
            throw Exception(
                makeDcmnetSubCondition(
                    DIMSEC_READPDVFAILED, OF_error,
                    "DIMSE Read PDV failed", cond));
        }
    }

    return pdv;
}

void
ServiceRole
::_check_dimse_ready() const
{
    if(this->_network == NULL)
    {
        throw Exception("No network");
    }
    else if(!this->_network->is_initialized())
    {
        throw Exception("Network is not initialized");
    }
    else if(this->_association == NULL)
    {
        throw Exception("No association");
    }
    else if(!this->_association->is_associated())
    {
        throw Exception("Not associated");
    }
}

}
