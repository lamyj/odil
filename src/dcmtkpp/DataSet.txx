/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a167e5b6_1de1_4d6e_b680_f410f3e6ec3b
#define _a167e5b6_1de1_4d6e_b680_f410f3e6ec3b

#include "dcmtkpp/DataSet.h"

#include <typeinfo>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

template<typename TValueType>
void
DataSet
::add(Tag const & tag, VR const & vr, TValueType const & value)
{
    if(this->_is_int_vr(vr))
    {
        if(typeid(TValueType) != typeid(Value::Integers))
        {
            throw Exception("Type mismatch");
        }
    }
    else if(this->_is_real_vr(vr))
    {
        if(typeid(TValueType) != typeid(Value::Reals))
        {
            throw Exception("Type mismatch");
        }
    }
    else if(this->_is_string_vr(vr))
    {
        if(typeid(TValueType) != typeid(Value::Strings))
        {
            throw Exception("Type mismatch");
        }
    }
    else if(vr == VR::SQ)
    {
        if(typeid(TValueType) != typeid(Value::DataSets))
        {
            throw Exception("Type mismatch");
        }
    }
    else
    {
        throw Exception("Unknown VR: "+::dcmtkpp::as_string(vr));
    }

    this->add(tag, Element(value, vr));
}

}

#endif // _a167e5b6_1de1_4d6e_b680_f410f3e6ec3b
