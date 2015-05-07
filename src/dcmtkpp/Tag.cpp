/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/Tag.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdicent.h>
#include <dcmtk/dcmdata/dcdict.h>
#include <dcmtk/dcmdata/dctagkey.h>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

Tag
::Tag(uint16_t group, uint16_t element)
: group(group), element(element)
{
    // Nothing else
}

Tag
::Tag(uint32_t tag)
: group(tag >> 16), element(tag & 0xffff)
{
    // Nothing else
}

Tag
::Tag(std::string const & name)
{
    DcmDictEntry const * entry = dcmDataDict.rdlock().findEntry(name.c_str());
    if(entry == NULL)
    {
        throw Exception("No such element: "+name);
    }

    DcmTagKey const tag = entry->getKey();
    this->group = tag.getGroup();
    this->element = tag.getElement();
}

Tag
::Tag(char const * name)
{
    DcmDictEntry const * entry = dcmDataDict.rdlock().findEntry(name);
    if(entry == NULL)
    {
        throw Exception(std::string("No such element: ")+name);
    }

    DcmTagKey const tag = entry->getKey();
    this->group = tag.getGroup();
    this->element = tag.getElement();
}

std::string
Tag
::get_name() const
{
    DcmTagKey const tag(this->group, this->element);
    DcmDictEntry const * entry = dcmDataDict.rdlock().findEntry(tag, NULL);
    if(entry == NULL)
    {
        throw Exception("No such element");
    }

    return entry->getTagName();
}

}
