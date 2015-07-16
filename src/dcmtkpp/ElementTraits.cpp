/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/ElementTraits.h"

#include <functional>
#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcelem.h>
#include <dcmtk/dcmdata/dcvr.h>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

OFCondition
getString(DcmElement & element, OFString & value, unsigned long const position)
{
    OFCondition condition;

    DcmEVR const evr = element.getTag().getVR().getValidEVR();
    if(evr == EVR_OB || evr == EVR_OF || evr == EVR_OW || evr == EVR_UN)
    {
        if(position != 0)
        {
            throw Exception("Position must be 0 for binary VRs");
        }
        condition = element.getOFStringArray(value);
    }
    else
    {
         condition = element.getOFString(value, position);
    }

    return condition;
}

OFCondition
putString(DcmElement & element, OFString const value, unsigned long const position)
{
    if(position != 0)
    {
        throw Exception("Position must be 0");
    }

    return element.putOFStringArray(value);
}

#define DEFINE_ELEMENT_TRAITS(TValueType, getter_, setter_) \
template<> \
ElementTraits<TValueType>::GetterType const \
ElementTraits<TValueType>\
::getter = getter_; \
\
template<> \
ElementTraits<TValueType>::SetterType const \
ElementTraits<TValueType>\
::setter = setter_;

DEFINE_ELEMENT_TRAITS(OFString, getString, putString)
DEFINE_ELEMENT_TRAITS(Float32, &DcmElement::getFloat32, &DcmElement::putFloat32)
DEFINE_ELEMENT_TRAITS(Float64, &DcmElement::getFloat64, &DcmElement::putFloat64)
DEFINE_ELEMENT_TRAITS(Sint16, &DcmElement::getSint16, &DcmElement::putSint16)
DEFINE_ELEMENT_TRAITS(Sint32, &DcmElement::getSint32, &DcmElement::putSint32)
DEFINE_ELEMENT_TRAITS(Uint16, &DcmElement::getUint16, &DcmElement::putUint16)
DEFINE_ELEMENT_TRAITS(Uint32, &DcmElement::getUint32, &DcmElement::putUint32)

#undef DEFINE_ELEMENT_TRAITS

}
