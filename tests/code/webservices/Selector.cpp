#define BOOST_TEST_MODULE Selector
#include <boost/test/unit_test.hpp>

#include <vector>

#include "odil/webservices/Selector.h"

BOOST_AUTO_TEST_CASE(Constructor_empty)
{
    odil::webservices::Selector const selector;
    BOOST_REQUIRE(!selector.is_study_present());
    BOOST_REQUIRE(!selector.is_series_present());
    BOOST_REQUIRE(!selector.is_instance_present());
}

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::webservices::Selector const selector("1.2", "3.4");
    BOOST_REQUIRE(selector.is_study_present());
    BOOST_REQUIRE_EQUAL(selector.get_study(), "1.2");

    BOOST_REQUIRE(selector.is_series_present());
    BOOST_REQUIRE_EQUAL(selector.get_series(), "3.4");

    BOOST_REQUIRE(!selector.is_instance_present());
    BOOST_REQUIRE(selector.get_frames().empty());
}

BOOST_AUTO_TEST_CASE(Equal)
{
    odil::webservices::Selector selector;
    selector.set_study("1.2");
    odil::webservices::Selector const selector_("1.2");
    BOOST_REQUIRE(selector == selector_);
}

BOOST_AUTO_TEST_CASE(Different)
{
    odil::webservices::Selector selector;
    selector.set_study("1.2").set_series("3.3");
    odil::webservices::Selector const selector_("1.2", "3.4");
    BOOST_REQUIRE(selector != selector_);
}

BOOST_AUTO_TEST_CASE(GetPath)
{
    odil::webservices::Selector selector;
    selector.set_study("1.2").set_series("3.4");
    BOOST_REQUIRE_EQUAL(selector.get_path(false), "/studies/1.2/series/3.4");

    odil::webservices::Selector selector_1;
    selector_1.set_study("1.2").set_series("");
    BOOST_REQUIRE_EQUAL(selector_1.get_path(false), "/studies/1.2/series/");

    odil::webservices::Selector const selector_2("1.2", "3.4", "5.6", {1,2,3});
    BOOST_REQUIRE_EQUAL(selector_2.get_path(true), "/studies/1.2/series/3.4/instances/5.6/frames/1,2,3");

    odil::webservices::Selector const selector_3("1.2", "3.4");
    BOOST_REQUIRE_EQUAL(selector_3.get_path(false), "/studies/1.2/series/3.4");
}

BOOST_AUTO_TEST_CASE(Is_XXX_present)
{
    odil::webservices::Selector selector;
    selector.set_instance("5.6");
    BOOST_REQUIRE(selector.is_instance_present());
}

BOOST_AUTO_TEST_CASE(Get_XXX)
{
    odil::webservices::Selector const selector("1.2", "3.4", "5.6", {1, 2, 3});
    BOOST_REQUIRE_EQUAL(selector.get_instance(), "5.6");
    std::vector<int> frames({1, 2, 3});
    BOOST_REQUIRE(selector.get_frames() == frames);
}

BOOST_AUTO_TEST_CASE(Set_XXX)
{
    odil::webservices::Selector selector;
    selector.set_frames({1, 2, 3});
    std::vector<int> frames({1, 2, 3});
    BOOST_REQUIRE(selector.get_frames() == frames);
}
