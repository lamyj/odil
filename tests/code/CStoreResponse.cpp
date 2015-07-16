#define BOOST_TEST_MODULE CStoreResponse
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CStoreResponse.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Message.h"

#include "../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<dcmtkpp::CStoreResponse>
{
    dcmtkpp::DataSet command_set;

    Fixture()
    {
        this->command_set.add("CommandField", {dcmtkpp::Message::Command::C_STORE_RSP});
        this->command_set.add("MessageIDBeingRespondedTo", {1234});
        this->command_set.add("Status", {STATUS_Success});

        this->command_set.add("MessageID", {5678});
        this->command_set.add("AffectedSOPClassUID", {UID_MRImageStorage});
        this->command_set.add("AffectedSOPInstanceUID", {"1.2.3.4"});
    }

    void check(dcmtkpp::CStoreResponse const & message)
    {
        BOOST_CHECK_EQUAL(message.get_command_field(), dcmtkpp::Message::Command::C_STORE_RSP);
        BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
        BOOST_CHECK_EQUAL(message.get_status(), STATUS_Success);
        BOOST_CHECK(!message.has_data_set());

        BOOST_CHECK(message.has_message_id());
        BOOST_CHECK_EQUAL(message.get_message_id(), 5678);

        BOOST_CHECK(message.has_affected_sop_class_uid());
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_class_uid(), UID_MRImageStorage);

        BOOST_CHECK(message.has_affected_sop_instance_uid());
        BOOST_CHECK_EQUAL(message.get_affected_sop_instance_uid(), "1.2.3.4");
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    dcmtkpp::CStoreResponse message(1234, STATUS_Success);
    message.set_message_id(5678);
    message.set_affected_sop_class_uid(UID_MRImageStorage);
    message.set_affected_sop_instance_uid("1.2.3.4");

    this->check(message);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    this->check_message_constructor(this->command_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    this->command_set.add("CommandField", {dcmtkpp::Message::Command::C_ECHO_RQ});
    this->check_message_constructor_throw(this->command_set);
}

