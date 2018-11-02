/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/Reader.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <functional>
#include <istream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include "odil/DataSet.h"
#include "odil/Element.h"
#include "odil/endian.h"
#include "odil/Exception.h"
#include "odil/logging.h"
#include "odil/registry.h"
#include "odil/Tag.h"
#include "odil/Value.h"
#include "odil/VR.h"
#include "odil/VRFinder.h"

std::string read_string(std::istream & stream, unsigned int size)
{
    if(size == 0)
    {
        return std::string();
    }
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

Value::Binary
Reader
::read_encapsulated_pixel_data(
    std::istream & stream, ByteOrdering byte_ordering,
    std::string transfer_syntax, bool keep_group_length)
{
    Value::Binary value;

    // PS 3.5, A.4
    Reader const sequence_reader(stream, transfer_syntax, keep_group_length);

    bool done = false;
    while(!done)
    {
        auto const tag = sequence_reader.read_tag();
        auto const item_length = Reader::read_binary<uint32_t>(
            stream, byte_ordering);

        if(tag == registry::Item)
        {
            Value::Binary::value_type item_data(item_length);

            if(item_length > 0)
            {
                stream.read(
                    reinterpret_cast<char*>(&item_data[0]), item_length);
                if(!stream)
                {
                    throw Exception("Could not read from stream");
                }
            }

            value.push_back(item_data);
        }
        else if(tag == registry::SequenceDelimitationItem)
        {
            // No value for Sequence Delimitation Item
            done = true;
        }
        else
        {
            throw Exception(
                "Expected SequenceDelimitationItem, got: "+std::string(tag));
        }
    }

    return value;
}

void
Reader
::ignore(std::istream & stream, std::streamsize size)
{
    stream.ignore(size);
    if(!stream)
    {
        throw Exception("Could not read from stream");
    }
}

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

std::shared_ptr<DataSet>
Reader
::read_data_set(std::function<bool(Tag const &)> halt_condition) const
{
    auto data_set = std::make_shared<DataSet>(this->transfer_syntax);

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
                data_set->add(tag, std::move(element));
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
    auto const group = this->read_binary<uint16_t>(
        this->stream, this->byte_ordering);
    auto const element = this->read_binary<uint16_t>(
        this->stream, this->byte_ordering);
    return Tag(group, element);
}

uint32_t
Reader
::read_length(VR vr) const
{
    uint32_t length;
    if(this->explicit_vr)
    {
        // PS 3.5, 7.1.2
        if(is_binary(vr)
            || vr == VR::SQ || vr == VR::UC || vr == VR::UR || vr == VR::UT)
        {
            Reader::ignore(this->stream, 2);
            auto const vl = Reader::read_binary<uint32_t>(
                this->stream, this->byte_ordering);
            length = vl;
        }
        else
        {
            auto const vl = Reader::read_binary<uint16_t>(
                this->stream, this->byte_ordering);
            length = vl;
        }
    }
    else
    {
        auto const vl = Reader::read_binary<uint32_t>(
            this->stream, this->byte_ordering);
        length = vl;
    }

    return length;
}

Element
Reader
::read_element(Tag const & tag, std::shared_ptr<DataSet const> data_set) const
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

    std::shared_ptr<Value> value;

    auto const vl = this->read_length(vr);
    if(is_int(vr))
    {
        value = std::make_shared<Value>(Value::Integers());
    }
    else if(is_real(vr))
    {
        value = std::make_shared<Value>(Value::Reals());
    }
    else if(is_string(vr))
    {
        value = std::make_shared<Value>(Value::Strings());
    }
    else if(vr == VR::SQ)
    {
        value = std::make_shared<Value>(Value::DataSets());
    }
    else if(is_binary(vr))
    {
        value = std::make_shared<Value>(Value::Binary());
    }
    else
    {
        throw Exception("Cannot create value for VR " + as_string(vr));
    }

    if(vl > 0)
    {
        Visitor visitor(
            this->stream, vr, vl, this->transfer_syntax, this->byte_ordering,
            this->explicit_vr, this->keep_group_length);
        apply_visitor(visitor, *value);
    }

    return Element(*value, vr);
}

