/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/Reader.h"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <istream>
#include <sstream>
#include <string>
#include <utility>

#include "odil/DataSet.h"
#include "odil/Element.h"
#include "odil/endian.h"
#include "odil/Exception.h"
#include "odil/registry.h"
#include "odil/Tag.h"
#include "odil/Value.h"
#include "odil/VR.h"
#include "odil/VRFinder.h"

#define odil_read_binary(type, value, stream, byte_ordering, size) \
type value; \
{ \
    uint##size##_t raw; \
    stream.read(reinterpret_cast<char*>(&raw), sizeof(raw)); \
    if(!stream) \
    { \
        throw Exception("Could not read from stream"); \
    } \
    if(byte_ordering == ByteOrdering::LittleEndian) \
    { \
        raw = little_endian_to_host(raw); \
    } \
    else if(byte_ordering == ByteOrdering::BigEndian) \
    { \
        raw = big_endian_to_host(raw); \
    } \
    else \
    { \
        throw Exception("Unknown endianness"); \
    } \
    value = *reinterpret_cast<type*>(&raw);\
}

#define odil_ignore(stream, size) \
    stream.ignore(size); \
    if(!stream) \
    { \
        throw Exception("Could not read from stream"); \
    }

std::string read_string(std::istream & stream, unsigned int size)
{
    std::string value(size, '\0');
    stream.read(&value[0], value.size());
    if(!stream)
    {
        throw odil::Exception("Cannot read string");
    }
    return value;
}

