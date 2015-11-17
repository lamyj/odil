#define BOOST_TEST_MODULE Exception
#include <boost/test/unit_test.hpp>

#include <ostream>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/ofcond.h>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

std::ostream & operator<<(std::ostream & stream, Exception::Source const & type)
{
    stream << int(type);
    return stream;
}

}

BOOST_AUTO_TEST_CASE(StringConstructor)
{
    dcmtkpp::Exception const exception("foo");
    BOOST_CHECK_EQUAL(exception.get_source(), dcmtkpp::Exception::Source::Message);
    BOOST_CHECK_EQUAL(exception.what(), "foo");
    BOOST_CHECK_THROW(exception.get_condition(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ConditionConstructor)
{
    dcmtkpp::Exception const exception(EC_IllegalParameter);
    BOOST_CHECK_EQUAL(exception.get_source(), dcmtkpp::Exception::Source::Condition);
    BOOST_CHECK_EQUAL(exception.what(), OFCondition(EC_IllegalParameter).text());
    BOOST_CHECK(exception.get_condition() == EC_IllegalParameter);
}
