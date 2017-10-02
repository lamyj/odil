/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d7a272d7_9beb_43c1_a5a1_fce4c0245c80
#define _d7a272d7_9beb_43c1_a5a1_fce4c0245c80

#include <istream>
#include <map>
#include <ostream>
#include <string>

#include "odil/odil.h"

namespace odil
{

namespace webservices
{

/// @brief RFC 5322 Message (i.e. headers with body).
class ODIL_API Message
{
public:
    /// @brief Associative container for headers.
    typedef std::map<std::string, std::string> Headers;

    /**
     * @brief Constructor.
     *
     * By default, headers and body will be empty.
     */
    Message(Headers const & headers=Headers(), std::string const & body="");

    /// @brief Destructor.
    virtual ~Message();

    /// @brief Return the headers
    Headers const & get_headers() const;

    /// @brief Set the headers.
    void set_headers(Headers const & headers);

    /**
     * @brief Test whether the given header exists.
     *
     * According to RFC 5322 1.2.2 and RFC 5234 2.3, the name is
     * case-insensitive.
     */
    bool has_header(std::string const & name) const;

    /**
     * @brief Return a header value or throw an exception if the required
     * header is missing.
     *
     * According to RFC 5322 1.2.2 and RFC 5234 2.3, the name is
     * case-insensitive.
     */
    std::string const & get_header(std::string const & name) const;

    /// @brief Set a header value.
    void set_header(std::string const & name, std::string const & value);

    /// @brief Return the body.
    std::string const & get_body() const;

    /// @brief Set the body.
    void set_body(std::string const & body);

private:
    Headers _headers;
    std::string _body;

    Headers::const_iterator _find_header(std::string const & name) const;
};

/// @brief Input a Message from a stream.
ODIL_API
std::istream &
operator>>(std::istream & stream, Message & message);

/// @brief Output a Message to a stream.
ODIL_API
std::ostream &
operator<<(std::ostream & stream, Message const & message);

}

}

#endif // _d7a272d7_9beb_43c1_a5a1_fce4c0245c80
