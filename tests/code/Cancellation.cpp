#define BOOST_TEST_MODULE Cancellation
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Cancellation.h"

#include "../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<dcmtkpp::Cancellation>
{
    dcmtkpp::DataSet command_set;
    Fixture()
    {
        this->command_set.add("CommandField", {DIMSE_C_CANCEL_RQ});
        this->command_set.add("MessageIDBeingRespondedTo", {1234});
    }

    void check(dcmtkpp::Cancellation const & message)
    {
        BOOST_CHECK_EQUAL(message.get_command_field(), DIMSE_C_CANCEL_RQ);
        BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    dcmtkpp::Cancellation const message(1234);
    this->check(message);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    this->check_message_constructor(this->command_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    this->command_set.as_int("CommandField") = {DIMSE_C_ECHO_RQ};
    this->check_message_constructor_throw(this->command_set);
}
