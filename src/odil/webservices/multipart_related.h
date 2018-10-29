/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _9d8fe506_1ea6_448c_8c6c_bcd7375e89de
#define _9d8fe506_1ea6_448c_8c6c_bcd7375e89de

#include <ostream>
#include <string>

#include "odil/webservices/Message.h"

namespace odil
{

namespace webservices
{

/// @brief Test whether the message is multipart/related.
ODIL_API bool is_multipart_related(Message const & message);

/**
 * @brief Return the number of parts in the message, 0 if the message is not
 * multipart/related.
 */
ODIL_API std::size_t count_parts(Message const & message);

/// @brief Return a random multipart/related boundary.
ODIL_API std::string random_boundary();

/// @brief Transform each part of a multipart/related message.
template<typename Iterator, typename UnaryFunctor>
void transform_parts(
    Message const & message, Iterator destination, UnaryFunctor functor);


/// @brief Use to call a functor for each part of a multipart/related message.
template<typename UnaryFunctor>
void for_each_part(Message const & message, UnaryFunctor functor);

/**
 * @brief Serialize the (begin, end) sequence as a multipart/related message
 * body in stream as described in the RFC 2046
 * https://tools.ietf.org/html/rfc2046#section-5.1.1.
 */
template<typename Iterator, typename UnaryFunction>
std::ostream & accumulate_parts(
    Iterator begin, Iterator end, UnaryFunction serialize, std::ostream & stream,
    std::string const & boundary);

}

}

#include "multipart_related.txx"

#endif // _9d8fe506_1ea6_448c_8c6c_bcd7375e89de
