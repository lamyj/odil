#ifndef _779c46d6_b6ea_443a_9642_f1ec5b87d4b3
#define _779c46d6_b6ea_443a_9642_f1ec5b87d4b3

#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/message/Message.h"

/// @brief Base class for fixtures of Message-derived classes.
template<typename TMessage>
struct MessageFixtureBase
{
    /// @brief Check that a specific message can be constructed from a generic Message.
    void check_message_constructor(
        odil::DataSet const & command_set)
    {
        odil::message::Message const generic_message(command_set);
        TMessage const message(generic_message);
        this->check(message);
    }

    /// @brief Check that a specific message can be constructed from a generic Message.
    void check_message_constructor(
        odil::DataSet const & command_set, odil::DataSet const & data_set)
    {
        odil::message::Message const generic_message(command_set, data_set);
        TMessage const message(generic_message);
        this->check(message);
    }

    /// @brief Check that a specific message cannot be constructed from a generic Message.
    void check_message_constructor_throw(
        odil::DataSet const & command_set)
    {
        odil::message::Message const generic_message(command_set);
        BOOST_CHECK_THROW(
            TMessage const message(generic_message),
            odil::Exception);
    }

    /// @brief Check that a specific message cannot be constructed from a generic Message.
    void check_message_constructor_throw(
        odil::DataSet const & command_set, odil::DataSet const & data_set)
    {
        odil::message::Message const generic_message(command_set, data_set);
        BOOST_CHECK_THROW(
            TMessage const message(generic_message),
            odil::Exception);
    }

    /// @brief Check that the specific message attributes are set correctly
    virtual void check(TMessage const & message) =0;
};

#endif // _779c46d6_b6ea_443a_9642_f1ec5b87d4b3
