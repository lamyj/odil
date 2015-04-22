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
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/ofstd/oftypes.h>

#include <dcmtkpp/ElementAccessor.h>
#include <dcmtkpp/ElementTraits.h>

namespace dcmtkpp
{

#define DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(name, tag, TValueType) \
    /** @brief Return the tag element of the command set. */ \
    TValueType get_##name() const \
    { \
        return ElementAccessor<TValueType>::get(this->_command_set, tag); \
    } \
    /** @brief Set the tag element of the command set. */ \
    void set_##name(TValueType const & value) \
    { \
        return ElementAccessor<TValueType>::set(this->_command_set, tag, value); \
    }

#define DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(name, tag, TValueType) \
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(name, tag, TValueType) \
    bool has_##name() const \
    { \
        return ElementAccessor<TValueType>::has(this->_command_set, tag); \
    } \
    void delete_##name() \
    { \
        this->_command_set.findAndDeleteElement(tag); \
    }

#define DCMTKPP_MESSAGE_SET_OPTIONAL_FIELD_MACRO(dataset, name, tag, TValueType) \
    if(ElementAccessor<TValueType>::has(dataset, tag)) \
    { \
        this->set_##name(ElementAccessor<TValueType>::get(dataset, tag)); \
    }

/**
 * @brief Base class for all DIMSE messages.
 */
class Message
{
public:
    /// @brief Create a message with an empty command set and an empty data set.
    Message();

    /// @brief Create a message from existing data.
    Message(DcmDataset const & command_set, DcmDataset * data_set=NULL);

    /// @brief Destructor;
    virtual ~Message();
    
    /// @brief Return the command set of the message.
    DcmDataset const & get_command_set() const;
    
    /// @brief Return the data set of the message, default to NULL.
    DcmDataset const * get_data_set() const;
    
    /// @brief Set the data set of the message.
    void set_data_set(DcmDataset const * data_set);

    /// @brief Delete the data set in this message.
    void delete_data_set();
    
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(command_field, DCM_CommandField, Uint16)

protected:
    /// @brief Command set of the message.
    DcmDataset _command_set;
    
    /// @brief Data set of the message.
    DcmDataset const * _data_set;
};

}

#endif // _dcfa5213_ad7e_4194_8b4b_e630aa0df2e8
