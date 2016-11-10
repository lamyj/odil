/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _9d8fe506_1ea6_448c_8c6c_bcd7375e89de
#define _9d8fe506_1ea6_448c_8c6c_bcd7375e89de

#include <string>

#include "odil/webservices/Message.h"

namespace odil
{

namespace webservices
{

/// @brief Test whether the message is multipart/related.
bool is_multipart_related(Message const & message);

/**
 * @brief Return the number of parts in the message, 0 if the message is not
 * multipart/related.
 */
std::size_t count_parts(Message const & message);

/**
 * @brief Split the a multipart/related message into its compound objects and
 * store them in the destination sequence.
 *
 * The sequence must be large enough to accomodate all parts.
 */
template<typename Iterator>
void split_parts(Message const & message, Iterator destination);

/**
 * @brief Join multiple messages into a multipart/related message.
 *
 * If the boundary is empty, generate a random one.
 */
template<typename Iterator>
Message join_parts(
    Iterator begin, Iterator end, std::string const & boundary="");

}

}

#include "multipart_related.txx"

#endif // _9d8fe506_1ea6_448c_8c6c_bcd7375e89de
