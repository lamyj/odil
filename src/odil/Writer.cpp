/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/Writer.h"

#include <cmath>
#include <cstdint>
#include <cstring>
#include <map>
#include <ostream>
#include <sstream>
#include <string>

#include "odil/DataSet.h"
#include "odil/endian.h"
#include "odil/Element.h"
#include "odil/Exception.h"
#include "odil/registry.h"
#include "odil/Tag.h"
#include "odil/uid.h"
#include "odil/VR.h"
#include "odil/write_ds.h"

namespace odil
{

void
Writer
::write_encapsulated_pixel_data(
    Value::Binary const & value, std::ostream & stream,
    ByteOrdering byte_ordering, bool explicit_vr)
{
    Writer writer(stream, byte_ordering, explicit_vr);
    uint32_t length;
    for(auto const & fragment: value)
    {
        writer.write_tag(registry::Item);
        length = fragment.size();
        Writer::write_binary(length, stream, byte_ordering);
        if(length > 0)
        {
            stream.write(reinterpret_cast<char const*>(&fragment[0]), length);
            if(!stream)
            {
                throw Exception("Could not write to stream");
            }
        }
    }
    writer.write_tag(registry::SequenceDelimitationItem);
    length = 0;
    Writer::write_binary(length, stream, byte_ordering);
    if(!stream)
    {
        throw Exception("Could not write to stream");
    }
}

std::size_t
Writer
::size(odil::Tag const &, bool, ItemEncoding, bool)
{
    return 4;
}

std::size_t
Writer
::size(
    odil::VR vr, odil::Value const & value, bool explicit_vr,
    ItemEncoding item_encoding, bool use_group_length)
{
    SizeVisitor const visitor(vr, explicit_vr, item_encoding, use_group_length);
    return apply_visitor(visitor, value);
}

std::size_t
Writer
::size(
    odil::Element const & element, bool explicit_vr, ItemEncoding item_encoding,
    bool use_group_length)
{
    std::size_t const vr = explicit_vr ? 2 : 0;
    std::size_t const vl = 
        explicit_vr
        ? (
            (
                element.vr == odil::VR::OB || element.vr == odil::VR::OW
                || element.vr == odil::VR::OF || element.vr == odil::VR::SQ
                || element.vr == odil::VR::UT || element.vr == odil::VR::UN)
            ? 2+4 /* PS3.5, table 7.1-1*/
            : 2 /* PS3.5, table 7.1-2*/ )
        : 4 /* PS 3.5, table 7.1-3 */;
    
    auto const value = Writer::size(
        element.vr, element.get_value(), explicit_vr, item_encoding,
        use_group_length);
    
    return vr+vl+value;
}

std::size_t
Writer
::size(
    odil::DataSet const & data_set, bool explicit_vr,
    ItemEncoding item_encoding, bool use_group_length)
{
    std::size_t size=0;
    
    uint16_t group = 0xffff;
    for(auto && item: data_set)
    {
        auto const & tag = item.first;
        auto const & element = item.second;
        
        size += Writer::size(tag, explicit_vr, item_encoding, use_group_length);
        size += Writer::size(
            element, explicit_vr, item_encoding, use_group_length);
        
        if(tag.group != group)
        {
            group = tag.group;
            auto const write_group_length = (
                group == 0 || group == 2 ||
                (use_group_length && group != 4 && group != 6));
            if(write_group_length)
            {
                // Tag
                size += 4;
                // Value (UL)
                size += 4;
            }
        }
    }
    
    return size;
}

Writer
::Writer(
    std::ostream & stream,
    ByteOrdering byte_ordering, bool explicit_vr, ItemEncoding item_encoding,
    bool use_group_length)
: stream(stream), byte_ordering(byte_ordering), explicit_vr(explicit_vr),
    item_encoding(item_encoding), use_group_length(use_group_length)
{
    // Nothing else
}

Writer
::Writer(
    std::ostream & stream,
    std::string const & transfer_syntax,
    ItemEncoding item_encoding, bool use_group_length)
: stream(stream),
    byte_ordering(
        (transfer_syntax==registry::ExplicitVRBigEndian)?
        ByteOrdering::BigEndian:ByteOrdering::LittleEndian),
    explicit_vr(transfer_syntax!=registry::ImplicitVRLittleEndian),
    item_encoding(item_encoding), use_group_length(use_group_length)
{
    // Nothing else
}

void
Writer
::write_data_set(std::shared_ptr<DataSet const> data_set) const
{
    // Utility function checking whether the group length should be written
    auto write_group_length = [](bool use_group_length, uint16_t group) {
        // Write group length if necessary
        // Mandatory for group 0: PS3.7, 9.3, 10.3, and E.1
        // Mandatory for group 2: PS3.10, 7.1
        // Forbidden for groups 4 and 6?
        return
            group == 0 || group == 2 ||
            (use_group_length && group != 4 && group != 6);
    };
    
    // Build a map of the group lengths
    std::map<uint16_t, odil::Value::Integer> group_lengths;
    for(auto && item: *data_set)
    {
        if(write_group_length(this->use_group_length, item.first.group))
        {
            auto const size = 
                Writer::size(
                    item.first, this->explicit_vr, this->item_encoding,
                    this->use_group_length)
                + Writer::size(
                    item.second, this->explicit_vr, this->item_encoding,
                    this->use_group_length);
            group_lengths.insert({item.first.group, 0}).first->second += size;
        }
    }
    
    // Write the data set items. When a new group appears, write its group
    // length if required.
    uint16_t previous_element = 0xffff;
    for(auto && item: *data_set)
    {
        auto const & tag = item.first;
        auto const group = tag.group;
        auto const element = tag.element;
        if(
            element < previous_element
            && write_group_length(this->use_group_length, group))
        {
            // Group length: (gggg,0000) UL Type=3 VM=1
            this->write_tag(Tag(tag.group, 0));
            this->write_element(
                Element(Value::Integers({group_lengths.at(group)}), VR::UL));
        }
        previous_element = element;
        
        this->write_tag(item.first);
        this->write_element(item.second);
        
        if(!this->stream)
        {
            throw Exception("Could not write to stream");
        }
    }
}

void
Writer
::write_tag(Tag const & tag) const
{
    Writer::write_binary(tag.group, this->stream, this->byte_ordering);
    Writer::write_binary(tag.element, this->stream, this->byte_ordering);
}

void
Writer
::write_element(Element const & element) const
{
    auto const vr = element.vr;

    // Write VR
    if(this->explicit_vr)
    {
        this->stream << as_string(vr);
        if(!this->stream)
        {
            throw Exception("Could not write to stream");
        }
    }

    // Write VL
    if(this->explicit_vr)
    {
        if(vr == VR::OB || vr == VR::OD || vr == VR::OF || vr == VR::OL ||
           vr == VR::OV || vr == VR::OW || vr == VR::SQ || vr == VR::UC || 
           vr == VR::UR || vr == VR::UT || vr == VR::UN)
        {
            Writer::write_binary(
                uint16_t(0), this->stream, this->byte_ordering);

            uint32_t vl;
            if(vr == VR::SQ &&
                this->item_encoding == ItemEncoding::UndefinedLength)
            {
                vl = 0xffffffff;
            }
            else if(is_binary(vr) && element.size() > 1)
            {
                vl = 0xffffffff;
            }
            else
            {
                vl = Writer::size(
                    vr, element.get_value(), this->explicit_vr,
                    this->item_encoding, this->use_group_length);
            }
            Writer::write_binary(vl, this->stream, this->byte_ordering);
        }
        else
        {
            auto const vl = Writer::size(
                vr, element.get_value(), this->explicit_vr, this->item_encoding,
                this->use_group_length);
            Writer::write_binary(
                uint16_t(vl), this->stream, this->byte_ordering);
        }
    }
    else
    {
        auto const vl = Writer::size(
            vr, element.get_value(), this->explicit_vr, this->item_encoding,
            this->use_group_length);
        Writer::write_binary(
            uint32_t(vl), this->stream, this->byte_ordering);
    }

    if(!element.get_value().empty())
    {
        WriteVisitor const visitor(
            this->stream, vr, this->byte_ordering, this->explicit_vr,
            this->item_encoding, this->use_group_length);
        apply_visitor(visitor, element.get_value());
    }
    if(!this->stream)
    {
        throw Exception("Could not write to stream");
    }
}

void
Writer
::write_file(
    std::shared_ptr<DataSet const> data_set , std::ostream & stream,
    std::shared_ptr<DataSet const> meta_information,
    std::string const & transfer_syntax, ItemEncoding item_encoding,
    bool use_group_length)
{
    // Build File Meta Information, PS3.10, 7.1
    std::shared_ptr<DataSet> meta_info =
        meta_information?std::make_shared<DataSet>(*meta_information)
        :std::make_shared<DataSet>();
    meta_info->add(
        registry::FileMetaInformationVersion, Value::Binary({{0x00, 0x01}}));

    if(!data_set->has(registry::SOPClassUID))
    {
        throw Exception("Missing SOP Class UID");
    }
    if(!data_set->is_string(registry::SOPClassUID))
    {
        throw Exception("SOP Class UID is not a string");
    }
    if(data_set->as_string(registry::SOPClassUID).size()<1)
    {
        throw Exception("Empty SOP Class UID");
    }

    meta_info->add(
        registry::MediaStorageSOPClassUID,
        data_set->as_string(registry::SOPClassUID));

    if(!data_set->has(registry::SOPInstanceUID))
    {
        throw Exception("Missing SOP Instance UID");
    }
    if(!data_set->is_string(registry::SOPInstanceUID))
    {
        throw Exception("SOP Instance UID is not a string");
    }
    if(data_set->as_string(registry::SOPInstanceUID).size()<1)
    {
        throw Exception("Empty SOP Instance UID");
    }

    meta_info->add(registry::MediaStorageSOPInstanceUID,
        data_set->as_string(registry::SOPInstanceUID));

    meta_info->add(registry::TransferSyntaxUID, {transfer_syntax});
    meta_info->add(
        registry::ImplementationClassUID, {implementation_class_uid});
    meta_info->add(
        registry::ImplementationVersionName, { implementation_version_name });

    // Information set by input attribute 'meta_information':
    // - SourceApplicationEntityTitle
    // - SendingApplicationEntityTitle
    // - ReceivingApplicationEntityTitle

    // File preamble
    for(unsigned int i=0; i<128; ++i)
    {
        stream.put(0);
        if(!stream)
        {
            throw Exception("Could not write to stream");
        }
    }

    // DICOM prefix
    std::string const prefix("DICM");
    stream.write(&prefix[0], prefix.size());
    if(!stream)
    {
        throw Exception("Could not write to stream");
    }

    // File Meta Information
    // PS3.10, 7.1: Except for the 128 byte preamble and the 4 byte prefix, the
    // File Meta Information shall be encoded using the Explicit VR
    // Little Endian Transfer Syntax
    Writer meta_information_writer(
        stream, registry::ExplicitVRLittleEndian, item_encoding, use_group_length);
    meta_information_writer.write_data_set(meta_info);

    // Data Set
    Writer data_set_writer(
        stream, transfer_syntax, item_encoding, use_group_length);
    data_set_writer.write_data_set(data_set);
}

Writer::WriteVisitor
::WriteVisitor(
    std::ostream & stream, VR vr,
    ByteOrdering byte_ordering, bool explicit_vr, Writer::ItemEncoding item_encoding,
    bool use_group_length)
: stream(stream), vr(vr), byte_ordering(byte_ordering), explicit_vr(explicit_vr),
    item_encoding(item_encoding), use_group_length(use_group_length)
{
    // Nothing else
}

Writer::WriteVisitor::result_type
Writer::WriteVisitor
::operator()(Value::Integers const & value) const
{
    if(this->vr == VR::IS)
    {
        this->write_strings(value, ' ');
    }
    else if(this->vr == VR::SV)
    {
        for(auto item: value)
        {
            Writer::write_binary(
                int64_t(item), this->stream, this->byte_ordering);
        }
    }
    else if(this->vr == VR::SL)
    {
        for(auto item: value)
        {
            Writer::write_binary(
                int32_t(item), this->stream, this->byte_ordering);
        }
    }
    else if(this->vr == VR::SS)
    {
        for(auto item: value)
        {
            Writer::write_binary(
                int16_t(item), this->stream, this->byte_ordering);
        }
    }
    else if(this->vr == VR::UV)
    {
        for(auto item: value)
        {
            Writer::write_binary(
                uint64_t(item), this->stream, this->byte_ordering);
        }
    }
    else if(this->vr == VR::UL)
    {
        for(auto item: value)
        {
            Writer::write_binary(
                uint32_t(item), this->stream, this->byte_ordering);
        }
    }
    else if(this->vr == VR::AT || this->vr == VR::US)
    {
        for(auto item: value)
        {
            Writer::write_binary(
                uint16_t(item), this->stream, this->byte_ordering);
        }
    }
    else
    {
        throw Exception("Cannot write " + as_string(this->vr) + " as integers");
    }
}

Writer::WriteVisitor::result_type
Writer::WriteVisitor
::operator()(Value::Reals const & value) const
{
    if(this->vr == VR::DS)
    {
        int written = 0;
        for(int i=0; i<value.size(); ++i)
        {
            auto const & item = value[i];
            
            if(!std::isfinite(item))
            {
                throw Exception("DS items must be finite");
            }
            
            // Each item in the DS is at most 16 bytes, account for NUL at end
            static unsigned int const buffer_size=16+1;
            static char buffer[buffer_size];
            write_ds(item, buffer, buffer_size);
            auto const length = strlen(buffer);
            
            this->stream.write(buffer, length);
            written += length;
            if(!this->stream.good())
            {
                throw Exception("Could not write DS");
            }
            
            if(i<value.size()-1)
            {
                this->stream.put('\\');
                written += 1;
                if(!this->stream.good())
                {
                    throw Exception("Could not write DS");
                }
            }
        };
        if(written % 2 == 1)
        {
            this->stream.put(' ');
        }
        //this->write_strings(value, ' ');
    }
    else if(this->vr == VR::FD)
    {
        for(auto const & item: value)
        {
            Writer::write_binary(
                double(item), this->stream, this->byte_ordering);
        }
    }
    else if(this->vr == VR::FL)
    {
        for(auto const & item: value)
        {
            Writer::write_binary(
                float(item), this->stream, this->byte_ordering);
        }
    }
    else
    {
        throw Exception("Cannot write " + as_string(this->vr) + " as reals");
    }
}

Writer::WriteVisitor::result_type
Writer::WriteVisitor
::operator()(Value::Strings const & value) const
{
    if(this->vr == VR::AT)
    {
        Value::Integers integers;
        for(auto const & string: value)
        {
            Tag const tag(string);
            integers.push_back(tag.group);
            integers.push_back(tag.element);
        }
        this->operator()(integers);
    }
    else
    {
        this->write_strings(value, (this->vr == VR::UI)?'\0':' ');
    }
}

Writer::WriteVisitor::result_type
Writer::WriteVisitor
::operator()(Value::DataSets const & value) const
{
    Writer sequence_writer(
        this->stream, this->byte_ordering, this->explicit_vr,
        this->item_encoding, this->use_group_length);

    for(auto const & item: value)
    {
        // Beginning of item
        sequence_writer.write_tag(registry::Item);

        // Item length
        uint32_t item_length;
        if(this->item_encoding == ItemEncoding::ExplicitLength)
        {
            item_length = Writer::size(
                *item, this->explicit_vr, this->item_encoding,
                this->use_group_length);
        }
        else
        {
            item_length = 0xffffffff;
        }
        Writer::write_binary(item_length, this->stream, this->byte_ordering);

        // Data set
        sequence_writer.write_data_set(item);
        if(!this->stream)
        {
            throw Exception("Could not write to stream");
        }

        // End of item
        if(this->item_encoding == ItemEncoding::UndefinedLength)
        {
            sequence_writer.write_tag(registry::ItemDelimitationItem);
            Writer::write_binary(uint32_t(0), this->stream, this->byte_ordering);
        }
    }

    // End of sequence
    if(this->item_encoding == ItemEncoding::UndefinedLength)
    {
        sequence_writer.write_tag(registry::SequenceDelimitationItem);
        Writer::write_binary(uint32_t(0), this->stream, this->byte_ordering);
    }

    if(!this->stream)
    {
        throw Exception("Could not write to stream");
    }
}

Writer::WriteVisitor::result_type
Writer::WriteVisitor
::operator()(Value::Binary const & value) const
{
    if(value.empty())
    {
        return;
    }
    else if(value.size() > 1)
    {
        Writer::write_encapsulated_pixel_data(
            value, this->stream, this->byte_ordering, this->explicit_vr);
    }
    else
    {
        if(this->vr == VR::OB || this->vr == VR::UN)
        {
            this->stream.write(
                reinterpret_cast<char const*>(&value[0][0]), value[0].size());
        }
        else if(this->vr == VR::OW)
        {
            if(value[0].size()%2 != 0)
            {
                throw Exception("Value cannot be written as OW");
            }
            for(int i=0; i<value[0].size(); i+=2)
            {
                uint16_t item = *reinterpret_cast<uint16_t const *>(&value[0][i]);
                Writer::write_binary(item, this->stream, this->byte_ordering);
            }
        }
        else if(this->vr == VR::OF)
        {
            if(value[0].size()%4 != 0)
            {
                throw Exception("Value cannot be written as OF");
            }
            for(int i=0; i<value[0].size(); i+=4)
            {
                uint32_t item = *reinterpret_cast<uint32_t const *>(&value[0][i]);
                Writer::write_binary(item, this->stream, this->byte_ordering);
            }
        }
        else
        {
            throw Exception("Cannot write "+as_string(this->vr)+" as binary");
        }

        if(!this->stream)
        {
            throw Exception("Could not write to stream");
        }

        if(value[0].size()%2 == 1)
        {
            this->stream.put('\0');
        }
    }
}

template<typename T>
void
Writer::WriteVisitor
::write_strings(T const & sequence, char padding) const
{
    if(sequence.empty())
    {
        return;
    }

    auto const stream_begin = this->stream.tellp();

    auto last_element_it = --sequence.end();
    for(auto it = sequence.begin(); it!= sequence.end(); ++it)
    {
        this->stream << *it;
        if(!this->stream)
        {
            throw Exception("Could not write to stream");
        }

        if(it != last_element_it)
        {
            this->stream << "\\";
            if(!this->stream)
            {
                throw Exception("Could not write to stream");
            }
        }
    }

    auto const stream_end = this->stream.tellp();

    if((stream_end-stream_begin)%2 == 1)
    {
        this->stream.put(padding);
        if(!this->stream)
        {
            throw Exception("Could not write to stream");
        }
    }
}

Writer::SizeVisitor
::SizeVisitor(
    VR vr, bool explicit_vr, ItemEncoding item_encoding, bool use_group_length)
: vr(vr), explicit_vr(explicit_vr), item_encoding(item_encoding),
    use_group_length(use_group_length)
{
    // Nothing else
}

Writer::SizeVisitor::result_type
Writer::SizeVisitor
::operator()(Value::Integers const & value) const
{
    if(this->vr == VR::IS)
    {
        std::size_t size=0;
        
        // Values
        for(auto && x: value)
        {
            // IS uses a base-10 representation (PS 3.5, 6.2). For any positive
            // integer x such that 10^n <= x < 10^(n+1), n+1 digits are required
            // Since n <= log10(x) < n+1,
            size += x==0 ? 1 : (1 + int(std::log10(std::abs(x))));
            // No implicit '+' prefix is used for positive integers
            if(x<0)
            {
                ++size;
            }
        }
        
        // Separators
        if(!value.empty())
        {
            size += value.size()-1;
        }
        
        // Padding
        if(size%2 == 1)
        {
            ++size;
        }
        
        return size;
    }
    else if(this->vr == VR::SV || this->vr == VR::UV)
    {
        return 8 * value.size();
    }
    else if(this->vr == VR::SL || this->vr == VR::UL)
    {
        return 4 * value.size();
    }
    else if(this->vr == VR::SS || this->vr == VR::US)
    {
        return 2 * value.size();
    }
    else
    {
        throw Exception("Cannot size " + as_string(this->vr));
    }
}

Writer::SizeVisitor::result_type
Writer::SizeVisitor
::operator()(Value::Reals const & value) const
{
    if(this->vr == VR::DS)
    {
        std::size_t size=0;
        
        // Values: the size of the representation cannot be predicted, so we
        // need to serialize each value
        for(auto && x: value)
        {
            // Each item in the DS is at most 16 bytes (PS 3.5, 6.2), account
            // for NUL at end
            static unsigned int const buffer_size=16+1;
            static char buffer[buffer_size];
            write_ds(x, buffer, buffer_size);
            size += strlen(buffer);
        }
        
        // Separators
        if(!value.empty())
        {
            size += value.size()-1;
        }
        
        // Padding
        if(size%2 == 1)
        {
            ++size;
        }
        
        return size;
    }
    else if(this->vr == VR::FD)
    {
        return 8 * value.size();
    }
    else if(this->vr == VR::FL)
    {
        return 4 * value.size();
    }
    else
    {
        throw Exception("Cannot size " + as_string(this->vr));
    }
}

Writer::SizeVisitor::result_type
Writer::SizeVisitor
::operator()(Value::Strings const & value) const
{
    if(this->vr == odil::VR::AT)
    {
        return 4*value.size();
    }
    else
    {
        std::size_t size=0;
        
        // Values
        for(auto && x: value)
        {
            size += x.size();
        }
        
        // Separators
        if(!value.empty())
        {
            size += value.size()-1;
        }
        
        // Padding
        if(size%2 == 1)
        {
            ++size;
        }
        
        return size;
    }
}

Writer::SizeVisitor::result_type
Writer::SizeVisitor
::operator()(Value::DataSets const & value) const
{
    std::size_t size=0;
    for(auto && x: value)
    {
        // Item tag
        size += 4;
        // Length
        size += 4;
        // Value
        size += Writer::size(
            *x, this->explicit_vr, this->item_encoding, this->use_group_length);
        if(this->item_encoding == ItemEncoding::UndefinedLength)
        {
            // Item Delimitation Item tag
            size += 4;
            // "Length" of the delimitation item
            size += 4;
        }
    }
    
    if(this->item_encoding == ItemEncoding::UndefinedLength)
    {
        // Sequence Delimitation Item tag
        size += 4;
        // "Length" of the delimitation item
        size += 4;
    }
    
    return size;
}

Writer::SizeVisitor::result_type
Writer::SizeVisitor
::operator()(Value::Binary const & value) const
{
    if(value.empty())
    {
        return 0;
    }
    else if(value.size() > 1)
    {
        std::size_t size = 0;
        for(auto && fragment: value)
        {
            // Item tag
            size += 4;
            // Length
            size += 4;
            // Content
            size += fragment.size();
        }
        // Sequence Delimitation Item tag
        size += 4;
        // "Length" of the empty final element
        size += 4;
        
        return size;
    }
    else
    {
        std::size_t size = value[0].size();
        
        // Padding
        if(size%2 == 1)
        {
            ++size;
        }
        
        return size;
    }
}

}
