/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _de64b8e1_4116_41f8_a085_dabfdc6c63c3
#define _de64b8e1_4116_41f8_a085_dabfdc6c63c3

#include "odil/Value.h"

#include "odil/Exception.h"

namespace odil
{
template<typename TVisitor>
typename TVisitor::result_type
apply_visitor(TVisitor const & visitor, Value const & value)
{
    if(value.get_type() == Value::Type::Empty)
    {
        throw Exception("Empty value");
    }
    else if(value.get_type() == Value::Type::Integers)
    {
        return visitor(value.as_integers());
    }
    else if(value.get_type() == Value::Type::Reals)
    {
        return visitor(value.as_reals());
    }
    else if(value.get_type() == Value::Type::Strings)
    {
        return visitor(value.as_strings());
    }
    else if(value.get_type() == Value::Type::DataSets)
    {
        return visitor(value.as_data_sets());
    }
    else if(value.get_type() == Value::Type::Binary)
    {
        return visitor(value.as_binary());
    }
    else
    {
        throw Exception("Unknown value type");
    }
}

template<typename TVisitor>
typename TVisitor::result_type
apply_visitor(TVisitor const & visitor, Value & value)
{
    if(value.get_type() == Value::Type::Empty)
    {
        throw Exception("Empty value");
    }
    else if(value.get_type() == Value::Type::Integers)
    {
        return visitor(value.as_integers());
    }
    else if(value.get_type() == Value::Type::Reals)
    {
        return visitor(value.as_reals());
    }
    else if(value.get_type() == Value::Type::Strings)
    {
        return visitor(value.as_strings());
    }
    else if(value.get_type() == Value::Type::DataSets)
    {
        return visitor(value.as_data_sets());
    }
    else if(value.get_type() == Value::Type::Binary)
    {
        return visitor(value.as_binary());
    }
    else
    {
        throw Exception("Unknown value type");
    }
}

}

#endif // _de64b8e1_4116_41f8_a085_dabfdc6c63c3
