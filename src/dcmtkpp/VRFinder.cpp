/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/VRFinder.h"

#include <functional>
#include <string>
#include <vector>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Tag.h"
#include "dcmtkpp/VR.h"

namespace dcmtkpp
{

std::vector<VRFinder::Finder> const
VRFinder
::default_finders=VRFinder::_get_default_finders();

VRFinder
::VRFinder()
: finders()
{
    // Nothing else
}

VR
VRFinder::operator()(
    Tag const & tag, DataSet const & data_set,
    std::string const & transfer_syntax) const
{
    VR vr = VR::UNKNOWN;

    for(auto const & finder: this->finders)
    {
        try
        {
            vr = finder(tag, data_set, transfer_syntax);
            break;
        }
        catch(Exception &)
        {
            // Ignore the error, try the next one
        }
    }

    if(vr == VR::UNKNOWN)
    {
        for(auto const & finder: VRFinder::default_finders)
        {
            try
            {
                vr = finder(tag, data_set, transfer_syntax);
                break;
            }
            catch(Exception &)
            {
                // Ignore the error, try the next one
            }
        }
    }

    if(vr == VR::UNKNOWN)
    {
        throw Exception("Could not find a VR for "+std::string(tag));
    }

    return vr;
}

VR
VRFinder
::public_dictionary(
    Tag const & tag, DataSet const &, std::string const &)
{
    auto const it = registry::public_dictionary.find(tag);
    if(it == registry::public_dictionary.end())
    {
        throw Exception("Element " + std::string(tag) + " is not in the public dictionary");
    }
    return as_vr(it->second.vr);
}

VR
VRFinder
::group_length(
    Tag const & tag, DataSet const &, std::string const &)
{
    if(tag.element == 0)
    {
        return VR::UL;
    }
    else
    {
        throw Exception("Not a group length tag");
    }
}

VR
VRFinder
::private_tag(
    Tag const & tag, DataSet const &, std::string const &)
{
    if(tag.group %2 == 1)
    {
        return VR::UN;
    }
    else
    {
        throw Exception("Not a private tag");
    }
}

VR
VRFinder
::implicit_vr_little_endian(
    Tag const & tag, DataSet const & data_set,
    std::string const & transfer_syntax)
{
    if(transfer_syntax == registry::ImplicitVRLittleEndian)
    {
        // PS3.5, A.1 (c)
        if(tag == registry::PixelData)
        {
            return VR::OW;
        }
        else if((tag.group<<8) == 0x60 && tag.element == 0x3000)
        {
            return VR::OW;
        }
        else if(tag == registry::WaveformData)
        {
            return VR::OW;
        }
        else if(tag == registry::RedPaletteColorLookupTableData ||
            tag == registry::GreenPaletteColorLookupTableData ||
            tag == registry::BluePaletteColorLookupTableData ||
            tag == registry::AlphaPaletteColorLookupTableData)
        {
            return VR::OW;
        }
        // {Red,Green,Blue,Alpha}PaletteColorLookupTableDescriptor
        else if(tag == registry::SegmentedRedPaletteColorLookupTableData ||
            tag == registry::SegmentedGreenPaletteColorLookupTableData ||
            tag == registry::SegmentedBluePaletteColorLookupTableData)
        {
            return VR::OW;
        }
        // LUTData
        // LUTDescriptor
        else if(tag == registry::BlendingLookupTableData)
        {
            return VR::OW;
        }
        else if(tag == registry::VertexPointIndexList ||
            tag == registry::EdgePointIndexList ||
            tag == registry::TrianglePointIndexList ||
            tag == registry::PrimitivePointIndexList)
        {
            return VR::OW;
        }
        else if(tag == registry::SmallestImagePixelValue ||
            tag == registry::LargestImagePixelValue ||
            tag == registry::SmallestPixelValueInSeries ||
            tag == registry::LargestPixelValueInSeries ||
            tag == registry::PixelPaddingValue)
        {
            return VR::US;
        }
        else
        {
            throw Exception("Unknown tag");
        }
    }
    else
    {
        throw Exception("Unknown transfer syntax");
    }
}

std::vector<VRFinder::Finder>
VRFinder
::_get_default_finders()
{
    return {
        group_length, private_tag, implicit_vr_little_endian,
        public_dictionary };
}

}
