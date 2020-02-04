/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/VRFinder.h"

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

#include "odil/DataSet.h"
#include "odil/ElementsDictionary.h"
#include "odil/Exception.h"
#include "odil/logging.h"
#include "odil/registry.h"
#include "odil/Tag.h"
#include "odil/VR.h"

namespace odil
{

std::vector<VRFinder::Finder> const
VRFinder
::default_finders=VRFinder::_get_default_finders();

VRFinder
::VRFinder(bool strict)
: finders(), strict(strict)
{
    // Nothing else
}

VR
VRFinder::operator()(
    Tag const & tag, std::shared_ptr<DataSet const> data_set,
    std::string const & transfer_syntax) const
{
    VR vr = VR::UNKNOWN;

    for(auto const & finder: this->finders)
    {
        try
        {
            vr = finder(tag, data_set, transfer_syntax);
            if (vr != VR::UNKNOWN)
            {
                break;
            }
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
                if (vr != VR::UNKNOWN)
                {
                    break;
                }
            }
            catch(Exception &)
            {
                // Ignore the error, try the next one
            }
        }
    }
    
    if(vr == VR::UNKNOWN)
    {
        if(this->strict)
        {
            throw Exception("Could not find a VR for "+std::string(tag));
        }
        else
        {
            ODIL_LOG(info) << "No known VR for " << tag << ", defaulting to UN";
            vr = VR::UN;
        }
    }

    return vr;
}

VR
VRFinder
::public_dictionary(
    Tag const & tag, std::shared_ptr<DataSet const>, std::string const &)
{
    VR vr = VR::UNKNOWN;
    
    auto const iterator = find(registry::public_dictionary, tag);
    if(iterator != registry::public_dictionary.end())
    {
        vr = as_vr(iterator->second.vr);
    }

    return vr;
}

VR
VRFinder
::group_length(
    Tag const & tag, std::shared_ptr<DataSet const>, std::string const &)
{
    if(tag.element == 0)
    {
        return VR::UL;
    }
  
    return VR::UNKNOWN; // Not a group length tag
}

VR
VRFinder
::private_tag(
    Tag const & tag, std::shared_ptr<DataSet const>, std::string const &)
{
    if(tag.group %2 == 1)
    {
        return VR::UN;
    }

    return VR::UNKNOWN; // Not a private tag
}

VR
VRFinder
::implicit_vr_little_endian(
    Tag const & tag, std::shared_ptr<DataSet const> data_set,
    std::string const & transfer_syntax)
{
    if(transfer_syntax == registry::ImplicitVRLittleEndian)
    {
        // PS3.5, A.1 (c)
        if(tag == registry::PixelData)
        {
            return VR::OW;
        }
        else if((tag.group>>8) == 0x60 && tag.element == 0x3000)
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
        else if(tag == registry::RedPaletteColorLookupTableDescriptor ||
            tag == registry::GreenPaletteColorLookupTableDescriptor ||
            tag == registry::BluePaletteColorLookupTableDescriptor)
        {
            // PS 3.3, C.7.6.3.1.5, note 2
            if(!data_set->has(registry::PixelRepresentation))
            {
                throw Exception("Cannot find VR without PixelRepresentation");
            }
            auto const & pixel_representation = 
                data_set->as_int(registry::PixelRepresentation)[0];
            return (pixel_representation==0)?(VR::US):(VR::SS);
        }
        else if(tag == registry::SegmentedRedPaletteColorLookupTableData ||
            tag == registry::SegmentedGreenPaletteColorLookupTableData ||
            tag == registry::SegmentedBluePaletteColorLookupTableData)
        {
            return VR::OW;
        }
        else if(tag == registry::LUTData)
        {
            return VR::OW;
        }
        else if(tag == registry::LUTDescriptor)
        {
            // - PS 3.3, C.11.1.1.1: may be heterogeneous, depends on 
            //   Pixel Representation
            // - PS 3.3, C.11.2.1.1: may be heterogeneous, depends on 
            //   Pixel Representation, Rescale Slope and Rescale Intercept
            // - C.11.4.1: always US
            // - C.11.6.1.1: always US
            // FIXME This is too context-dependent
            return VR::UN;
        }
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
            if(!data_set->has(registry::PixelRepresentation))
            {
                throw Exception("Cannot find VR without PixelRepresentation");
            }
            auto const & pixel_representation = 
                data_set->as_int(registry::PixelRepresentation)[0];
            return (pixel_representation==0)?(VR::US):(VR::SS);
        }
        else
        {
            // Unknown tag
            return VR::UNKNOWN;
        }
    }
    else
    {
        // Unknown transfer syntax
        return VR::UNKNOWN;
    }
}

VR
VRFinder
::explicit_vr_little_endian(
    Tag const & tag, std::shared_ptr<DataSet const> data_set,
    std::string const & transfer_syntax)
{
    if(transfer_syntax == registry::ExplicitVRLittleEndian)
    {
        // PS3.5, A.1 (c)
        if(tag == registry::PixelData)
        {
            if(!data_set->has(registry::BitsAllocated))
            {
                throw Exception("Cannot find VR without BitsAllocated");
            }
            auto const & bits_allocated = 
                data_set->as_int(registry::BitsAllocated)[0];
            return (bits_allocated<=8)?(VR::OB):(VR::OW);
        }
        else if((tag.group>>8) == 0x60 && tag.element == 0x3000)
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
        else if(tag == registry::RedPaletteColorLookupTableDescriptor ||
            tag == registry::GreenPaletteColorLookupTableDescriptor ||
            tag == registry::BluePaletteColorLookupTableDescriptor)
        {
            // PS 3.3, C.7.6.3.1.5, note 2
            if(!data_set->has(registry::PixelRepresentation))
            {
                throw Exception("Cannot find VR without PixelRepresentation");
            }
            auto const & pixel_representation = 
                data_set->as_int(registry::PixelRepresentation)[0];
            return (pixel_representation==0)?(VR::US):(VR::SS);
        }
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
            if(!data_set->has(registry::PixelRepresentation))
            {
                throw Exception("Cannot find VR without PixelRepresentation");
            }
            auto const & pixel_representation = 
                data_set->as_int(registry::PixelRepresentation)[0];
            return (pixel_representation==0)?(VR::US):(VR::SS);
        }
        else
        {
            // Unknown tag
            return VR::UNKNOWN;
        }
    }
    else
    {
        // Unknown transfer syntax
        return VR::UNKNOWN;
    }
}

std::vector<VRFinder::Finder>
VRFinder
::_get_default_finders()
{
    return {
        group_length, private_tag, implicit_vr_little_endian,
        explicit_vr_little_endian, public_dictionary };
}

}
