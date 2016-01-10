/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _feb2071a_de26_4adb_9305_59d0dd64c970
#define _feb2071a_de26_4adb_9305_59d0dd64c970

#include "odil/Element.h"

#include <vector>

#include "odil/Exception.h"

namespace odil
{

template<typename TVisitor>
typename TVisitor::result_type
apply_visitor(TVisitor const & visitor, Element const & element)
{
    if(element.empty())
    {
        return visitor(element.vr);
    }
    else if(is_string(element.vr))
    {
        return visitor(element.vr, element.as_string());
    }
    else if(is_real(element.vr))
    {
        return visitor(element.vr, element.as_real());
    }
    else if(is_int(element.vr))
    {
        return visitor(element.vr, element.as_int());
    }
    else if(element.vr == VR::SQ)
    {
        return visitor(element.vr, element.as_data_set());
    }
    else if(is_binary(element.vr))
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
