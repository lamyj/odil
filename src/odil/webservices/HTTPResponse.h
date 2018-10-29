/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _c08db816_ac02_484c_8e9a_ab816c5198c7
#define _c08db816_ac02_484c_8e9a_ab816c5198c7

#include <string>

#include "odil/odil.h"
#include "odil/webservices/Message.h"

namespace odil
{

namespace webservices
{

/// @brief HTTP Response
class ODIL_API HTTPResponse: public Message
{
public:
    /**
     * @brief Constructor
     *
     * By default, HTTP version and reason default to "" and status to 0
     * "HTTP/1.0".
     */
    HTTPResponse(
        std::string const & http_version="",
        unsigned int status=0, std::string const & reason="",
        Headers const & headers={}, std::string const & body="");

    HTTPResponse(HTTPResponse const &) = default;
    HTTPResponse(HTTPResponse &&) = default;
    HTTPResponse & operator=(HTTPResponse const &) = default;
    HTTPResponse & operator=(HTTPResponse &&) = default;
    virtual ~HTTPResponse() = default;

    /// @brief Return the HTTP version.
    std::string const & get_http_version() const;

    /// @brief Set the HTTP version.
    void set_http_version(std::string const & http_version);

    /// @brief Return the status.
    unsigned int get_status() const;

    /// @brief Set the status.
    void set_status(unsigned int status);

    /// @brief Return the reason.
    std::string const & get_reason() const;

    /// @brief Set the reason.
    void set_reason(std::string const & target);

private:
    std::string _http_version;
    unsigned int _status;
    std::string _reason;
};

/// @brief Input an HTTP response from a stream.
ODIL_API
std::istream &
operator>>(std::istream & stream, HTTPResponse & Response);

/// @brief Output an HTTP response to a stream.
ODIL_API
std::ostream &
operator<<(std::ostream & stream, HTTPResponse const & Response);

}

}

#endif // _c08db816_ac02_484c_8e9a_ab816c5198c7
