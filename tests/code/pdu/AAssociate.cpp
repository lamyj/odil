#define BOOST_TEST_MODULE AAssociateAC
#include <boost/test/unit_test.hpp>

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "dcmtkpp/pdu/AAssociate.h"
#include "dcmtkpp/pdu/ApplicationContext.h"
#include "dcmtkpp/pdu/PresentationContext.h"
#include "dcmtkpp/pdu/UserIdentityAC.h"
#include "dcmtkpp/pdu/UserInformation.h"
#include "dcmtkpp/Exception.h"

struct Fixture
{
public:
    static std::string const read_data;
    static std::string const write_data;

    dcmtkpp::pdu::ApplicationContext application_context;
    std::vector<dcmtkpp::pdu::PresentationContext> presentation_contexts;
    dcmtkpp::pdu::UserInformation user_information;

    Fixture()
    : application_context("foo")
    {
        dcmtkpp::pdu::PresentationContext pc1("transfer_syntax");
        pc1.set_id(3);
        pc1.set_result_reason(1);

        dcmtkpp::pdu::PresentationContext pc2("transfer_syntax_2");
        pc2.set_id(5);
        pc2.set_result_reason(2);

        this->presentation_contexts = {pc1, pc2};

        this->user_information.set_sub_items<dcmtkpp::pdu::MaximumLength>(
            { { 0x12345678 } });
        this->user_information.set_sub_items<dcmtkpp::pdu::UserIdentityAC>(
            { { "bar" } });
    }

    void check_application_context(
        dcmtkpp::pdu::ApplicationContext const & context) const
    {
        BOOST_REQUIRE_EQUAL(
            context.get_name(), this->application_context.get_name());
    }

    void check_presentation_contexts(
        std::vector<dcmtkpp::pdu::PresentationContext> const & contexts)
    {
        BOOST_REQUIRE_EQUAL(contexts.size(), presentation_contexts.size());
        for(int i=0; i<contexts.size(); ++i)
        {
            BOOST_REQUIRE_EQUAL(
                contexts[i].get_item_type(),
                presentation_contexts[i].get_item_type());
            BOOST_REQUIRE_EQUAL(
                contexts[i].get_id(),
                presentation_contexts[i].get_id());
            BOOST_REQUIRE_EQUAL(
                contexts[i].get_result_reason(),
                presentation_contexts[i].get_result_reason());
        }
    }

    void check_user_information(
        dcmtkpp::pdu::UserInformation const & user_information) const
    {
        BOOST_REQUIRE(
            !user_information.get_sub_items<dcmtkpp::pdu::MaximumLength>().empty());
        BOOST_REQUIRE_EQUAL(
            user_information.get_sub_items<dcmtkpp::pdu::MaximumLength>()[0].get_maximum_length(),
            0x12345678);

        BOOST_REQUIRE(
            !user_information.get_sub_items<dcmtkpp::pdu::UserIdentityAC>().empty());
        BOOST_REQUIRE_EQUAL(
            user_information.get_sub_items<dcmtkpp::pdu::UserIdentityAC>()[0].get_server_response(),
            "bar");
    }
};

std::string const
Fixture
::read_data(
    // Header, 6 bytes

    "\x02\x00"
    "\x00\x00\x00\x98"

    // Items: 68 bytes

    "\x00\x01\x00\x00"
    "       CALLED_AE"
    "CALLING_AE      "
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

    // Application Context, 7 bytes

    "\x10\x00\x00\x03"
    "foo"

    // Presentation Contexts, 27+29 bytes

    "\x21\x00\x00\x17"
    "\x03\x00\x01\x00"
    "\x40\x00\x00\x0f""transfer_syntax"

    "\x21\x00\x00\x19"
    "\x05\x00\x02\x00"
    "\x40\x00\x00\x11""transfer_syntax_2"

    // User Information, 21 bytes

    "\x50\x00\x00\x11"
    "\x51\x00\x00\x04"
    "\x12\x34\x56\x78"
    "\x59\x00\x00\x05"
    "\x00\x03" "bar"
    ,
    158
);

std::string const
Fixture
::write_data(
    // Header, 6 bytes

    "\x02\x00"
    "\x00\x00\x00\x98"

    // Items: 68 bytes

    "\x00\x01\x00\x00"
    "CALLED_AE       "
    "CALLING_AE      "
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

    // Application Context, 7 bytes

    "\x10\x00\x00\x03"
    "foo"

    // Presentation Contexts, 27+29 bytes

    "\x21\x00\x00\x17"
    "\x03\x00\x01\x00"
    "\x40\x00\x00\x0f""transfer_syntax"

    "\x21\x00\x00\x19"
    "\x05\x00\x02\x00"
    "\x40\x00\x00\x11""transfer_syntax_2"

    // User Information, 21 bytes

    "\x50\x00\x00\x11"
    "\x51\x00\x00\x04"
    "\x12\x34\x56\x78"
    "\x59\x00\x00\x05"
    "\x00\x03" "bar"
    ,
    158
);

BOOST_AUTO_TEST_CASE(Constructor)
{
    dcmtkpp::pdu::AAssociate const pdu(dcmtkpp::pdu::AAssociate::Type::AC);

    BOOST_REQUIRE(pdu.get_type() == dcmtkpp::pdu::AAssociate::Type::AC);
    BOOST_REQUIRE_EQUAL(pdu.get_called_ae_title(), "");
    BOOST_REQUIRE_EQUAL(pdu.get_calling_ae_title(), "");
    BOOST_REQUIRE_EQUAL(pdu.get_protocol_version(), 0);
    BOOST_REQUIRE_THROW(pdu.get_application_context(), dcmtkpp::Exception);
    BOOST_REQUIRE(pdu.get_presentation_contexts().empty());
    BOOST_REQUIRE_THROW(pdu.get_user_information(), dcmtkpp::Exception);
}

