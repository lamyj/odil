#define BOOST_TEST_MODULE GetSCU
#include <boost/test/unit_test.hpp>

#include "odil/DataSet.h"
#include "odil/GetSCU.h"
#include "odil/registry.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    static bool store_callback_called;
    static bool get_callback_called;

    std::shared_ptr<odil::DataSet> query;

    Fixture()
    : PeerFixtureBase({
            {
                1, odil::registry::PatientRootQueryRetrieveInformationModelGET,
                { odil::registry::ImplicitVRLittleEndian }, 
                odil::AssociationParameters::PresentationContext::Role::SCU
            },
            {
                3, odil::registry::RawDataStorage,
                { odil::registry::ImplicitVRLittleEndian }, 
                odil::AssociationParameters::PresentationContext::Role::SCP
            }
        }),
        query(std::make_shared<odil::DataSet>())
    {
        Fixture::store_callback_called = false;
        Fixture::get_callback_called = false;

        this->query->add("QueryRetrieveLevel", {"PATIENT"});
        this->query->add("PatientName", {"Doe^John"});
    }


    static void store_callback(std::shared_ptr<odil::DataSet const>)
    {
        Fixture::store_callback_called = true;
    }

    static void get_callback(std::shared_ptr<odil::message::CGetResponse const>)
    {
        Fixture::get_callback_called = true;
    }
};

bool Fixture::store_callback_called = false;
bool Fixture::get_callback_called = false;

BOOST_FIXTURE_TEST_CASE(Get, Fixture)
{
    odil::GetSCU scu(this->association);

    scu.set_affected_sop_class(
        odil::registry::PatientRootQueryRetrieveInformationModelGET);
    auto const results = scu.get(this->query);

    BOOST_REQUIRE_EQUAL(results.size(), 1);
    BOOST_CHECK(
        results[0]->as_string("SOPInstanceUID") ==
            odil::Value::Strings(
                {"2.25.95090344942250266709587559073467305647"}));
}

BOOST_FIXTURE_TEST_CASE(GetBothCallbacks, Fixture)
{
    odil::GetSCU scu(this->association);

    scu.set_affected_sop_class(
        odil::registry::PatientRootQueryRetrieveInformationModelGET);
    scu.get(this->query, Fixture::store_callback, Fixture::get_callback);

    BOOST_CHECK(Fixture::store_callback_called);
    BOOST_CHECK(Fixture::get_callback_called);
}

BOOST_FIXTURE_TEST_CASE(GetOnlyStoreCallback, Fixture)
{
    odil::GetSCU scu(this->association);

    scu.set_affected_sop_class(
        odil::registry::PatientRootQueryRetrieveInformationModelGET);
    scu.get(this->query, Fixture::store_callback);

    BOOST_CHECK(Fixture::store_callback_called);
    BOOST_CHECK(!Fixture::get_callback_called);
}
