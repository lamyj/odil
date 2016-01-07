/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/dcmtk/ElementAccessor.h"

#include <string>
#include <vector>

namespace dcmtkpp
{

namespace dcmtk
{

#define DEFINE_ELEMENT_ACCESSOR(TValueType, getter, setter) \
template<> \
ElementAccessor<TValueType>::GetterType const \
ElementAccessor<TValueType>\
::element_get = getter<TValueType>; \
\
template<> \
ElementAccessor<TValueType>::SetterType const \
ElementAccessor<TValueType>\
::element_set = setter<TValueType>;

DEFINE_ELEMENT_ACCESSOR(std::string, get_string, set_string)
DEFINE_ELEMENT_ACCESSOR(std::vector<uint8_t>, get_binary, set_binary)
DEFINE_ELEMENT_ACCESSOR(Float32, get_default, set_default)
DEFINE_ELEMENT_ACCESSOR(Float64, get_default, set_default)
DEFINE_ELEMENT_ACCESSOR(Sint16, get_default, set_default)
DEFINE_ELEMENT_ACCESSOR(Sint32, get_default, set_default)
DEFINE_ELEMENT_ACCESSOR(Uint16, get_default, set_default)
DEFINE_ELEMENT_ACCESSOR(Uint32, get_default, set_default)

#undef DEFINE_ELEMENT_ACCESSOR

}

}
