/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/rle_lossless.h"

#include <cstdint>
#include <map>
#include <string>

#include <boost/any.hpp>

#include "odil/encapsulated_pixel_data.h"
#include "odil/DataSet.h"
#include "odil/registry.h"
#include "odil/Value.h"

namespace odil
{

namespace rle_lossless
{

Value::Binary
encode(DataSet const & data_set, std::map<std::string, boost::any> const &)
{
    Value::Binary encoded_pixel_data;
    
    // http://dicom.nema.org/medical/dicom/current/output/chtml/part05/sect_G.3.html
    
    return encoded_pixel_data;
}

Value::Binary decode(DataSet const & data_set)
{
    Value::Binary decoded_pixel_data;
    
    auto const & encoded_pixel_data = data_set.as_binary(registry::PixelData);
    for(auto const & encoded_frame: encoded_pixel_data)
    {
        // CAUTION: everything is in little-endian and thus must be swapped to
        // host order
        // http://dicom.nema.org/medical/dicom/current/output/chtml/part05/sect_G.5.html
        
        // Each frame shall be encoded in one and only one Fragment
        // http://dicom.nema.org/medical/dicom/current/output/chtml/part05/sect_A.4.2.html
        
        // Read RLE header
        // http://dicom.nema.org/medical/dicom/current/output/chtml/part05/sect_G.5.html
        uint32_t const number_of_rle_segments = 
            *reinterpret_cast<uint32_t const *>(&encoded_frame[0]);
        if(number_of_rle_segments>15)
        {
            throw Exception("Number of RLE segments too large");
        }
        
        std::vector<uint32_t> offsets(number_of_rle_segments);
        for(unsigned int i=0; i<number_of_rle_segments; ++i)
        {
            offsets[i] = 
                *reinterpret_cast<uint32_t const *>(
                    &encoded_frame[sizeof(uint32_t)*(i+1)]);
        }
        if(offsets[0] != 64)
        {
            throw Exception("Invalid offset of first RLE segment");
        }
        
        Value::Binary::value_type decoded_frame;
        for(unsigned int i=0; i<offsets.size(); ++i)
        {
            uint32_t const begin = offsets[i];
            uint32_t const end = 
                (i<offsets.size()-1)?offsets[i+1]:encoded_frame.size();
            
            // Decode segment
            // http://dicom.nema.org/medical/dicom/current/output/chtml/part05/sect_G.3.2.html
            uint32_t position=begin;
            while(position < end)
            {
                int8_t const n = encoded_frame[position];
                position += 1;
                
                if(n >= 0)
                {
                    std::copy(
                        &encoded_frame[position], &encoded_frame[position+n], 
                        std::back_inserter(decoded_frame));
                    position += n;
                }
                else if(n >= -127)
                {
                    auto const byte = encoded_frame[position];
                    Value::Binary::value_type const replicate(n, byte);
                    std::copy(
                        replicate.begin(), replicate.end(), 
                        std::back_inserter(decoded_frame));
                        
                    position += 1;
                }
                else 
                {
                    // n == -128: do nothing
                }
            }
        }
        
        decoded_pixel_data.push_back(decoded_frame);
    }
    
    return decoded_pixel_data;
}

bool register_transfer_syntax()
{
    encapsulated_pixel_data::encoders[registry::RLELossless] = encode;
    encapsulated_pixel_data::decoders[registry::RLELossless] = decode;
    return true;
}

static bool const registered=register_transfer_syntax();

}

}
