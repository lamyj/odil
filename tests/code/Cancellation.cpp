#define BOOST_TEST_MODULE Cancellation
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/Cancellation.h"

#include "../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<dcmtkpp::Cancellation>
{
    DcmDataset command_set;
    Fixture()
    {
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DCM_CommandField, DIMSE_C_CANCEL_RQ);
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DCM_MessageIDBeingRespondedTo, 1234);
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
    this->check_message_constructor(this->command_set, NULL);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    dcmtkpp::ElementAccessor<Uint16>::set(
        this->command_set, DCM_CommandField, DIMSE_C_ECHO_RQ);
    this->check_message_constructor_throw(this->command_set, NULL);
}