namespace odil
{

Reader
::Reader(
    std::istream & stream, std::string const & transfer_syntax,
    bool keep_group_length)
: stream(stream), transfer_syntax(transfer_syntax),
    byte_ordering(
        (transfer_syntax==registry::ExplicitVRBigEndian_Retired)?
        ByteOrdering::BigEndian:ByteOrdering::LittleEndian),
    explicit_vr(transfer_syntax!=registry::ImplicitVRLittleEndian),
    keep_group_length(keep_group_length)
{
    // Nothing else
}

DataSet
Reader
::read_data_set(std::function<bool(Tag const &)> halt_condition) const
{
    DataSet data_set;

    bool done = (this->stream.peek() == EOF);
    while(!done)
    {
        Tag const tag = this->read_tag();

        if(halt_condition(tag))
        {
            done = true;
            this->stream.seekg(-4, std::ios::cur);
            break;
        }
        else
        {
            Element element = this->read_element(tag, data_set);

            if(this->keep_group_length || tag.element != 0)
            {
                data_set.add(tag, element);
            }
        }

        done = (this->stream.peek() == EOF);
    }

    return data_set;
}

Tag
Reader
::read_tag() const
{
    odil_read_binary(uint16_t, group, this->stream, this->byte_ordering, 16);
    odil_read_binary(uint16_t, element, this->stream, this->byte_ordering, 16);
    return Tag(group, element);
}

Element
Reader
::read_element(Tag const & tag, DataSet const & data_set) const
{
    VR vr;
    if(this->explicit_vr)
    {
        vr = as_vr(read_string(this->stream, 2));
    }
    else
    {
        VRFinder const vr_finder;
        vr = vr_finder(tag, data_set, this->transfer_syntax);
    }

    Value value;

    if(vr == VR::IS || vr == VR::SL || vr == VR::SS ||
        vr == VR::UL || vr == VR::US)
    {
        value = Value(Value::Integers());
    }
    else if(vr == VR::DS || vr == VR::FD || vr == VR::FL)
    {
        value = Value(Value::Reals());
    }
    else if(vr == VR::AE || vr == VR::AS || vr == VR::AT || vr == VR::CS ||
        vr == VR::DA || vr == VR::DS || vr == VR::DT || vr == VR::LO ||
        vr == VR::LT || vr == VR::PN || vr == VR::SH || vr == VR::ST ||
        vr == VR::TM || vr == VR::UC || vr == VR::UI || vr == VR::UR ||
        vr == VR::UT)
    {
        value = Value(Value::Strings());
    }
    else if(vr == VR::SQ)
    {
        value = Value(Value::DataSets());
    }
    else if(vr == VR::OB || vr == VR::OF || vr == VR::OW || vr == VR::UN)
    {
        value = Value(Value::Binary());
    }
    else
    {
        throw Exception("Cannot create value for VR " + as_string(vr));
    }

    Visitor visitor(
        this->stream, vr, this->transfer_syntax, this->byte_ordering,
        this->explicit_vr, this->keep_group_length);
    apply_visitor(visitor, value);

    return Element(value, vr);
}

std::pair<DataSet, DataSet>
Reader
::read_file(std::istream & stream, bool keep_group_length)
{
    // File preamble
    stream.ignore(128);
    if(!stream)
    {
        throw Exception("Cannot read preamble");
    }

    // DICOM prefix
    std::string const prefix = read_string(stream, 4);
    if(prefix != "DICM")
    {
        throw Exception("Unexpected prefix: \""+prefix+"\"");
    }

    // Read meta information
    Reader meta_information_reader(
        stream, registry::ExplicitVRLittleEndian, keep_group_length);
    auto const meta_information = meta_information_reader.read_data_set(
        [](Tag const & tag) { return (tag.group != 0x0002); });

    if(!meta_information.has(registry::TransferSyntaxUID))
    {
        throw Exception("Missing Transfer Syntax UID");
    }
    if(!meta_information.is_string(registry::TransferSyntaxUID))
    {
        throw Exception("Transfer Syntax UID is not a string");
    }
    if(meta_information.as_string(registry::TransferSyntaxUID).size()<1)
    {
        throw Exception("Empty Transfer Syntax UID");
    }

    Reader data_set_reader(
        stream, meta_information.as_string(registry::TransferSyntaxUID)[0],
        keep_group_length);
    auto const data_set = data_set_reader.read_data_set();

    return std::pair<DataSet, DataSet>(meta_information, data_set);
}

Reader::Visitor
::Visitor(
    std::istream & stream, VR vr, std::string const & transfer_syntax,
    ByteOrdering byte_ordering, bool explicit_vr, bool keep_group_length)
: stream(stream), vr(vr), transfer_syntax(transfer_syntax),
    byte_ordering(byte_ordering), explicit_vr(explicit_vr),
    keep_group_length(keep_group_length)
{
    // Nothing else
}

Reader::Visitor::result_type
Reader::Visitor
::operator()(Value::Integers & value) const
{
    auto const vl = this->read_length();

    if(this->vr == VR::IS)
    {
        auto const string = read_string(this->stream, vl);
        if(!string.empty())
        {
            auto const strings = this->split_strings(string);

            value.resize(strings.size());
            std::transform(
                strings.begin(), strings.end(), value.begin(),
                [](std::string const & s) { return std::stoll(s); });
        }
    }
    else
    {
        uint32_t items = 0;
        if(this->vr == VR::SL || this->vr == VR::UL)
        {
            items = vl/4;
        }
        else if(this->vr == VR::AT || this->vr == VR::SS || this->vr == VR::US)
        {
            items = vl/2;
        }
        else
        {
            throw Exception("Cannot read integers from "+as_string(this->vr));
        }

        value.resize(items);
        for(unsigned int i=0; i<items; ++i)
        {
            if(this->vr == VR::SL)
            {
                odil_read_binary(
                    int32_t, item, this->stream, this->byte_ordering, 32);
                value[i] = item;
            }
            else if(this->vr == VR::SS)
            {
                odil_read_binary(
                    int16_t, item, this->stream, this->byte_ordering, 16);
                value[i] = item;
            }
            else if(this->vr == VR::UL)
            {
                odil_read_binary(
                    uint32_t, item, this->stream, this->byte_ordering, 32);
                value[i] = item;
            }
            else if(this->vr == VR::AT || this->vr == VR::US)
            {
                odil_read_binary(
                    uint16_t, item, this->stream, this->byte_ordering, 16);
                value[i] = item;
            }
        }
    }
}

Reader::Visitor::result_type
Reader::Visitor
::operator()(Value::Reals & value) const
{
    auto const vl = this->read_length();

    if(this->vr == VR::DS)
    {
        auto const string = read_string(this->stream, vl);
        if(!string.empty())
        {
            auto const strings = this->split_strings(string);
            value.resize(strings.size());
            std::transform(
                strings.begin(), strings.end(), value.begin(),
                [](std::string const & s) { return std::stod(s); });
        }
    }
    else
    {
        uint32_t items = 0;
        if(this->vr == VR::FD)
        {
            items = vl/8;
        }
        else if(this->vr == VR::FL)
        {
            items = vl/4;
        }
        else
        {
            throw Exception("Cannot read reals from "+as_string(this->vr));
        }

        value.resize(items);
        for(unsigned int i=0; i<items; ++i)
        {
            if(this->vr == VR::FD)
            {
                odil_read_binary(
                    double, item, this->stream, this->byte_ordering, 64);
                value[i] = item;
            }
            else if(this->vr == VR::FL)
            {
                odil_read_binary(
                    float, item, this->stream, this->byte_ordering, 32);
                value[i] = item;
            }
        }
    }
}

Reader::Visitor::result_type
Reader::Visitor
::operator()(Value::Strings & value) const
{
    if(this->vr == VR::AT)
    {
        Value::Integers integers;
        this->operator()(integers);

        if(integers.size()%2 != 0)
        {
            throw Exception("Cannot read AT from odd-sized array");
        }
        for(unsigned int i=0; i<integers.size(); i+=2)
        {
            Tag const tag(integers[i], integers[i+1]);
            value.push_back(std::string(tag));
        }
    }
    else
    {
        auto const vl = this->read_length();
        auto const string = read_string(this->stream, vl);
        if(this->vr == VR::LT || this->vr == VR::ST || this->vr == VR::UT)
        {
            value = { string };
        }
        else
        {
            value = this->split_strings(string);
        }

        // Remove padding
        static std::string const padding={ '\0', ' ' };

        for(auto & item: value)
        {
            auto const last_char = item.find_last_not_of(padding);
            if(last_char != std::string::npos)
            {
                item = item.substr(0, last_char+1);
            }
        }
    }
}

Reader::Visitor::result_type
Reader::Visitor
::operator()(Value::DataSets & value) const
{
    auto const vl = this->read_length();

    if(vl != 0xffffffff)
    {
        // Explicit length sequence
        std::string const data = read_string(this->stream, vl);
        std::istringstream sequence_stream(data);
        Reader const sequence_reader(
            sequence_stream, this->transfer_syntax, this->keep_group_length);

        bool done = (sequence_stream.peek() == EOF);
        while(!done)
        {
            auto const tag = sequence_reader.read_tag();
            if(tag == registry::Item)
            {
                value.push_back(this->read_item(sequence_stream));
            }
            else
            {
                throw Exception("Expected Item, got: "+std::string(tag));
            }

            done = (sequence_stream.peek() == EOF);
        }
    }
    else
    {
        // Undefined length sequence
        Reader const sequence_reader(
            this->stream, this->transfer_syntax, this->keep_group_length);

        bool done = false;
        while(!done)
        {
            auto const tag = sequence_reader.read_tag();
            if(tag == registry::Item)
            {
                value.push_back(this->read_item(this->stream));
            }
            else if(tag == registry::SequenceDelimitationItem)
            {
                done = true;
                odil_ignore(this->stream, 4);
            }
            else
            {
                throw Exception("Expected SequenceDelimitationItem, got: "+std::string(tag));
            }
        }
    }
}

Reader::Visitor::result_type
Reader::Visitor
::operator()(Value::Binary & value) const
{
    auto const vl = this->read_length();

    if(this->vr == VR::OB)
    {
        value.resize(vl);
        this->stream.read(reinterpret_cast<char*>(&value[0]), value.size());
    }
    else if(this->vr == VR::OF)
    {
        if(vl%4 != 0)
        {
            throw Exception("Cannot read OF for odd-sized array");
        }

        value.resize(vl);
        for(unsigned int i=0; i<value.size(); i+=4)
        {
            odil_read_binary(
                float, item, this->stream, this->byte_ordering, 32);
            *reinterpret_cast<float*>(&value[i]) = item;
        }
    }
    else if(this->vr == VR::OW)
    {
        if(vl%2 != 0)
        {
            throw Exception("Cannot read OW for odd-sized array");
        }

        value.resize(vl);
        for(unsigned int i=0; i<value.size(); i+=2)
        {
            odil_read_binary(
                uint16_t, item, this->stream, this->byte_ordering, 16);
            *reinterpret_cast<uint16_t*>(&value[i]) = item;
        }
    }
    else if(this->vr == VR::UN)
    {
        value.resize(vl);
        this->stream.read(reinterpret_cast<char*>(&value[0]), value.size());
    }
    else
    {
        throw Exception("Cannot read "+as_string(this->vr)+" as binary");
    }
}

uint32_t
Reader::Visitor
::read_length() const
{
    uint32_t length;
    if(this->explicit_vr)
    {
        if(vr == VR::OB || vr == VR::OW || vr == VR::OF || vr == VR::SQ ||
           vr == VR::UC || vr == VR::UR || vr == VR::UT || vr == VR::UN)
        {
            odil_ignore(this->stream, 2);
            odil_read_binary(
                uint32_t, vl, this->stream, this->byte_ordering, 32);
            length = vl;
        }
        else
        {
            odil_read_binary(
                uint16_t, vl, this->stream, this->byte_ordering, 16);
            length = vl;
        }
    }
    else
    {
        odil_read_binary(
            uint32_t, vl, this->stream, this->byte_ordering, 32);
        length = vl;
    }

    return length;
}

Value::Strings
Reader::Visitor
::split_strings(std::string const & string) const
{
    unsigned int const items_count =
        1+std::count(string.begin(), string.end(), '\\');
    std::vector<std::string> value(items_count);

    std::string::size_type begin = 0;
    unsigned int index=0;
    while(begin != string.size())
    {
        auto const end = string.find('\\', begin);
        auto const item = string.substr(
            begin, (end==std::string::npos)?end:(end-begin));

        value[index] = item;
        ++index;

        begin = (end==std::string::npos)?string.size():(end+1);
    }

    return value;
}

DataSet
Reader::Visitor
::read_item(std::istream & specific_stream) const
{
    odil_read_binary(
        uint32_t, item_length, specific_stream, this->byte_ordering, 32);

    DataSet item;
    if(item_length != 0xffffffff)
    {
        // Explicit length item
        std::string const data = read_string(specific_stream, item_length);
        std::istringstream item_stream(data);
        Reader const item_reader(
            item_stream, this->transfer_syntax, this->keep_group_length);
        item = item_reader.read_data_set();
    }
    else
    {
        // Undefined length item
        Reader const item_reader(
            specific_stream, this->transfer_syntax, this->keep_group_length);
        item = item_reader.read_data_set(
            [](Tag const & tag) { return tag == registry::ItemDelimitationItem; });

        auto const tag = item_reader.read_tag();
        if(tag != registry::ItemDelimitationItem)
        {
            throw Exception("Unexpected tag: "+std::string(tag));
        }
        odil_ignore(specific_stream, 4);
    }

    return item;
}

}

#undef odil_ignore
#undef odil_read_binary
