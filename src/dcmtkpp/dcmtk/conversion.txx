/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _665b5269_140c_4320_94f2_ad8a7c052e9b
#define _665b5269_140c_4320_94f2_ad8a7c052e9b

#include "dcmtkpp/dcmtk/conversion.h"

#include <sstream>

#include "dcmtkpp/Element.h"
#include "dcmtkpp/dcmtk/ElementAccessor.h"

namespace dcmtkpp
{

namespace dcmtk
{

template<typename TSourceType, typename TDestinationType>
void convert(
    Element const & source, DcmElement * destination,
    TSourceType const & (Element::*getter)() const)
{
    auto const & source_values = (source.*getter)();
    for(auto i = 0; i<source_values.size(); ++i)
    {
        ElementAccessor<TDestinationType>::element_set(
            *destination, source_values[i], i);
    }
}

template<typename TSourceType>
void convert(
    Element const & source, DcmElement * destination,
    TSourceType const & (Element::*getter)() const)
{
    OFString destination_value;

    auto const & source_values = (source.*getter)();
    if(!source_values.empty())
    {
        auto const last_it = --source_values.end();
        auto it = source_values.begin();
        while(it != last_it)
        {
            std::ostringstream stream;
            stream << *it;
            destination_value += stream.str().c_str();
            destination_value += "\\";
            ++it;
        }

        std::ostringstream stream;
        stream << *last_it;
        destination_value += stream.str().c_str();
    }

    destination->putOFStringArray(destination_value);
}

template<typename TSourceType, typename TDestinationType>
void convert(
    DcmElement * source, Element & destination,
    TDestinationType & (Element::*getter)())
{
    auto & destination_values = (destination.*getter)();

    destination_values.reserve(source->getVM());

    for(auto i = 0; i<source->getVM(); ++i)
    {
        destination_values.push_back(
            ElementAccessor<TSourceType>::element_get(*source, i));
    }
}

}

}

#endif // _665b5269_140c_4320_94f2_ad8a7c052e9b
