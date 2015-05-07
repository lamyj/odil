#define BOOST_TEST_MODULE VR
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/VR.h"

BOOST_AUTO_TEST_CASE(as_string)
{
    dcmtkpp::VR const vr(dcmtkpp::VR::AT);
    std::string const string = dcmtkpp::as_string(vr);
    BOOST_CHECK_EQUAL(string, "AT");
}

BOOST_AUTO_TEST_CASE(as_vr)
{
    std::string const string("AT");
    dcmtkpp::VR const vr = dcmtkpp::as_vr(string);
    BOOST_CHECK(vr == dcmtkpp::VR::AT);
}

BOOST_AUTO_TEST_CASE(as_vr_wrong)
{
    std::string const string("XX");
    BOOST_CHECK_THROW(dcmtkpp::as_vr(string), dcmtkpp::Exception);
}
