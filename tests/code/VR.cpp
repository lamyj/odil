#define BOOST_TEST_MODULE VR
#include <boost/test/unit_test.hpp>

#include "odil/Exception.h"
#include "odil/VR.h"

BOOST_AUTO_TEST_CASE(as_string)
{
    odil::VR const vr(odil::VR::AT);
    std::string const string = odil::as_string(vr);
    BOOST_CHECK_EQUAL(string, "AT");
}

BOOST_AUTO_TEST_CASE(as_string_invalid)
{
    odil::VR const vr(odil::VR::INVALID);
    BOOST_CHECK_THROW(odil::as_string(vr), odil::Exception);
}

BOOST_AUTO_TEST_CASE(as_vr)
{
    std::string const string("AT");
    odil::VR const vr = odil::as_vr(string);
    BOOST_CHECK(vr == odil::VR::AT);
}

BOOST_AUTO_TEST_CASE(as_vr_wrong)
{
    std::string const string("XX");
    BOOST_CHECK_THROW(odil::as_vr(string), odil::Exception);
}