BOOST_FIXTURE_TEST_CASE(ConstructorStream, Fixture)
{
    std::istringstream stream(read_data);
    dcmtkpp::pdu::AAssociate const pdu(stream);

    BOOST_REQUIRE(pdu.get_type() == dcmtkpp::pdu::AAssociate::Type::AC);
    BOOST_REQUIRE_EQUAL(pdu.get_called_ae_title(), "CALLED_AE");
    BOOST_REQUIRE_EQUAL(pdu.get_calling_ae_title(), "CALLING_AE");
    BOOST_REQUIRE_EQUAL(pdu.get_protocol_version(), 1);
    this->check_application_context(pdu.get_application_context());
    this->check_presentation_contexts(pdu.get_presentation_contexts());
    this->check_user_information(pdu.get_user_information());
}

BOOST_AUTO_TEST_CASE(ProtocolVersion)
{
    dcmtkpp::pdu::AAssociate pdu(dcmtkpp::pdu::AAssociate::Type::AC);
    BOOST_REQUIRE_EQUAL(pdu.get_protocol_version(), 0);
    pdu.set_protocol_version(2);
    BOOST_REQUIRE_EQUAL(pdu.get_protocol_version(), 2);
}

BOOST_AUTO_TEST_CASE(CalledAETitle)
{
    dcmtkpp::pdu::AAssociate pdu(dcmtkpp::pdu::AAssociate::Type::AC);
    BOOST_REQUIRE_EQUAL(pdu.get_called_ae_title(), "");
    pdu.set_called_ae_title("called");
    BOOST_REQUIRE_EQUAL(pdu.get_called_ae_title(), "called");
}

BOOST_AUTO_TEST_CASE(CallingAETitle)
{
    dcmtkpp::pdu::AAssociate pdu(dcmtkpp::pdu::AAssociate::Type::AC);
    BOOST_REQUIRE_EQUAL(pdu.get_calling_ae_title(), "");
    pdu.set_calling_ae_title("calling");
    BOOST_REQUIRE_EQUAL(pdu.get_calling_ae_title(), "calling");
}

BOOST_FIXTURE_TEST_CASE(ApplicationContext, Fixture)
{
    dcmtkpp::pdu::AAssociate pdu(dcmtkpp::pdu::AAssociate::Type::AC);
    BOOST_REQUIRE_THROW(pdu.get_application_context(), dcmtkpp::Exception);
    pdu.set_application_context(application_context);
    this->check_application_context(pdu.get_application_context());
}

BOOST_FIXTURE_TEST_CASE(PresentationContexts, Fixture)
{
    dcmtkpp::pdu::AAssociate pdu(dcmtkpp::pdu::AAssociate::Type::AC);
    BOOST_REQUIRE(pdu.get_presentation_contexts().empty());
    pdu.set_presentation_contexts(presentation_contexts);
    this->check_presentation_contexts(pdu.get_presentation_contexts());
}

BOOST_FIXTURE_TEST_CASE(UserInformation, Fixture)
{
    dcmtkpp::pdu::AAssociate pdu(dcmtkpp::pdu::AAssociate::Type::AC);
    BOOST_REQUIRE_THROW(pdu.get_user_information(), dcmtkpp::Exception);
    pdu.set_user_information(user_information);
    this->check_user_information(pdu.get_user_information());
}

BOOST_FIXTURE_TEST_CASE(Write, Fixture)
{
    dcmtkpp::pdu::AAssociate pdu(dcmtkpp::pdu::AAssociate::Type::AC);
    pdu.set_protocol_version(1);
    pdu.set_called_ae_title("CALLED_AE");
    pdu.set_calling_ae_title("CALLING_AE");

    pdu.set_application_context(application_context);
    pdu.set_presentation_contexts(presentation_contexts);
    pdu.set_user_information(user_information);

    std::ostringstream stream;
    stream << pdu;

    BOOST_REQUIRE(stream.str() == write_data);
}

BOOST_AUTO_TEST_CASE(CalledAETitleEmpty)
{
    dcmtkpp::pdu::AAssociate pdu(dcmtkpp::pdu::AAssociate::Type::AC);
    BOOST_REQUIRE_THROW(pdu.set_called_ae_title(""), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(CalledAETitleTooLong)
{
    dcmtkpp::pdu::AAssociate pdu(dcmtkpp::pdu::AAssociate::Type::AC);
    BOOST_REQUIRE_THROW(
        pdu.set_called_ae_title("123456789abcdef01"), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(CallingAETitleEmpty)
{
    dcmtkpp::pdu::AAssociate pdu(dcmtkpp::pdu::AAssociate::Type::AC);
    BOOST_REQUIRE_THROW(pdu.set_calling_ae_title(""), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(CallingAETitleTooLong)
{
    dcmtkpp::pdu::AAssociate pdu(dcmtkpp::pdu::AAssociate::Type::AC);
    BOOST_REQUIRE_THROW(
        pdu.set_calling_ae_title("123456789abcdef01"), dcmtkpp::Exception);
}
