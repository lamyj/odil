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
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcistrmb.h>
#include <dcmtk/dcmdata/dcostrmb.h>
#include <dcmtk/dcmdata/dctagkey.h>
#include <dcmtk/dcmdata/dcwcache.h>
#include <dcmtk/dcmdata/dcxfer.h>
#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/conversion.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Reader.h"
#include "dcmtkpp/registry.h"

namespace dcmtkpp
{

ServiceRole
::ServiceRole()
: _association(NULL), _network(NULL)
{
    // Nothing else
}

ServiceRole
::ServiceRole(ServiceRole const & other)
: _association(other._association), _network(other._network)
{
    // Nothing else
}

ServiceRole const &
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
    Message const & message, std::string const & abstract_syntax,
    ProgressCallback callback, void* callback_data) const
{
    T_ASC_PresentationContextID const presentation_context = 
        this->_find_presentation_context(abstract_syntax);
    
    DcmDataset * command_set = dynamic_cast<DcmDataset*>(
        convert(message.get_command_set()));

    this->_send(
        command_set,
        presentation_context, EXS_LittleEndianImplicit, 
        DUL_COMMANDPDV, NULL, NULL);
    if(message.has_data_set() && !message.get_data_set().empty())
    {
        DcmDataset * data_set = dynamic_cast<DcmDataset*>(
            convert(message.get_data_set()));
        // FIXME: transfer syntax
        this->_send(
            data_set,
            presentation_context, EXS_LittleEndianImplicit, 
            DUL_DATASETPDV, callback, callback_data);
        delete data_set;
    }

    delete command_set;
}

Message
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
    
    return has_data_set?Message(command_set, data_set):Message(command_set);
}

OFCondition
ServiceRole
::_send(
    DcmDataset *obj, T_ASC_PresentationContextID presID,
    E_TransferSyntax xferSyntax, DUL_DATAPDV pdvType,
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
    OFBool written = OFFalse;
    DcmWriteCache wcache;

    /* we may wish to restrict output PDU size */
    /* max PDV size is max PDU size minus 12 bytes PDU/PDV header */
    unsigned long bufLen = this->_association->get_association()->sendPDVLength;
    if (bufLen + 12 > dcmMaxOutgoingPDUSize.get())
    {
        bufLen = dcmMaxOutgoingPDUSize.get() - 12;
    }

    /* on the basis of the association's buffer, create a buffer variable that we can write to */
    DcmOutputBufferStream outBuf(
        this->_association->get_association()->sendPDVBuffer, bufLen);

    /* prepare all elements in the DcmDataset variable for transfer */
    obj->transferInit();

    /* groupLength_encoding specifies what will be done concerning
     * group length tags
     */
    E_GrpLenEncoding groupLength_encoding = g_dimse_send_groupLength_encoding;
    /* Mind that commands must always include group length (0000,0000) and */
    /* that commands do not contain sequences, yet */
    if (pdvType == DUL_COMMANDPDV)
    {
        groupLength_encoding = EGL_withGL;
    }

    /* sequenceType_encoding specifies how sequences will be handled */
    E_EncodingType const sequenceType_encoding = g_dimse_send_sequenceType_encoding;

    /* start a loop: in each iteration information from the DcmDataset object (i.e. infor- */
    /* mation which shall be sent) will be set in the buffer (we need more than one itera- */
    /* tion if there is more information than the buffer can take at a time), a PDV object */
    /* with the buffer's data will be created and assigned to a list, and finally the */
    /* list's information will be sent over the network to the other DICOM application. */
    OFBool last = OFFalse;
    Uint32 bytesTransmitted = 0;
    while (!last)
    {
        /* write data values which are contained in the DcmDataSet variable to the above created */
        /* buffer. Mind the transfer syntax, the sequence type encoding, the group length encoding */
        /* and remove all padding data elements. Depending on whether all information has been written */
        /* to the buffer, update the variable that determines the end of the while loop. (Note that */
        /* DcmDataset stores information about what of its content has already been sent to the buffer.) */
        if (! written)
        {
            OFCondition const econd =
                obj->write(outBuf, xferSyntax, sequenceType_encoding, &wcache,
                groupLength_encoding, EPD_withoutPadding);
            if (econd == EC_Normal)                   /* all contents have been written to the buffer */
            {
                written = OFTrue;
            }
            else if (econd == EC_StreamNotifyClient)  /* no more space in buffer, _not_ all elements have been written to it */
            {
                // nothing to do
            }
            else                                      /* some error has occurred */
            {
                //DCMNET_WARN(DIMSE_warn_str(assoc) << "writeBlock Failed (" << econd.text() << ")");
                return DIMSE_SENDFAILED;
            }
        }

        if (written)
        {
            outBuf.flush(); // flush stream including embedded compression codec.
        }

        /* get buffer and its length, assign to local variable */
        void *fullBuf = NULL;
        offile_off_t rtnLength;
        outBuf.flushBuffer(fullBuf, rtnLength);

        last = written && outBuf.isFlushed();

        /* if the buffer is not empty, do something with its contents */
        if (rtnLength > 0)
        {
            /* rtnLength could be odd */
            if (rtnLength & 1)
            {
                /* this should only happen if we use a stream compressed transfer
                 * syntax and then only at the very end of the stream. Everything
                 * else is a failure.
                 */
                if (!last)
                {
                    return makeDcmnetCondition(
                        DIMSEC_SENDFAILED, OF_error,
                        "DIMSE Failed to send message: odd block length encountered");
                }

                /* since the block size is always even, block size must be larger
                 * than rtnLength, so we can safely add a pad byte (and hope that
                 * the pad byte will not confuse the receiver's decompressor).
                 */
                unsigned char *cbuf = (unsigned char *)fullBuf;
                cbuf[rtnLength++] = 0; // add zero pad byte
            }

            /* initialize a DUL_PDV variable with the buffer's data */
            DUL_PDV pdv;
            pdv.fragmentLength = OFstatic_cast(unsigned long, rtnLength);
            pdv.presentationContextID = presID;
            pdv.pdvType = pdvType;
            pdv.lastPDV = last;
            pdv.data = fullBuf;

            /* append this PDV to a PDV list structure, set the counter variable */
            /* to 1 since this structure contains only 1 element */
            DUL_PDVLIST pdvList;
            pdvList.count = 1;
            pdvList.pdv = &pdv;

            /* send information over the network to the other DICOM application */
            OFCondition const dulCond = DUL_WritePDVs(
                &this->_association->get_association()->DULassociation,
                &pdvList);
            if (dulCond.bad())
            {
                return makeDcmnetSubCondition(DIMSEC_SENDFAILED, OF_error, "DIMSE Failed to send message", dulCond);
            }

            /* count the bytes and the amount of PDVs which were transmitted */
            bytesTransmitted += OFstatic_cast(Uint32, rtnLength);

            /* execute callback function to indicate progress */
            if(callback)
            {
                callback(callbackContext, bytesTransmitted);
            }
        }
    }

    /* indicate the end of the transfer */
    obj->transferEnd();

    return EC_Normal;
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
            throw Exception("Unkown PDV type");
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
