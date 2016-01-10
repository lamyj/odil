/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f9af3e63_3597_4513_8c10_b55058f5370b
#define _f9af3e63_3597_4513_8c10_b55058f5370b

#include "odil/dcmtk/ElementAccessor.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcelem.h>
#include <dcmtk/dcmdata/dcerror.h>
#include <dcmtk/ofstd/ofstring.h>

namespace odil
{

namespace dcmtk
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

template<typename TValueType>
TValueType
get_binary(DcmElement const & element, unsigned long const position)
{
    if(position != 0)
    {
        throw Exception("Position must be 0 for binary VRs");
    }

    DcmEVR const evr = element.getTag().getVR().getValidEVR();

    TValueType result;
    OFCondition condition;

    typename TValueType::value_type * data=NULL;
    if(evr == EVR_OB || evr == EVR_UN)
    {
        Uint8 * typed_data;
        condition = const_cast<DcmElement&>(element).getUint8Array(typed_data);
        data = reinterpret_cast<typename TValueType::value_type *>(typed_data);
    }
    else if(evr == EVR_OW)
    {
        Uint16 * typed_data;
        condition = const_cast<DcmElement&>(element).getUint16Array(typed_data);
        data = reinterpret_cast<typename TValueType::value_type *>(typed_data);
    }
    else if(evr == EVR_OF)
    {
        Float32 * typed_data;
        condition = const_cast<DcmElement&>(element).getFloat32Array(typed_data);
        data = reinterpret_cast<typename TValueType::value_type *>(typed_data);
    }
    else
    {
        throw Exception(
            std::string("Unknown VR: ") +
            element.getTag().getVR().getValidVRName());
    }

    if(condition.bad())
    {
        throw Exception(condition);
    }

    result.resize(element.getLengthField());
    std::copy(data, data+element.getLengthField(), result.begin());

    return result;
}

template<typename TValueType>
void
set_binary(
    DcmElement & element, TValueType const & value,
    unsigned long const position)
{

}

}

}

#endif // _f9af3e63_3597_4513_8c10_b55058f5370b
