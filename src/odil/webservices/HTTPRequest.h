/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a927d586_9154_4f1e_bd56_82f2b6f0450d
#define _a927d586_9154_4f1e_bd56_82f2b6f0450d

#include <string>

#include "odil/webservices/Message.h"
#include "odil/webservices/URL.h"

namespace odil
{

namespace webservices
{

/// @brief HTTP request
class HTTPRequest: public Message
{
public:
    /**
     * @brief Constructor
     *
     * By default, method, target are empty, and HTTP version default to
     * "HTTP/1.0".
     */
    HTTPRequest(
        std::string const & method="", URL const & target=URL(),
        std::string const & http_version="HTTP/1.0",
        Headers const & headers=Headers(), std::string const & body="");

    /// @brief Destructor.
    virtual ~HTTPRequest();

    /// @brief Return the method.
    std::string const & get_method() const;

    /// @brief Set the method.
    void set_method(std::string const & method);

    /// @brief Return the target.
    URL const & get_target() const;

    /// @brief Set the target.
    void set_target(URL const & target);

    /// @brief Return the HTTP version.
    std::string const & get_http_version() const;

    /// @brief Set the HTTP version.
    void set_http_version(std::string const & http_version);

private:
    std::string _method;
    URL _target;
    std::string _http_version;
};

/// @brief Input an HTTP request from a stream.
std::istream & operator>>(std::istream & stream, HTTPRequest & request);

/// @brief Output an HTTP request to a stream.
std::ostream & operator<<(std::ostream & stream, HTTPRequest const & request);

}

}

#endif // _a927d586_9154_4f1e_bd56_82f2b6f0450d
