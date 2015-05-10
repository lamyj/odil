/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/conversion.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Element.h"
#include "dcmtkpp/Tag.h"

namespace dcmtkpp
{

DcmTagKey convert(Tag const & tag)
{
    return DcmTagKey(tag.group, tag.element);
}

Tag convert(DcmTagKey const & tag)
{
    return Tag(tag.getGroup(), tag.getElement());
}

DcmElement * convert(const Tag & tag, Element const & source)
{
    DcmTagKey const destination_tag = convert(tag);

    DcmElement * destination = NULL;
    if(source.vr == dcmtkpp::VR::AE)
    {
        destination = new DcmApplicationEntity(destination_tag);
    }
    else if (source.vr == dcmtkpp::VR::AS)
    {
        destination = new DcmAgeString(destination_tag);
    }

    return destination;
}

Element convert(DcmElement * source)
{
    Element destination;

    DcmEVR const source_vr = source->getTag().getVR().getValidEVR();

    if(source_vr == EVR_AE)
    {
        destination.vr = VR::AE;
    }
    else if(source_vr == EVR_AS)
    {
        destination.vr = VR::AS;
    }

    return destination;
}

DcmDataset convert(DataSet const & source)
{
    DcmDataset destination;

    for(auto const & iterator: source)
    {
        DcmElement * destination_element = convert(iterator.first, iterator.second);
        destination.insert(destination_element);
    }

    return destination;
}

DataSet convert(DcmDataset const & source)
{
    DataSet destination;

    for(unsigned long i=0; i<source.card(); ++i)
    {
        DcmElement * source_element = const_cast<DcmDataset &>(source).getElement(i);
        Element const destination_element = convert(source_element);
        // TODO
    }
    return destination;
}

}
