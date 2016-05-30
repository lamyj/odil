/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/encapsulated_pixel_data.h"

#include <functional>
#include <map>
#include <string>

#include <boost/any.hpp>

#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/Value.h"

namespace odil
{

namespace encapsulated_pixel_data
{
    
std::map<std::string, Encoder> encoders=std::map<std::string, Encoder>();
std::map<std::string, Decoder> decoders=std::map<std::string, Decoder>();

Value::Binary 
encode(
    DataSet const & data_set, std::string const & transfer_syntax, 
    std::map<std::string, boost::any> const & parameters)
{
    auto const encoder_it = encoders.find(transfer_syntax);
    if(encoder_it == encoders.end())
    {
        throw Exception("No encoder registered for "+transfer_syntax);
    }
    
    return encoder_it->second(data_set, parameters);
}

Value::Binary
decode(DataSet const & data_set, std::string const & transfer_syntax)
{
    auto const decoder_it = decoders.find(transfer_syntax);
    if(decoder_it == decoders.end())
    {
        throw Exception("No decoder registered for "+transfer_syntax);
    }
    
    return decoder_it->second(data_set);
}

}

}
