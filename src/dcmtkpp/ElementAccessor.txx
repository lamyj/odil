/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f9af3e63_3597_4513_8c10_b55058f5370b
#define _f9af3e63_3597_4513_8c10_b55058f5370b

#include "ElementAccessor.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcelem.h>
#include <dcmtk/dcmdata/dcerror.h>
#include <dcmtk/ofstd/ofstring.h>

namespace dcmtkpp
{

template<typename TValueType>
bool
ElementAccessor<TValueType>
::has(DcmDataset const & dataset, DcmTagKey const & tag)
{
    DcmElement * dummy;
    OFCondition const condition =
        const_cast<DcmDataset&>(dataset).findAndGetElement(tag, dummy);
    if(condition.good())
    {
        return true;
    }
    else if(condition == EC_TagNotFound)
    {
        return false;
    }
    else
    {
        throw Exception(condition);
    }
}

template<typename TValueType>
TValueType
ElementAccessor<TValueType>
::get(
    DcmDataset const & dataset,
    DcmTagKey const tag, unsigned int const position)
{
    DcmElement * element;
    OFCondition const condition =
        const_cast<DcmDataset &>(dataset).findAndGetElement(tag, element);
    if(condition.bad())
    {
        throw Exception(condition);
    }

    return element_get(*element, position);
}

template<typename TValueType>
void
ElementAccessor<TValueType>
::set(
    DcmDataset & dataset,
    DcmTagKey const tag, ValueType const & value, unsigned int const position)
{
    DcmElement * element;
    OFCondition const get_condition = dataset.findAndGetElement(tag, element);
    if(get_condition.bad())
    {
        OFCondition const insert_condition = dataset.insertEmptyElement(tag);
        if(insert_condition.bad())
        {
            throw Exception(insert_condition);
        }

        OFCondition const new_get_condition =
            dataset.findAndGetElement(tag, element);
        if(new_get_condition.bad())
        {
            throw Exception(insert_condition);
        }
    }

    element_set(*element, value, position);
}

template<typename TValueType>
TValueType
get_default(DcmElement const & element, unsigned long const position)
{
    TValueType value;
    OFCondition const & condition =
        ElementTraits<TValueType>::getter(
            const_cast<DcmElement&>(element), value, position);
    if(condition.bad())
    {
        throw Exception(condition);
    }

    return value;
}

template<typename TValueType>
void
set_default(
    DcmElement & element, TValueType const & value,
    unsigned long const position)
{
    OFCondition const condition = ElementTraits<TValueType>::setter(element, value, position);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

template<typename TValueType>
TValueType
get_string(DcmElement const & element, unsigned long const position)
{
    OFString value;
    ElementTraits<OFString>::getter(const_cast<DcmElement&>(element), value, position);

    return std::string(value.c_str());
}

template<typename TValueType>
void
set_string(
    DcmElement & element, TValueType const & value,
    unsigned long const position)
{
    OFString const value_dcmtk(value.c_str(), value.size());
    OFCondition const condition = ElementTraits<OFString>::setter(
        element, value_dcmtk, position);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

}

#endif // _f9af3e63_3597_4513_8c10_b55058f5370b
