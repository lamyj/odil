#define BOOST_TEST_MODULE conversion
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "dcmtkpp/conversion.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Tag.h"
#include "dcmtkpp/Value.h"

BOOST_AUTO_TEST_CASE(TagFromDcmtkpp)
{
    dcmtkpp::Tag const source(0xdead, 0xbeef);
    DcmTagKey const destination = dcmtkpp::convert(source);

    BOOST_CHECK_EQUAL(destination.getGroup(), 0xdead);
    BOOST_CHECK_EQUAL(destination.getElement(), 0xbeef);
}

BOOST_AUTO_TEST_CASE(TagFromDcmtk)
{
    DcmTagKey const source(0xdead, 0xbeef);
    dcmtkpp::Tag const destination = dcmtkpp::convert(source);

    BOOST_CHECK_EQUAL(destination.group, 0xdead);
    BOOST_CHECK_EQUAL(destination.element, 0xbeef);
}

BOOST_AUTO_TEST_CASE(EmptyFromDcmtkpp)
{
    dcmtkpp::DataSet const empty;
    DcmDataset const result = dcmtkpp::convert(empty);
    BOOST_CHECK_EQUAL(result.card(), 0);
}

BOOST_AUTO_TEST_CASE(EmptyFromDcmtk)
{
    DcmDataset const empty;
    dcmtkpp::DataSet const result = dcmtkpp::convert(empty);
    BOOST_CHECK(result.empty());
}
