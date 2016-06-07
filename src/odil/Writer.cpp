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

#define odil_write_binary(value, stream, byte_ordering, size) \
{ \
    auto raw = value; \
    if(byte_ordering == ByteOrdering::LittleEndian) \
    { \
        raw = host_to_little_endian(raw); \
    } \
    else if(byte_ordering == ByteOrdering::BigEndian) \
    { \
        raw = host_to_big_endian(raw); \
    } \
    else \
    { \
        throw Exception("Unknown endianness"); \
    } \
    stream.write(reinterpret_cast<char const*>(&raw), sizeof(raw)); \
    if(!stream) \
    { \
        throw Exception("Could not write to stream"); \
    } \
}

namespace odil
{

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
        (transfer_syntax==registry::ExplicitVRBigEndian_Retired)?
        ByteOrdering::BigEndian:ByteOrdering::LittleEndian),
    explicit_vr(transfer_syntax!=registry::ImplicitVRLittleEndian),
    item_encoding(item_encoding), use_group_length(use_group_length)
{
    // Nothing else
}

void
Writer
::write_data_set(DataSet const & data_set) const
{
    // Build a map of the different group in order to handle
    // Group Length elements
    std::map<uint16_t, std::vector<Tag>> groups;
    for(auto const & item: data_set)
    {
        auto const & tag = item.first;
        groups[tag.group].push_back(tag);
    }

    for(auto const & groups_it: groups)
    {
        std::ostringstream group_stream;
        Writer group_writer(
            group_stream, this->byte_ordering, this->explicit_vr,
            this->item_encoding, this->use_group_length);

        for(auto const & tag: groups_it.second)
        {
            group_writer.write_tag(tag);
            group_writer.write_element(data_set[tag]);
        }

        // Write group length if necessary
        // Mandatory for group 0: PS3.7, 9.3, 10.3, and E.1
        // Mandatory for group 2: PS3.10, 7.1
        // Forbidden for groups 4 and 6?
        auto const write_group_length = (
            groups_it.first == 0 || groups_it.first == 2 ||
            (this->use_group_length && groups_it.first != 4 && groups_it.first != 6));
        if(write_group_length)
        {
            // Group length: (gggg,0000) UL Type=3 VM=1
            this->write_tag(Tag(groups_it.first, 0));
            this->write_element(
                Element(Value::Integers({group_stream.tellp()}), VR::UL));
        }

        // Write group data to main stream
        std::string const group_data = group_stream.str();
        this->stream.write(&group_data[0], group_data.size());
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
    odil_write_binary(tag.group, this->stream, this->byte_ordering, 16);
    odil_write_binary(tag.element, this->stream, this->byte_ordering, 16);
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

    // Write value to a sub-stream
    std::ostringstream value_stream;
    if(!element.get_value().empty())
    {
        Visitor const visitor(
            value_stream, vr, this->byte_ordering, this->explicit_vr,
            this->item_encoding, this->use_group_length);
        apply_visitor(visitor, element.get_value());
    }

    // Write VL
    if(this->explicit_vr)
    {
        if(vr == VR::OB || vr == VR::OW || vr == VR::OF || vr == VR::SQ ||
           vr == VR::UC || vr == VR::UR || vr == VR::UT || vr == VR::UN)
        {
            odil_write_binary(uint16_t(0), this->stream, this->byte_ordering, 16);

            uint32_t vl;
            if(vr == VR::SQ &&
                this->item_encoding == ItemEncoding::UndefinedLength)
            {
                vl = 0xffffffff;
            }
            else if((vr == VR::OB || vr == VR::OW) && element.size() > 1)
            {
                vl = 0xffffffff;
            }
            else
            {
               vl = value_stream.tellp();
            }
            odil_write_binary(vl, this->stream, this->byte_ordering, 32);
        }
        else
        {
            odil_write_binary(uint16_t(value_stream.tellp()), this->stream, this->byte_ordering, 16);
        }
    }
    else
    {
        odil_write_binary(uint32_t(value_stream.tellp()), this->stream, this->byte_ordering, 32);
    }

    this->stream.write(value_stream.str().c_str(), value_stream.tellp());
    if(!this->stream)
    {
        throw Exception("Could not write to stream");
    }
}

void
Writer
::write_file(DataSet const &data_set , std::ostream & stream,
             odil::DataSet const & meta_information,
             std::string const & transfer_syntax, ItemEncoding item_encoding,
             bool use_group_length)
{
    // Build File Meta Information, PS3.10, 7.1
    DataSet meta_info = meta_information;
    meta_info.add(
        registry::FileMetaInformationVersion, Value::Binary({{0x00, 0x01}}));

    if(!data_set.has(registry::SOPClassUID))
    {
        throw Exception("Missing SOP Class UID");
    }
    if(!data_set.is_string(registry::SOPClassUID))
    {
        throw Exception("SOP Class UID is not a string");
    }
    if(data_set.as_string(registry::SOPClassUID).size()<1)
    {
        throw Exception("Empty SOP Class UID");
    }

    meta_info.add(
        registry::MediaStorageSOPClassUID,
        data_set.as_string(registry::SOPClassUID));

    if(!data_set.has(registry::SOPInstanceUID))
    {
        throw Exception("Missing SOP Instance UID");
    }
    if(!data_set.is_string(registry::SOPInstanceUID))
    {
        throw Exception("SOP Instance UID is not a string");
    }
    if(data_set.as_string(registry::SOPInstanceUID).size()<1)
    {
        throw Exception("Empty SOP Instance UID");
    }

    meta_info.add(registry::MediaStorageSOPInstanceUID,
        data_set.as_string(registry::SOPInstanceUID));

    meta_info.add(registry::TransferSyntaxUID, {transfer_syntax});
    meta_info.add(
        registry::ImplementationClassUID, {implementation_class_uid});
    meta_info.add(
        registry::ImplementationVersionName, { implementation_version_name });

    // Information set by input attribut 'meta_information':
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

Writer::Visitor
::Visitor(
    std::ostream & stream, VR vr,
    ByteOrdering byte_ordering, bool explicit_vr, Writer::ItemEncoding item_encoding,
    bool use_group_length)
: stream(stream), vr(vr), byte_ordering(byte_ordering), explicit_vr(explicit_vr),
    item_encoding(item_encoding), use_group_length(use_group_length)
{
    // Nothing else
}

Writer::Visitor::result_type
Writer::Visitor
::operator()(Value::Integers const & value) const
{
    if(this->vr == VR::IS)
    {
        this->write_strings(value, ' ');
    }
    else if(this->vr == VR::SL)
    {
        for(auto item: value)
        {
            odil_write_binary(
                int32_t(item), this->stream, this->byte_ordering, 32);
        }
    }
    else if(this->vr == VR::SS)
    {
        for(auto item: value)
        {
            odil_write_binary(
                int16_t(item), this->stream, this->byte_ordering, 16);
        }
    }
    else if(this->vr == VR::UL)
    {
        for(auto item: value)
        {
            odil_write_binary(
                uint32_t(item), this->stream, this->byte_ordering, 32);
        }
    }
    else if(this->vr == VR::AT || this->vr == VR::US)
    {
        for(auto item: value)
        {
            odil_write_binary(
                uint16_t(item), this->stream, this->byte_ordering, 16);
        }
    }
    else
    {
        throw Exception("Cannot write " + as_string(this->vr) + " as integers");
    }
}

Writer::Visitor::result_type
Writer::Visitor
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
            
            // Each item in the DS is at most 16 bytes.
            static char buffer[16];
            write_ds(item, buffer, 16);
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
            odil_write_binary(
                double(item), this->stream, this->byte_ordering, 64);
        }
    }
    else if(this->vr == VR::FL)
    {
        for(auto const & item: value)
        {
            odil_write_binary(
                float(item), this->stream, this->byte_ordering, 32);
        }
    }
    else
    {
        throw Exception("Cannot write " + as_string(this->vr) + " as reals");
    }
}

