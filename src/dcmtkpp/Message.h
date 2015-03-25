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
#include <dcmtk/ofstd/oftypes.h>

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
    DcmDataset const & get_command_set() const;
    
    /// @brief Return the data set of the message, default to NULL.
    DcmDataset const * get_data_set() const;
    
    /// @brief Set the data set of the message.
    void set_data_set(DcmDataset * data_set);
    
    Uint16 get_command_field() const;
    void set_command_field(Uint16 command_field);

protected:
    /// @brief Command set of the message.
    DcmDataset _command_set;
    
    /// @brief Data set of the message.
    DcmDataset * _data_set;
};

}

#endif // _dcfa5213_ad7e_4194_8b4b_e630aa0df2e8
