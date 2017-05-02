#define BOOST_TEST_MODULE multipart_related
#include <boost/test/unit_test.hpp>

#include <iterator>
#include <sstream>
#include <vector>

#include "odil/webservices/Message.h"
#include "odil/webservices/multipart_related.h"

BOOST_AUTO_TEST_CASE(is_multipart_related)
{
    odil::webservices::Message const message(
        odil::webservices::Message::Headers{{
            "Content-Type", "Multipart/Related; "
            "boundary=example-1;start=\"<950120.aaCC@XIson.com>\";"
            "type=\"Application/X-FixedRecord\";start-info=\"-o ps\"\r\n"}});
    BOOST_REQUIRE(odil::webservices::is_multipart_related(message));
}

BOOST_AUTO_TEST_CASE(is_not_multipart_related_bad_content)
{
    odil::webservices::Message const message(
    odil::webservices::Message::Headers{{
        "Content-Type", "text/plain; format=flowed"}});
    BOOST_REQUIRE(!odil::webservices::is_multipart_related(message));
}

BOOST_AUTO_TEST_CASE(is_not_multipart_related_no_content)
{
    odil::webservices::Message const message;
    BOOST_REQUIRE(!odil::webservices::is_multipart_related(message));
}

BOOST_AUTO_TEST_CASE(count_parts)
{
    odil::webservices::Message const message(
        odil::webservices::Message::Headers{{
            "Content-Type", "Multipart/Related; boundary=example-1;"
            "start=\"<950120.aaCC@XIson.com>\";"
            "type=\"Application/X-FixedRecord\";start-info=\"-o ps\"\r\n"}},
        "--example-1\r\n"
        "Content-Type: Application/X-FixedRecord\r\n"
        "Content-ID: <950120.aaCC@XIson.com>\r\n"
        "\r\n"
        "25\r\n"
        "10\r\n"
        "34\r\n"
        "10\r\n"
        "25\r\n"
        "21\r\n"
        "26\r\n"
        "10\r\n"
        "--example-1\r\n"
        "Content-Type: Application/octet-stream\r\n"
        "Content-Description: The fixed length records\r\n"
        "Content-Transfer-Encoding: base64\r\n"
        "Content-ID: <950120.aaCB@XIson.com>\r\n"
        "\r\n"
        "T2xkIE1hY0RvbmFsZCBoYWQgYSBmYXJtCkUgSS\r\n"
        "BFIEkgTwpBbmQgb24gaGlzIGZhcm0gaGUgaGFk\r\n"
        "IHNvbWUgZHVja3MKRSBJIEUgSSBPCldpdGggYS\r\n"
        "BxdWFjayBxdWFjayBoZXJlLAphIHF1YWNrIHF1\r\n"
        "YWNrIHRoZXJlLApldmVyeSB3aGVyZSBhIHF1YW\r\n"
        "NrIHF1YWNrCkUgSSBFIEkgTwo=\r\n"
        "\r\n"
        "--example-1--\r\n"
        "\r\n");

    BOOST_REQUIRE_EQUAL(odil::webservices::count_parts(message), 2);
}

BOOST_AUTO_TEST_CASE(random_boundary)
{
    BOOST_REQUIRE(
        odil::webservices::random_boundary()
            != odil::webservices::random_boundary());
}

struct Fixture
{
    odil::webservices::Message message;
    std::vector<odil::webservices::Message> parts;

