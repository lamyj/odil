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

}

#endif // _feb2071a_de26_4adb_9305_59d0dd64c970
