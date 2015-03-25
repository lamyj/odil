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
#include <dcmtk/dcmdata/dcostrmb.h>
#include <dcmtk/dcmdata/dctagkey.h>
#include <dcmtk/dcmdata/dcwcache.h>
#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/Exception.h"

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
::_send(Message const & message, std::string const & abstract_syntax) const
{
    T_ASC_PresentationContextID const presentation_context = 
        this->_find_presentation_context(abstract_syntax);
    
    this->_sendDcmDataset(
        this->_association->get_association(), 
        const_cast<DcmDataset*>(&message.get_command_set()), 
        presentation_context, EXS_LittleEndianImplicit, 
        DUL_COMMANDPDV, NULL, NULL);
    if(message.get_data_set() != NULL && 
       !const_cast<DcmDataset*>(message.get_data_set())->isEmpty())
    {
        // TODO: progress callback
        // FIXME: transfer syntax
        this->_sendDcmDataset(
            this->_association->get_association(), 
            const_cast<DcmDataset*>(message.get_data_set()),
            presentation_context, EXS_LittleEndianImplicit, 
            DUL_DATASETPDV, NULL, NULL);
    }
}

Message
ServiceRole
::_receive(ProgressCallback callback, void* callback_data) const
{
    OFCondition condition;
    
    T_ASC_PresentationContextID presentation_context;
    T_DIMSE_Message dcmtk_message;
    DcmDataset * command_set;
    condition = DIMSE_receiveCommand(
        this->_association->get_association(), DIMSE_BLOCKING,
        this->_network->get_timeout(), 
        &presentation_context, &dcmtk_message,
        NULL, &command_set);
    if(condition.bad())
    {
        throw Exception(condition);
    }
    
    DcmDataset * data_set;
    
    Uint16 command_data_set_type;
    
    condition = command_set->findAndGetUint16(
        DcmTagKey(0x0000, 0x0800), command_data_set_type);
    if(condition.bad())
    {
        throw Exception(condition);
    }
    
    if(command_data_set_type == DIMSE_DATASET_PRESENT)
    {
        // Encapsulate the callback and its data
        ProgressCallbackData encapsulated;
        if(callback != NULL)
        {
            encapsulated.callback = callback;
            encapsulated.data = callback_data;
        }
        
        OFCondition const condition = DIMSE_receiveDataSetInMemory(
            this->_association->get_association(), DIMSE_BLOCKING, 
            this->_network->get_timeout(), 
            &presentation_context, &data_set, 
            (callback != NULL)?(ServiceRole::_progress_callback_wrapper):NULL, 
            (callback != NULL)?(&encapsulated):NULL
        );
        
        if(condition.bad())
        {
            throw Exception(condition);
        }
    }
    else if(command_data_set_type == DIMSE_DATASET_NULL)
    {
        data_set = NULL;
    }
    else
    {
        throw Exception("Unknown Command Data Set Type");
    }
    
    Message message(*command_set, data_set);
    
    return message;
}

std::pair<T_ASC_PresentationContextID, T_DIMSE_Message>
ServiceRole
::_receive_command(T_DIMSE_BlockingMode block_mode) const
{
    this->_check_dimse_ready();
    
    std::pair<T_ASC_PresentationContextID, T_DIMSE_Message> result;
    
    result.first = -1;
    memset(static_cast<void*>(&result.second), 0, sizeof(result.second));
    
    OFCondition const condition = DIMSE_receiveCommand(
        this->_association->get_association(), block_mode, 
        this->_network->get_timeout(), 
        &result.first, &result.second, 
        NULL /*statusDetail*/, NULL /*commandSet*/);
    
    if(condition.bad())
    {
        throw Exception(condition);
    }
    
    return result;
}

std::pair<T_ASC_PresentationContextID, DcmDataset *>
ServiceRole
::_receive_dataset(
    T_DIMSE_BlockingMode block_mode,
    ProgressCallback callback, void* callback_data) const
{
    this->_check_dimse_ready();
    
    std::pair<T_ASC_PresentationContextID, DcmDataset *> result;
    result.second = NULL;
    
    // Encapsulate the callback and its data
    ProgressCallbackData encapsulated;
    if(callback != NULL)
    {
        encapsulated.callback = callback;
        encapsulated.data = callback_data;
    }
    
    OFCondition const condition = DIMSE_receiveDataSetInMemory(
        this->_association->get_association(), block_mode, 
        this->_network->get_timeout(), 
        &result.first, &result.second, 
        (callback != NULL)?(ServiceRole::_progress_callback_wrapper):NULL, 
        (callback != NULL)?(&encapsulated):NULL
    );
    
    if(condition.bad())
    {
        throw Exception(condition);
    }
    
    return result;
}

OFCondition
ServiceRole
::_sendDcmDataset(
        T_ASC_Association *assoc,
        DcmDataset *obj,
        T_ASC_PresentationContextID presID,
        E_TransferSyntax xferSyntax,
        DUL_DATAPDV pdvType,
        DIMSE_ProgressCallback callback,
        void *callbackContext)
    /*
     * This function sends all information which is included in a DcmDataset object over
     * the network which is provided in assoc.
     *
     * Parameters:
     *   assoc           - [in] The association (network connection to another DICOM application).
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
    unsigned long bufLen = assoc->sendPDVLength;
    if (bufLen + 12 > dcmMaxOutgoingPDUSize.get())
    {
        bufLen = dcmMaxOutgoingPDUSize.get() - 12;
    }

    /* on the basis of the association's buffer, create a buffer variable that we can write to */
    DcmOutputBufferStream outBuf(assoc->sendPDVBuffer, bufLen);

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
            OFCondition const dulCond = DUL_WritePDVs(&assoc->DULassociation, &pdvList);
            if (dulCond.bad())
            {
                return makeDcmnetSubCondition(DIMSEC_SENDFAILED, OF_error, "DIMSE Failed to send message", dulCond);
            }

            /* count the bytes and the amount of PDVs which were transmitted */
            bytesTransmitted += OFstatic_cast(Uint32, rtnLength);

            /* execute callback function to indicate progress */
            if (callback)
            {
                callback(callbackContext, bytesTransmitted);
            }
        }
    }

    /* indicate the end of the transfer */
    obj->transferEnd();

    return EC_Normal;
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