    Fixture()
    {
        this->message = odil::webservices::Message(
            odil::webservices::Message::Headers{{
                "Content-Type", "Multipart/Related; "
                "boundary=example-1;start=\"<950120.aaCC@XIson.com>\";"
                "type=\"Application/X-FixedRecord\";start-info=\"-o ps\"\r\n"}},
            "Preamble, must be ignored\r\n"
            "--example-1\r\n"
            "Content-Type: Application/X-FixedRecord\r\n"
            "Content-ID: <950120.aaCC@XIson.com>\r\n"
            "\r\n"
            "25\r\n"
            "10\r\n"
            "34\r\n"
            "10\r\n"
            "25\r\n"
            "21\r\n"
            "26\r\n"
            "10\r\n"
            "--example-1\r\n"
            "Content-Type: Application/octet-stream\r\n"
            "Content-Description: The fixed length records\r\n"
            "Content-Transfer-Encoding: base64\r\n"
            "Content-ID: <950120.aaCB@XIson.com>\r\n"
            "\r\n"
            "T2xkIE1hY0RvbmFsZCBoYWQgYSBmYXJtCkUgSS\r\n"
            "BFIEkgTwpBbmQgb24gaGlzIGZhcm0gaGUgaGFk\r\n"
            "IHNvbWUgZHVja3MKRSBJIEUgSSBPCldpdGggYS\r\n"
            "BxdWFjayBxdWFjayBoZXJlLAphIHF1YWNrIHF1\r\n"
            "YWNrIHRoZXJlLApldmVyeSB3aGVyZSBhIHF1YW\r\n"
            "NrIHF1YWNrCkUgSSBFIEkgTwo=\r\n"
            "\r\n"
            "--example-1--\r\n"
            "\r\n"
            "Epilogue, must also be ignored");

        this->parts = std::vector<odil::webservices::Message>{
            {
                {
                    { "Content-Type", "Application/X-FixedRecord" },
                    { "Content-ID", "<950120.aaCC@XIson.com>" }
                },
                "25\r\n"
                "10\r\n"
                "34\r\n"
                "10\r\n"
                "25\r\n"
                "21\r\n"
                "26\r\n"
                "10"
            },
            {
                {
                    { "Content-Type", "Application/octet-stream" },
                    { "Content-Description", "The fixed length records" },
                    { "Content-Transfer-Encoding", "base64" },
                    { "Content-ID", "<950120.aaCB@XIson.com>" }
                },
                "T2xkIE1hY0RvbmFsZCBoYWQgYSBmYXJtCkUgSS\r\n"
                "BFIEkgTwpBbmQgb24gaGlzIGZhcm0gaGUgaGFk\r\n"
                "IHNvbWUgZHVja3MKRSBJIEUgSSBPCldpdGggYS\r\n"
                "BxdWFjayBxdWFjayBoZXJlLAphIHF1YWNrIHF1\r\n"
                "YWNrIHRoZXJlLApldmVyeSB3aGVyZSBhIHF1YW\r\n"
                "NrIHF1YWNrCkUgSSBFIEkgTwo=\r\n"
            }
        };
    }
};

BOOST_FIXTURE_TEST_CASE(transform_parts, Fixture)
{
    std::vector<odil::webservices::Message> transformed_parts;
    int called = 0;
    auto const functor =
        [&called](odil::webservices::Message const & part)
        {
            ++called;
            return part;
        };

    odil::webservices::transform_parts(
        this->message, std::back_inserter(transformed_parts), functor);
    BOOST_REQUIRE_EQUAL(called, this->parts.size());
    BOOST_REQUIRE(
        std::equal(
            this->parts.begin(), this->parts.end(),
            transformed_parts.begin(),
            [](
                odil::webservices::Message const & m1,
                odil::webservices::Message const & m2)
            {
                return (
                    m1.get_headers() == m2.get_headers()
                    && m1.get_body() == m2.get_body());
            }
    ));
}

BOOST_FIXTURE_TEST_CASE(accumulate_parts, Fixture)
{
    std::ostringstream stream;
    int called = 0;
    auto const serialize =
        [&called](odil::webservices::Message const & part)
        {
            ++called;
            return part;
        };

    odil::webservices::accumulate_parts(
        this->parts.begin(), this->parts.end(), serialize, stream, "example-1");
    BOOST_REQUIRE_EQUAL(called, this->parts.size());

    odil::webservices::Message const new_message(
        { {"Content-Type", "multipart/related;boundary=example-1"} },
        stream.str());
    std::vector<odil::webservices::Message> transformed_parts;
    auto const functor =
        [](odil::webservices::Message const & part)
        {
            return part;
        };

    odil::webservices::transform_parts(
        new_message, std::back_inserter(transformed_parts), functor);
    BOOST_REQUIRE_EQUAL(called, this->parts.size());
    BOOST_REQUIRE(
        std::equal(
            this->parts.begin(), this->parts.end(),
            transformed_parts.begin(),
            [](
                odil::webservices::Message const & m1,
                odil::webservices::Message const & m2)
            {
                return (
                    m1.get_headers() == m2.get_headers()
                    && m1.get_body() == m2.get_body());
            }
    ));
}
