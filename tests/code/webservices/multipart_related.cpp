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
            "Content-Type", "Multipart/Related; "
            "boundary=example-1;start=\"<950120.aaCC@XIson.com>\";"
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

BOOST_AUTO_TEST_CASE(split_parts)
{
    odil::webservices::Message const message(
        odil::webservices::Message::Headers{{
            "Content-Type", "Multipart/Related; "
            "boundary=example-1;start=\"<950120.aaCC@XIson.com>\";"
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

    std::vector<odil::webservices::Message> parts;
    odil::webservices::split_parts(message, std::back_inserter(parts));

    BOOST_REQUIRE_EQUAL(parts.size(), 2);

    BOOST_REQUIRE(
        parts[0].get_headers() == odil::webservices::Message::Headers({
            { "Content-Type", "Application/X-FixedRecord" },
            { "Content-ID", "<950120.aaCC@XIson.com>" }
        }));
    BOOST_REQUIRE_EQUAL(parts[0].get_body(),
        "25\r\n"
        "10\r\n"
        "34\r\n"
        "10\r\n"
        "25\r\n"
        "21\r\n"
        "26\r\n"
        "10\r\n"
    );

    BOOST_REQUIRE(
        parts[1].get_headers() == odil::webservices::Message::Headers({
            { "Content-Type", "Application/octet-stream" },
            { "Content-Description", "The fixed length records" },
            { "Content-Transfer-Encoding", "base64" },
            { "Content-ID", "<950120.aaCB@XIson.com>" }
        }));
    BOOST_REQUIRE_EQUAL(parts[1].get_body(),
        "T2xkIE1hY0RvbmFsZCBoYWQgYSBmYXJtCkUgSS\r\n"
        "BFIEkgTwpBbmQgb24gaGlzIGZhcm0gaGUgaGFk\r\n"
        "IHNvbWUgZHVja3MKRSBJIEUgSSBPCldpdGggYS\r\n"
        "BxdWFjayBxdWFjayBoZXJlLAphIHF1YWNrIHF1\r\n"
        "YWNrIHRoZXJlLApldmVyeSB3aGVyZSBhIHF1YW\r\n"
        "NrIHF1YWNrCkUgSSBFIEkgTwo=\r\n"
        "\r\n"
    );
}

BOOST_AUTO_TEST_CASE(join_parts)
{
    std::vector<odil::webservices::Message> parts{
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
            "10\r\n"
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
            "\r\n"
        }
    };

    auto const multipart_related = odil::webservices::join_parts(
        parts.begin(), parts.end()/*, "example-1"*/);

    BOOST_REQUIRE(odil::webservices::is_multipart_related(multipart_related));
    BOOST_REQUIRE_EQUAL(odil::webservices::count_parts(multipart_related), 2);


    std::vector<odil::webservices::Message> result;
    odil::webservices::split_parts(multipart_related, std::back_inserter(result));

    BOOST_REQUIRE_EQUAL(result.size(), 2);

    BOOST_REQUIRE(
        result[0].get_headers() == odil::webservices::Message::Headers({
            { "Content-Type", "Application/X-FixedRecord" },
            { "Content-ID", "<950120.aaCC@XIson.com>" }
        }));
    BOOST_REQUIRE_EQUAL(result[0].get_body(),
        "25\r\n"
        "10\r\n"
        "34\r\n"
        "10\r\n"
        "25\r\n"
        "21\r\n"
        "26\r\n"
        "10\r\n"
    );

    BOOST_REQUIRE(
        result[1].get_headers() == odil::webservices::Message::Headers({
            { "Content-Type", "Application/octet-stream" },
            { "Content-Description", "The fixed length records" },
            { "Content-Transfer-Encoding", "base64" },
            { "Content-ID", "<950120.aaCB@XIson.com>" }
        }));
    BOOST_REQUIRE_EQUAL(result[1].get_body(),
        "T2xkIE1hY0RvbmFsZCBoYWQgYSBmYXJtCkUgSS\r\n"
        "BFIEkgTwpBbmQgb24gaGlzIGZhcm0gaGUgaGFk\r\n"
        "IHNvbWUgZHVja3MKRSBJIEUgSSBPCldpdGggYS\r\n"
        "BxdWFjayBxdWFjayBoZXJlLAphIHF1YWNrIHF1\r\n"
        "YWNrIHRoZXJlLApldmVyeSB3aGVyZSBhIHF1YW\r\n"
        "NrIHF1YWNrCkUgSSBFIEkgTwo=\r\n"
        "\r\n"
    );
}

