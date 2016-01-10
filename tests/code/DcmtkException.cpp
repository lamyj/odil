#define BOOST_TEST_MODULE DcmtkException
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/ofcond.h>

#include "odil/dcmtk/Exception.h"

BOOST_AUTO_TEST_CASE(StringConstructor)
{
    odil::dcmtk::Exception const exception("foo");
    BOOST_REQUIRE(
        exception.get_source() == odil::dcmtk::Exception::Source::Message);
    BOOST_REQUIRE_EQUAL(exception.what(), "foo");
    BOOST_REQUIRE_THROW(exception.get_condition(), odil::dcmtk::Exception);
}

BOOST_AUTO_TEST_CASE(ConditionConstructor)
{
    odil::dcmtk::Exception const exception(EC_IllegalParameter);
    BOOST_REQUIRE(
        exception.get_source() == odil::dcmtk::Exception::Source::Condition);
    BOOST_REQUIRE_EQUAL(
        exception.what(), OFCondition(EC_IllegalParameter).text());
    BOOST_REQUIRE(exception.get_condition() == EC_IllegalParameter);
}
