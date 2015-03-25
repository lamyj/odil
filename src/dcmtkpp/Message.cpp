/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Message.h"

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcostrmb.h>
#include <dcmtk/dcmdata/dcwcache.h>
#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

Message
::Message()
{
    this->set_data_set(NULL);
}

Message
::~Message()
{
    // Nothing to do.
}

DcmDataset & 
Message
::get_command_set()
{
    return this->_command_set;
}

DcmDataset *
Message
::get_data_set()
{
    return this->_data_set;
}

void
Message
::set_data_set(DcmDataset * data_set)
{
    this->_data_set = data_set;
    
    Uint16 command_dataset_type;
    if(data_set == NULL || data_set->isEmpty())
    {
        command_dataset_type = DIMSE_DATASET_NULL;
    }
    else
    {
        command_dataset_type = DIMSE_DATASET_PRESENT;
    }
    
    this->_command_set.putAndInsertUint16(
        DcmTagKey(0x0000, 0x0800), command_dataset_type);
}

Uint16 
Message
::get_command_field() const
{
    DcmDataset & command_set = const_cast<DcmDataset &>(this->_command_set);
    Uint16 command_field;
    
    OFCondition const condition = command_set.findAndGetUint16(
        DCM_CommandField, command_field);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

void 
Message
::set_command_field(Uint16 command_field)
{
    OFCondition const condition = this->_command_set.putAndInsertUint16(
        DCM_CommandField, command_field);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

void 
Message
::send(Association & association, std::string const & abstract_syntax) const
{
    T_ASC_PresentationContextID const presentation_context = 
        this->_find_presentation_context(association, abstract_syntax);
    
    Message::sendDcmDataset(
        association.get_association(), 
        const_cast<DcmDataset*>(&this->_command_set), 
        presentation_context, EXS_LittleEndianImplicit, 
        DUL_COMMANDPDV, NULL, NULL);
    if(this->_data_set != NULL && !this->_data_set->isEmpty())
    {
        // TODO: progress callback
        // FIXME: transfer syntax
        Message::sendDcmDataset(
            association.get_association(), 
            this->_data_set,
            presentation_context, EXS_LittleEndianImplicit, 
            DUL_DATASETPDV, NULL, NULL);
    }
}

T_ASC_PresentationContextID
Message
::_find_presentation_context(
    Association & association, std::string const & abstract_syntax)
{
    T_ASC_PresentationContextID const presentation_id = 
        ASC_findAcceptedPresentationContextID(
            association.get_association(), 
            abstract_syntax.c_str());
    if(presentation_id == 0) 
    {
        throw Exception("No Presentation Context for Get Operation");
    }
    
    return presentation_id;
}

OFCondition
Message
::sendDcmDataset(
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
    OFCondition dulCond = EC_Normal;
    OFCondition econd = EC_Normal;
    unsigned char *buf;
    unsigned long bufLen;
    OFBool last = OFFalse;
    OFBool written = OFFalse;
    offile_off_t rtnLength;
    Uint32 bytesTransmitted = 0;
    DUL_PDVLIST pdvList;
    DUL_PDV pdv;
    /* the following variable is currently unused, leave it for future use */
    unsigned long pdvCount = 0;
    DcmWriteCache wcache;

    /* initialize some local variables (we want to use the association's send buffer */
    /* to store data) this buffer can only take a certain number of elements */
    buf = assoc->sendPDVBuffer;
    bufLen = assoc->sendPDVLength;

    /* we may wish to restrict output PDU size */
    Uint32 maxpdulen = dcmMaxOutgoingPDUSize.get();

    /* max PDV size is max PDU size minus 12 bytes PDU/PDV header */
    if (bufLen + 12 > maxpdulen)
    {
      bufLen = maxpdulen - 12;
    }

    /* on the basis of the association's buffer, create a buffer variable that we can write to */
    DcmOutputBufferStream outBuf(buf, bufLen);

    /* prepare all elements in the DcmDataset variable for transfer */
    obj->transferInit();

    /* initialize two more variables: groupLength_encoding specifies what will be done concerning */
    /* group length tags, sequenceType_encoding specifies how sequences will be handled */
    E_GrpLenEncoding groupLength_encoding = g_dimse_send_groupLength_encoding;
    E_EncodingType sequenceType_encoding = g_dimse_send_sequenceType_encoding;

    /* Mind that commands must always include group length (0000,0000) and */
    /* that commands do not contain sequences, yet */
    if (pdvType == DUL_COMMANDPDV)
        groupLength_encoding = EGL_withGL;

    /* start a loop: in each iteration information from the DcmDataset object (i.e. infor- */
    /* mation which shall be sent) will be set in the buffer (we need more than one itera- */
    /* tion if there is more information than the buffer can take at a time), a PDV object */
    /* with the buffer's data will be created and assigned to a list, and finally the */
    /* list's information will be sent over the network to the other DICOM application. */
    while (!last)
    {
        /* write data values which are contained in the DcmDataSet variable to the above created */
        /* buffer. Mind the transfer syntax, the sequence type encoding, the group length encoding */
        /* and remove all padding data elements. Depending on whether all information has been written */
        /* to the buffer, update the variable that determines the end of the while loop. (Note that */
        /* DcmDataset stores information about what of its content has already been sent to the buffer.) */
        if (! written)
        {
          econd = obj->write(outBuf, xferSyntax, sequenceType_encoding, &wcache,
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

        if (written) outBuf.flush(); // flush stream including embedded compression codec.

        /* get buffer and its length, assign to local variable */
        void *fullBuf = NULL;
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
                return makeDcmnetCondition(DIMSEC_SENDFAILED, OF_error,
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
            pdv.fragmentLength = OFstatic_cast(unsigned long, rtnLength);
            pdv.presentationContextID = presID;
            pdv.pdvType = pdvType;
            pdv.lastPDV = last;
            pdv.data = fullBuf;

            /* append this PDV to a PDV list structure, set the counter variable */
            /* to 1 since this structure contains only 1 element */
            pdvList.count = 1;
            pdvList.pdv = &pdv;

            /* dump some information if required */
            //DCMNET_TRACE("DIMSE sendDcmDataset: sending " << pdv.fragmentLength << " bytes");

            /* send information over the network to the other DICOM application */
            dulCond = DUL_WritePDVs(&assoc->DULassociation, &pdvList);
            if (dulCond.bad())
                return makeDcmnetSubCondition(DIMSEC_SENDFAILED, OF_error, "DIMSE Failed to send message", dulCond);

            /* count the bytes and the amount of PDVs which were transmitted */
            bytesTransmitted += OFstatic_cast(Uint32, rtnLength);
            pdvCount += pdvList.count;

            /* execute callback function to indicate progress */
            if (callback) {
                callback(callbackContext, bytesTransmitted);
            }
        }
    }

    /* indicate the end of the transfer */
    obj->transferEnd();

    return EC_Normal;
}

}
