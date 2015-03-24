/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b9607695_cb3b_4188_8caa_bc8bb051ef28
#define _b9607695_cb3b_4188_8caa_bc8bb051ef28

#include <exception>
#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/ofcond.h>

namespace dcmtkpp
{

/// @brief Base class for dcmtkpp exceptions.
class Exception: public std::exception
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
    virtual ~Exception() throw();
    
    /**
     * @brief Return the reason for the exception.
     * 
     * The reason for the exception is set to the message (for Source::Message) or
     * to the text of the condition (for Source::Condition).
     */
    virtual const char* what() const throw();
    
    /// @brief Return the exception source.
    Source get_source() const;
    
    /**
     * @brief Return the condition that was used to create this exception.
     * 
     * If the source is not Source::Condition, throw an exception.
     */
    OFCondition const & get_condition() const;

private:
    Source _source;
    std::string _message;
    OFCondition _condition;
};

}

#endif // _b9607695_cb3b_4188_8caa_bc8bb051ef28
