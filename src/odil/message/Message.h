/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _dcfa5213_ad7e_4194_8b4b_e630aa0df2e8
#define _dcfa5213_ad7e_4194_8b4b_e630aa0df2e8

#include "odil/DataSet.h"
#include "odil/odil.h"
#include "odil/registry.h"
#include "odil/Value.h"

namespace odil
{

namespace message
{

#define ODIL_MESSAGE_MANDATORY_FIELD_MACRO(name, tag, TValueType, function) \
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

#define ODIL_MESSAGE_OPTIONAL_FIELD_MACRO(name, tag, TValueType, function) \
    ODIL_MESSAGE_MANDATORY_FIELD_MACRO(name, tag, TValueType, function) \
    bool has_##name() const \
    { \
        return this->_command_set.has(tag);; \
    } \
    void delete_##name() \
    { \
        this->_command_set.remove(tag); \
    }

#define ODIL_MESSAGE_SET_OPTIONAL_FIELD_MACRO(dataset, name, tag, function) \
    if(dataset.has(tag)) \
    { \
        this->set_##name(dataset.function(tag, 0)); \
    }

#define ODIL_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(name, tag) \
    ODIL_MESSAGE_MANDATORY_FIELD_MACRO(name, tag, Value::Integer, as_int)

#define ODIL_MESSAGE_MANDATORY_FIELD_STRING_MACRO(name, tag) \
    ODIL_MESSAGE_MANDATORY_FIELD_MACRO(name, tag, Value::String, as_string)

#define ODIL_MESSAGE_OPTIONAL_FIELD_INTEGER_MACRO(name, tag) \
    ODIL_MESSAGE_OPTIONAL_FIELD_MACRO(name, tag, Value::Integer, as_int)

#define ODIL_MESSAGE_OPTIONAL_FIELD_STRING_MACRO(name, tag) \
    ODIL_MESSAGE_OPTIONAL_FIELD_MACRO(name, tag, Value::String, as_string)

/**
 * @brief Base class for all DIMSE messages.
 */
class ODIL_API Message
{
public:
    struct Command
    {
        enum Type
        {
            C_STORE_RQ = 0x0001,
            C_STORE_RSP = 0x8001,

            C_FIND_RQ = 0x0020,
            C_FIND_RSP = 0x8020,

            C_CANCEL_RQ = 0x0FFF,

            C_GET_RQ = 0x0010,
            C_GET_RSP = 0x8010,

            C_MOVE_RQ = 0x0021,
            C_MOVE_RSP = 0x8021,

            C_ECHO_RQ = 0x0030,
            C_ECHO_RSP = 0x8030,

            N_EVENT_REPORT_RQ = 0x0100,
            N_EVENT_REPORT_RSP = 0x8100,

            N_GET_RQ = 0x0110,
            N_GET_RSP = 0x8110,

            N_SET_RQ = 0x0120,
            N_SET_RSP = 0x8120,

            N_ACTION_RQ = 0x0130,
            N_ACTION_RSP = 0x8130,

            N_CREATE_RQ = 0x0140,
            N_CREATE_RSP = 0x8140,

            N_DELETE_RQ = 0x0150,
            N_DELETE_RSP = 0x8150,
        };
    };

    struct Priority
    {
        enum Type
        {
            LOW = 0x0002,
            MEDIUM = 0x0000,
            HIGH = 0x0001,
        };
    };

    struct DataSetType
    {
        enum Type
        {
            PRESENT = 0x0000,
            ABSENT = 0x0101,
        };
    };

    /// @brief Create a message with an empty command set and an empty data set.
    Message();

    /// @brief Create a message from existing data.
    Message(DataSet const & command_set);

    /// @brief Create a message from existing data.
    Message(DataSet && command_set);

    /// @brief Create a message from existing data.
    Message(DataSet const & command_set, DataSet const & data_set);

    /// @brief Create a message from existing data.
    Message(DataSet && command_set, DataSet && data_set);

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

    /**
     * @brief Return the data set of the message, raise an exception if no
     * data set is present.
     */
    DataSet & get_data_set();
    
    /// @brief Set the data set of the message.
    void set_data_set(DataSet const & data_set);

    /// @brief Set the data set of the message.
    void set_data_set(DataSet && data_set);

    /// @brief Delete the data set in this message.
    void delete_data_set();
    
    ODIL_MESSAGE_MANDATORY_FIELD_INTEGER_MACRO(
        command_field, registry::CommandField)

protected:
    /// @brief Command set of the message.
    DataSet _command_set;
    
    /// @brief Data set of the message.
    DataSet _data_set;
};

}

}

#endif // _dcfa5213_ad7e_4194_8b4b_e630aa0df2e8