Writer::Visitor::result_type
Writer::Visitor
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

Writer::Visitor::result_type
Writer::Visitor
::operator()(Value::DataSets const & value) const
{
    // Write all items to a sub-stream
    std::ostringstream sequence_stream;
    Writer sequence_writer(
        sequence_stream, this->byte_ordering, this->explicit_vr,
        this->item_encoding, this->use_group_length);

    for(auto const & item: value)
    {
        // Write item to a sub-stream
        std::ostringstream item_stream;
        Writer item_writer(
            item_stream, this->byte_ordering, this->explicit_vr,
            this->item_encoding, this->use_group_length);
        item_writer.write_data_set(item);

        // Beginning of item
        sequence_writer.write_tag(registry::Item);

        // Item length
        uint32_t item_length;
        if(this->item_encoding == ItemEncoding::ExplicitLength)
        {
            item_length = item_stream.tellp();
        }
        else
        {
            item_length = 0xffffffff;
        }
        odil_write_binary(item_length, sequence_stream, this->byte_ordering, 32);

        // Data set
        sequence_stream.write(item_stream.str().c_str(), item_stream.tellp());
        if(!sequence_stream)
        {
            throw Exception("Could not write to stream");
        }

        // End of item
        if(this->item_encoding == ItemEncoding::UndefinedLength)
        {
            sequence_writer.write_tag(registry::ItemDelimitationItem);
            odil_write_binary(uint32_t(0), sequence_stream, this->byte_ordering, 32);
        }
    }

    // End of sequence
    if(this->item_encoding == ItemEncoding::UndefinedLength)
    {
        sequence_writer.write_tag(registry::SequenceDelimitationItem);
        odil_write_binary(uint32_t(0), sequence_stream, this->byte_ordering, 32);
    }

    this->stream.write(sequence_stream.str().c_str(), sequence_stream.tellp());
    if(!this->stream)
    {
        throw Exception("Could not write to stream");
    }
}

Writer::Visitor::result_type
Writer::Visitor
::operator()(Value::Binary const & value) const
{
    if(value.empty())
    {
        return;
    }
    else if(value.size() > 1)
    {
        this->write_encapsulated_pixel_data(value);
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
                odil_write_binary(item, this->stream, this->byte_ordering, 16);
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
                odil_write_binary(item, this->stream, this->byte_ordering, 32);
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
Writer::Visitor
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

void
Writer::Visitor
::write_encapsulated_pixel_data(Value::Binary const & value) const
{
    // FIXME: handle fragments
    Writer writer(this->stream, this->byte_ordering, this->explicit_vr);
    uint32_t length;
    for(auto const & fragment: value)
    {
        writer.write_tag(registry::Item);
        length = fragment.size();
        odil_write_binary(
            length, this->stream, this->byte_ordering, 8*sizeof(length));
        if(length > 0)
        {
            this->stream.write(reinterpret_cast<char const*>(&fragment[0]), length);
            if(!this->stream)
            {
                throw Exception("Could not write to stream");
            }
        }
    }
    writer.write_tag(registry::SequenceDelimitationItem);
    length = 0;
    odil_write_binary(
        length, this->stream, this->byte_ordering, 8*sizeof(length));
    if(!this->stream)
    {
        throw Exception("Could not write to stream");
    }
}

}

#undef odil_write_binary
