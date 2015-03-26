/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/ElementAccessor.h"

namespace dcmtkpp
{

#define DEFINE_ELEMENT_ACCESSOR(vr, getter, setter) \
template<> ElementAccessor<vr>::GetterType const ElementAccessor<vr>::element_get = getter<vr>; \
template<> ElementAccessor<vr>::SetterType const ElementAccessor<vr>::element_set = setter<vr>;

DEFINE_ELEMENT_ACCESSOR(EVR_AE, get_string, set_string)
DEFINE_ELEMENT_ACCESSOR(EVR_AS, get_string, set_string)
//DEFINE_ELEMENT_ACCESSOR(EVR_AT
DEFINE_ELEMENT_ACCESSOR(EVR_CS, get_string, set_string)
DEFINE_ELEMENT_ACCESSOR(EVR_DA, get_string, set_string)
DEFINE_ELEMENT_ACCESSOR(EVR_DS, get_default, set_default)
DEFINE_ELEMENT_ACCESSOR(EVR_DT, get_string, set_string)
DEFINE_ELEMENT_ACCESSOR(EVR_FD, get_default, set_default)
DEFINE_ELEMENT_ACCESSOR(EVR_FL, get_default, set_default)
DEFINE_ELEMENT_ACCESSOR(EVR_IS, get_default, set_default)
DEFINE_ELEMENT_ACCESSOR(EVR_LO, get_string, set_string)
DEFINE_ELEMENT_ACCESSOR(EVR_LT, get_string, set_string)
//DEFINE_ELEMENT_ACCESSOR(EVR_OB
//DEFINE_ELEMENT_ACCESSOR(EVR_OF
//DEFINE_ELEMENT_ACCESSOR(EVR_OW
DEFINE_ELEMENT_ACCESSOR(EVR_PN, get_string, set_string)
DEFINE_ELEMENT_ACCESSOR(EVR_SH, get_string, set_string)
DEFINE_ELEMENT_ACCESSOR(EVR_SL, get_default, set_default)
//DEFINE_ELEMENT_ACCESSOR(EVR_SQ
DEFINE_ELEMENT_ACCESSOR(EVR_SS, get_default, set_default)
DEFINE_ELEMENT_ACCESSOR(EVR_ST, get_string, set_string)
DEFINE_ELEMENT_ACCESSOR(EVR_TM, get_string, set_string)
DEFINE_ELEMENT_ACCESSOR(EVR_UI, get_string, set_string)
//DEFINE_ELEMENT_ACCESSOR(EVR_UN
DEFINE_ELEMENT_ACCESSOR(EVR_UL, get_default, set_default)
DEFINE_ELEMENT_ACCESSOR(EVR_US, get_default, set_default)
DEFINE_ELEMENT_ACCESSOR(EVR_UT, get_string, set_string)

#undef DEFINE_ELEMENT_ACCESSOR

}
