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

template<DcmEVR VR>
bool
ElementAccessor<VR>
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

template<DcmEVR VR>
typename ElementAccessor<VR>::ValueType
ElementAccessor<VR>
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

template<DcmEVR VR>
void
ElementAccessor<VR>
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

template<DcmEVR VR>
typename ElementTraits<VR>::ValueType
get_default(DcmElement const & element, unsigned long const position)
{
    if(element.getTag().getVR().getValidEVR() != VR)
    {
        throw Exception("VR mismatch");
    }

    typename ElementTraits<VR>::ValueType value;
    OFCondition const & condition =
        ElementTraits<VR>::getter(
            const_cast<DcmElement&>(element), value, position);
    if(condition.bad())
    {
        throw Exception(condition);
    }

    return value;
}

template<DcmEVR VR>
void
set_default(
    DcmElement & element,
    typename ElementTraits<VR>::ValueType const & value, unsigned long const position)
{
    if(element.getTag().getVR().getValidEVR() != VR)
    {
        throw Exception("VR mismatch");
    }

    OFCondition const condition = ElementTraits<VR>::setter(element, value, position);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

template<DcmEVR VR>
typename ElementTraits<VR>::ValueType
get_string(DcmElement const & element, unsigned long const position)
{
    if(element.getTag().getVR().getValidEVR() != VR)
    {
        throw Exception("VR mismatch");
    }

    OFString value;
    ElementTraits<VR>::getter(const_cast<DcmElement&>(element), value, position);

    return std::string(value.c_str());
}

template<DcmEVR VR>
void
set_string(
    DcmElement & element,
    typename ElementTraits<VR>::ValueType const & value, unsigned long const position)
{
    if(element.getTag().getVR().getValidEVR() != VR)
    {
        throw Exception("VR mismatch");
    }

    OFString const value_dcmtk(value.c_str(), value.size());
    OFCondition const condition = ElementTraits<VR>::setter(
        element, value_dcmtk, position);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

}

#endif // _f9af3e63_3597_4513_8c10_b55058f5370b
