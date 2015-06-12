/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _dcfa5213_ad7e_4194_8b4b_e630aa0df2e8
#define _dcfa5213_ad7e_4194_8b4b_e630aa0df2e8

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

#define DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(name, tag, TValueType, function) \
    /** @brief Return the tag element of the command set. */ \
    TValueType const & get_##name() const \
    { \
        auto const & data = this->_command_set.function(tag); \
        if(data.empty()) \
        { \
            throw Exception("Empty element"); \
        } \
        return data[0]; \
    } \
    /** @brief Set the tag element of the command set. */ \
    void set_##name(TValueType const & value) \
    { \
        if(!this->_command_set.has(tag)) \
        { \
            this->_command_set.add(tag); \
        } \
        this->_command_set.function(tag) = { value }; \
    }

#define DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(name, tag, TValueType, function) \
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(name, tag, TValueType, function) \
    bool has_##name() const \
    { \
        return this->_command_set.has(tag);; \
    } \
    void delete_##name() \
    { \
        this->_command_set.remove(tag); \
    }

#define DCMTKPP_MESSAGE_SET_OPTIONAL_FIELD_MACRO(dataset, name, tag, function) \
    if(dataset.has(tag)) \
    { \
        this->set_##name(dataset.function(tag, 0)); \
    }

#define DCMTKPP_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(name, tag) \
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(name, tag, Value::Integer, as_int)

#define DCMTKPP_MESSAGE_MANDATORY_FIELD_STRING_MACRO(name, tag) \
    DCMTKPP_MESSAGE_MANDATORY_FIELD_MACRO(name, tag, Value::String, as_string)

#define DCMTKPP_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(name, tag) \
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(name, tag, Value::Integer, as_int)

#define DCMTKPP_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(name, tag) \
    DCMTKPP_MESSAGE_OPTIONAL_FIELD_MACRO(name, tag, Value::String, as_string)

/**
 * @brief Base class for all DIMSE messages.
 */
class Message
{
public:
    /// @brief Create a message with an empty command set and an empty data set.
    Message();

    /// @brief Create a message from existing data.
    Message(DataSet const & command_set);

    /// @brief Create a message from existing data.
    Message(DataSet const & command_set, DataSet const & data_set);

    /// @brief Destructor;
    virtual ~Message();
    
    /// @brief Return the command set of the message.
    DataSet const & get_command_set() const;
    
    /// @brief Test whether as data set is present in the message.
    bool has_data_set() const;

    /**
     * @brief Return the data set of the message, raise an exception if no
     * data set is present.
     */
    DataSet const & get_data_set() const;
    
    /// @brief Set the data set of the message.
    void set_data_set(DataSet const & data_set);

    /// @brief Delete the data set in this message.
    void delete_data_set();
    
    DCMTKPP_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(
        command_field, registry::CommandField)

protected:
    /// @brief Command set of the message.
    DataSet _command_set;
    
    /// @brief Data set of the message.
    DataSet _data_set;
};

}

#endif // _dcfa5213_ad7e_4194_8b4b_e630aa0df2e8
