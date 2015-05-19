/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _feb2071a_de26_4adb_9305_59d0dd64c970
#define _feb2071a_de26_4adb_9305_59d0dd64c970

#include "dcmtkpp/Element.h"

#include <vector>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

template<typename T>
Element
::Element(T const & value)
: _value(value), vr()
{
    // Nothing else
}

template<typename T>
Element
::Element(T const & value, VR const & vr)
: _value(value), vr(vr)
{
    // Nothing else
}

template<typename TVisitor>
typename TVisitor::result_type
apply_visitor(TVisitor const & visitor, Element const & element)
{
    if(element.vr == VR::AE || element.vr == VR::AS || element.vr == VR::CS ||
       element.vr == VR::DA || element.vr == VR::DT || element.vr == VR::LO ||
       element.vr == VR::LT || element.vr == VR::PN || element.vr == VR::SH ||
       element.vr == VR::ST || element.vr == VR::TM || element.vr == VR::UI ||
       element.vr == VR::UT)
    {
        return visitor(element.vr, element.as_string());
    }
    else if(element.vr == VR::DS || element.vr == VR::FD || element.vr == VR::FL)
    {
        return visitor(element.vr, element.as_real());
    }
    else if(element.vr == VR::IS || element.vr == VR::SL ||
            element.vr == VR::SS || element.vr == VR::UL ||
            element.vr == VR::US)
    {
        return visitor(element.vr, element.as_int());
    }
    else if(element.vr == VR::SQ)
    {
        return visitor(element.vr, element.as_data_set());
    }
    else if(element.vr == VR::OB || element.vr == VR::OF ||
            element.vr == VR::OW || element.vr == VR::UN)
    {
        return visitor(element.vr, element.as_binary());
    }
    else
    {
        throw Exception("Unknown VR: "+as_string(element.vr));
    }
}

}

#endif // _feb2071a_de26_4adb_9305_59d0dd64c970
