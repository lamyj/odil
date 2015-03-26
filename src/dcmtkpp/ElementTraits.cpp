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
    return element.getOFString(value, position);
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

#define DEFINE_ELEMENT_TRAITS(vr, getter_, setter_) \
ElementTraits<vr>::GetterType const ElementTraits<vr>::getter = getter_; \
ElementTraits<vr>::SetterType const ElementTraits<vr>::setter = setter_;

DEFINE_ELEMENT_TRAITS(EVR_AE, getString, putString)
DEFINE_ELEMENT_TRAITS(EVR_AS, getString, putString)
//DEFINE_ELEMENT_TRAITS(EVR_AT
DEFINE_ELEMENT_TRAITS(EVR_CS, getString, putString)
DEFINE_ELEMENT_TRAITS(EVR_DA, getString, putString)
DEFINE_ELEMENT_TRAITS(EVR_DS, &DcmElement::getFloat64, &DcmElement::putFloat64)
DEFINE_ELEMENT_TRAITS(EVR_DT, getString, putString)
DEFINE_ELEMENT_TRAITS(EVR_FD, &DcmElement::getFloat64, &DcmElement::putFloat64)
DEFINE_ELEMENT_TRAITS(EVR_FL, &DcmElement::getFloat32, &DcmElement::putFloat32)
DEFINE_ELEMENT_TRAITS(EVR_IS, &DcmElement::getSint32, &DcmElement::putSint32)
DEFINE_ELEMENT_TRAITS(EVR_LO, getString, putString)
DEFINE_ELEMENT_TRAITS(EVR_LT, getString, putString)
//DEFINE_ELEMENT_TRAITS(EVR_OB
//DEFINE_ELEMENT_TRAITS(EVR_OF
//DEFINE_ELEMENT_TRAITS(EVR_OW
DEFINE_ELEMENT_TRAITS(EVR_PN, getString, putString)
DEFINE_ELEMENT_TRAITS(EVR_SH, getString, putString)
DEFINE_ELEMENT_TRAITS(EVR_SL, &DcmElement::getSint32, &DcmElement::putSint32)
//DEFINE_ELEMENT_TRAITS(EVR_SQ
DEFINE_ELEMENT_TRAITS(EVR_SS, &DcmElement::getSint16, &DcmElement::putSint16)
DEFINE_ELEMENT_TRAITS(EVR_ST, getString, putString)
DEFINE_ELEMENT_TRAITS(EVR_TM, getString, putString)
DEFINE_ELEMENT_TRAITS(EVR_UI, getString, putString)
DEFINE_ELEMENT_TRAITS(EVR_UL, &DcmElement::getUint32, &DcmElement::putUint32)
//DEFINE_ELEMENT_TRAITS(EVR_UN
DEFINE_ELEMENT_TRAITS(EVR_US, &DcmElement::getUint16, &DcmElement::putUint16)
DEFINE_ELEMENT_TRAITS(EVR_UT, getString, putString)

#undef DEFINE_ELEMENT_TRAITS

}
