#define BOOST_TEST_MODULE AsynchronousOperationsWindow
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "odil/Exception.h"
#include "odil/dul/AsynchronousOperationsWindow.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::dul::AsynchronousOperationsWindow const window(123, 456);
    BOOST_REQUIRE_EQUAL(window.get_maximum_number_operations_invoked(), 123);
    BOOST_REQUIRE_EQUAL(window.get_maximum_number_operations_performed(), 456);
}

BOOST_AUTO_TEST_CASE(FromStream)
{
    std::string const data(
        "\x53\x00\x00\x04"
        "\x12\x34\x56\x78",
        8
    );
    std::istringstream stream(data);

    odil::dul::AsynchronousOperationsWindow const window(stream);

    BOOST_REQUIRE_EQUAL(window.get_maximum_number_operations_invoked(), 0x1234);
    BOOST_REQUIRE_EQUAL(window.get_maximum_number_operations_performed(), 0x5678);
}

BOOST_AUTO_TEST_CASE(MaximumNumberOperationsInvoked)
{
    odil::dul::AsynchronousOperationsWindow window(0, 0);
    window.set_maximum_number_operations_invoked(123);
    BOOST_REQUIRE_EQUAL(window.get_maximum_number_operations_invoked(), 123);
}

BOOST_AUTO_TEST_CASE(MaximumNumberOperationsPerformed)
{
    odil::dul::AsynchronousOperationsWindow window(0, 0);
    window.set_maximum_number_operations_performed(123);
    BOOST_REQUIRE_EQUAL(window.get_maximum_number_operations_performed(), 123);
}

BOOST_AUTO_TEST_CASE(Write)
{
    odil::dul::AsynchronousOperationsWindow const window(0x1234, 0x5678);
    std::ostringstream data;
    data << window;

    std::string const expected(
        "\x53\x00\x00\x04"
        "\x12\x34\x56\x78",
        8
    );

    BOOST_REQUIRE_EQUAL(data.str(), expected);
}
