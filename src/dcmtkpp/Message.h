/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _dcfa5213_ad7e_4194_8b4b_e630aa0df2e8
#define _dcfa5213_ad7e_4194_8b4b_e630aa0df2e8

#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/Association.h"

namespace dcmtkpp
{

/**
 * @brief Base class for all DIMSE messages.
 */
class Message
{
public:
    Message();
    virtual ~Message();
    
    /// @brief Return the command set of the message.
    DcmDataset & get_command_set();
    
    /// @brief Return the data set of the message, default to NULL.
    DcmDataset * get_data_set();
    
    /// @brief Set the data set of the message.
    void set_data_set(DcmDataset * data_set);
    
    Uint16 get_command_field() const;
    void set_command_field(Uint16 command_field);
    
    /**
     * @brief Send the message
     * @param association
     * @param abstract_syntax
     */
    void send(Association & association, std::string const & abstract_syntax) const;

protected:
    /// @brief Command set of the message.
    DcmDataset _command_set;
    
    /// @brief Data set of the message.
    DcmDataset * _data_set;
    
    /// @brief Find an accepted presentation context for the abstract syntax.
    static T_ASC_PresentationContextID _find_presentation_context(
        Association & association, std::string const & abstract_syntax);

private:
    static OFCondition sendDcmDataset(
        T_ASC_Association *assoc,
        DcmDataset *obj,
        T_ASC_PresentationContextID presID,
        E_TransferSyntax xferSyntax,
        DUL_DATAPDV pdvType,
        DIMSE_ProgressCallback callback,
        void *callbackContext);
};

}

#endif // _dcfa5213_ad7e_4194_8b4b_e630aa0df2e8