std::pair<std::shared_ptr<DataSet>, std::shared_ptr<DataSet>>
Reader
::read_file(
    std::istream & stream, bool keep_group_length,
    std::function<bool(Tag const &)> halt_condition)
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
    auto meta_information = meta_information_reader.read_data_set(
        [](Tag const & tag) { return (tag.group != 0x0002); });

    if(!meta_information->has(registry::TransferSyntaxUID))
    {
        throw Exception("Missing Transfer Syntax UID");
    }
    if(!meta_information->is_string(registry::TransferSyntaxUID))
    {
        throw Exception("Transfer Syntax UID is not a string");
    }
    if(meta_information->as_string(registry::TransferSyntaxUID).size()<1)
    {
        throw Exception("Empty Transfer Syntax UID");
    }

    Reader data_set_reader(
        stream, meta_information->as_string(registry::TransferSyntaxUID)[0],
        keep_group_length);
    auto data_set = data_set_reader.read_data_set(halt_condition);

    return std::make_pair(meta_information, data_set);
}

Reader::Visitor
::Visitor(
    std::istream & stream, VR vr, uint32_t vl,
    std::string const & transfer_syntax, ByteOrdering byte_ordering,
    bool explicit_vr, bool keep_group_length)
: stream(stream), vr(vr), vl(vl), transfer_syntax(transfer_syntax),
    byte_ordering(byte_ordering), explicit_vr(explicit_vr),
    keep_group_length(keep_group_length)
{
    // Nothing else
}

Reader::Visitor::result_type
Reader::Visitor
::operator()(Value::Integers & value) const
{
    if(this->vr == VR::IS)
    {
        auto const string = read_string(this->stream, this->vl);
        if(!string.empty())
        {
            auto const strings = this->split_strings(string);

            value.resize(strings.size());
            std::transform(
                strings.begin(), strings.end(), value.begin(),
                [](std::string const & s)
                {
                    long long value = 0;
                    try
                    {
                        value = std::stoll(s);
                    }
                    catch(std::invalid_argument const &)
                    {
                        ODIL_LOG(error)
                            << "Cannot convert \"" << s << "\" to IS, "
                            << "setting to 0";
                    }
                    return static_cast<Value::Integer>(value);
                });
        }
    }
    else
    {
        uint32_t items = 0;
        if(this->vr == VR::SL || this->vr == VR::UL)
        {
            items = this->vl/4;
        }
        else if(this->vr == VR::AT || this->vr == VR::SS || this->vr == VR::US)
        {
            items = this->vl/2;
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
                auto const item = Reader::read_binary<int32_t>(
                    this->stream, this->byte_ordering);
                value[i] = item;
            }
            else if(this->vr == VR::SS)
            {
                auto const item = Reader::read_binary<int16_t>(
                    this->stream, this->byte_ordering);
                value[i] = item;
            }
            else if(this->vr == VR::UL)
            {
                auto const item = Reader::read_binary<uint32_t>(
                    this->stream, this->byte_ordering);
                value[i] = item;
            }
            else if(this->vr == VR::AT || this->vr == VR::US)
            {
                auto const item = Reader::read_binary<uint16_t>(
                    this->stream, this->byte_ordering);
                value[i] = item;
            }
        }
    }
}

