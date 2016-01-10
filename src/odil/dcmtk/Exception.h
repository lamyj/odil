/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _9e106372_aca6_4551_a591_95695eb00e4c
#define _9e106372_aca6_4551_a591_95695eb00e4c

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/ofcond.h>

#include "odil/Exception.h"

namespace odil
{

namespace dcmtk
{

class Exception: public ::odil::Exception
{
public:
    /**
     * @brief Source of the Exception: either a message string or an
     * OFCondition.
     */
    enum class Source { Message, Condition };

    /// @brief Message string constructor, set the source to Source::Message.
    Exception(std::string const & message);

    /// @brief Condition constructor, set the source to Source::Condition.
    Exception(OFCondition const & condition);

    /// @brief Destructor.
    virtual ~Exception() noexcept;

    /// @brief Return the exception source.
    Source get_source() const;

    /**
     * @brief Return the condition that was used to create this exception.
     *
     * If the source is not Source::Condition, throw an exception.
     */
    OFCondition const & get_condition() const;

    /**
     * @brief Return the reason for the exception.
     *
     * The reason for the exception is set to the message (for Source::Message) or
     * to the text of the condition (for Source::Condition).
     */
    virtual const char* what() const noexcept;
private:
    Source _source;
    OFCondition _condition;
};

}

}

#endif // _9e106372_aca6_4551_a591_95695eb00e4c