Reader::Visitor::result_type
Reader::Visitor
::operator()(Value::Reals & value) const
{
    if(this->vr == VR::DS)
    {
        auto const string = read_string(this->stream, this->vl);
        if(!string.empty())
        {
            auto const strings = this->split_strings(string);
            value.resize(strings.size());
            std::transform(
                strings.begin(), strings.end(), value.begin(),
                [](std::string const & s)
                {
                    long double value = 0;
                    try
                    {
                        value = std::stold(s);
                    }
                    catch(std::invalid_argument const &)
                    {
                        ODIL_LOG(error)
                            << "Cannot convert \"" << s << "\" to DS, "
                            << "setting to 0";
                    }
                    return static_cast<Value::Real>(value);
                }
            );
        }
    }
    else
    {
        uint32_t items = 0;
        if(this->vr == VR::FD)
        {
            items = this->vl/8;
        }
        else if(this->vr == VR::FL)
        {
            items = this->vl/4;
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
                auto const item = Reader::read_binary<double>(
                    this->stream, this->byte_ordering);
                value[i] = item;
            }
            else if(this->vr == VR::FL)
            {
                auto const item = Reader::read_binary<float>(
                    this->stream, this->byte_ordering);
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
        auto const string = read_string(this->stream, this->vl);
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
    if(this->vl != 0xffffffff)
    {
        // Explicit length sequence
        std::string const data = read_string(this->stream, this->vl);
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
                Reader::ignore(this->stream, 4);
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
    if(this->vl == 0)
    {
        return;
    }
    else if(this->vl == 0xffffffff)
    {
        value = Reader::read_encapsulated_pixel_data(
            this->stream, this->byte_ordering, this->transfer_syntax,
            this->keep_group_length);
    }
    else
    {
        value.resize(1);
        if(this->vr == VR::OB || this->vr == VR::UN)
        {
            value[0].resize(this->vl);
            this->stream.read(
                reinterpret_cast<char*>(&value[0][0]), value[0].size());
        }
        else if(this->vr == VR::OD)
        {
            if(this->vl%8 != 0)
            {
                throw Exception("Cannot read OD for odd-sized array");
            }

            value[0].resize(this->vl);
            for(unsigned int i=0; i<value[0].size(); i+=8)
            {
                auto const item = Reader::read_binary<double>(
                    this->stream, this->byte_ordering);
                *reinterpret_cast<double*>(&value[0][i]) = item;
            }
        }
        else if(this->vr == VR::OF)
        {
            if(this->vl%4 != 0)
            {
                throw Exception("Cannot read OF for odd-sized array");
            }

            value[0].resize(this->vl);
            for(unsigned int i=0; i<value[0].size(); i+=4)
            {
                auto const item = Reader::read_binary<float>(
                    this->stream, this->byte_ordering);
                *reinterpret_cast<float*>(&value[0][i]) = item;
            }
        }
        else if(this->vr == VR::OL)
        {
            if(this->vl%4 != 0)
            {
                throw Exception("Cannot read OL for odd-sized array");
            }

            value[0].resize(this->vl);
            for(unsigned int i=0; i<value[0].size(); i+=4)
            {
                auto const item = Reader::read_binary<uint32_t>(
                    this->stream, this->byte_ordering);
                *reinterpret_cast<uint32_t*>(&value[0][i]) = item;
            }
        }
        else if(this->vr == VR::OW)
        {
            if(this->vl%2 != 0)
            {
                throw Exception("Cannot read OW for odd-sized array");
            }

            value[0].resize(this->vl);
            for(unsigned int i=0; i<value[0].size(); i+=2)
            {
                auto const item = Reader::read_binary<uint16_t>(
                    this->stream, this->byte_ordering);
                *reinterpret_cast<uint16_t*>(&value[0][i]) = item;
            }
        }
        else
        {
            throw Exception("Cannot read "+as_string(this->vr)+" as binary");
        }
    }
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

std::shared_ptr<DataSet>
Reader::Visitor
::read_item(std::istream & specific_stream) const
{
    auto const item_length = Reader::read_binary<uint32_t>(
        specific_stream, this->byte_ordering);

    std::shared_ptr<DataSet> item;
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
        Reader::ignore(specific_stream, 4);
    }

    return item;
}

}
