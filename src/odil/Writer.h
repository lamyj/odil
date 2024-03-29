/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _ca5c06d2_04f9_4009_9e98_5607e1060379
#define _ca5c06d2_04f9_4009_9e98_5607e1060379

#include <ostream>
#include <string>

#include "odil/DataSet.h"
#include "odil/Element.h"
#include "odil/endian.h"
#include "odil/odil.h"
#include "odil/registry.h"
#include "odil/Tag.h"
#include "odil/Value.h"
#include "odil/VR.h"

namespace odil
{

/// @brief Write DICOM objects to a stream.
class ODIL_API Writer
{
public:
    /// @brief Encodings of sequence items.
    enum class ItemEncoding
    {
        ExplicitLength,
        UndefinedLength
    };

    /// @brief Output stream.
    std::ostream & stream;

    /// @brief Endianness.
    ByteOrdering byte_ordering;
    /// @brief Explicit-ness of the Value Representations.
    bool explicit_vr;
    /// @brief Encoding of sequence items.
    ItemEncoding item_encoding;
    /// @brief Presence of group length elements.
    bool use_group_length;

    /**
     * @brief Write binary data to an stream encoded with the given endianness,
     * ensure stream is still good.
     */
    template<typename T>
    static void write_binary(
        T const & value, std::ostream & stream, ByteOrdering byte_ordering);

    /// @brief Write pixel data in encapsulated form.
    static void write_encapsulated_pixel_data(
        Value::Binary const & value, std::ostream & stream,
        ByteOrdering byte_ordering, bool explicit_vr);

    static std::size_t size(
        odil::Tag const &, bool explicit_vr, ItemEncoding item_encoding,
        bool use_group_length);
    static std::size_t size(
        odil::VR vr, odil::Value const &, bool explicit_vr,
        ItemEncoding item_encoding, bool use_group_length);
    static std::size_t size(
        odil::Element const &, bool explicit_vr, ItemEncoding item_encoding,
        bool use_group_length);
    static std::size_t size(
        odil::DataSet const &, bool explicit_vr, ItemEncoding item_encoding,
        bool use_group_length);
    
    /// @brief Build a writer.
    Writer(
        std::ostream & stream,
        ByteOrdering byte_ordering, bool explicit_vr,
        ItemEncoding item_encoding=ItemEncoding::ExplicitLength,
        bool use_group_length=false);

    /**
     * @brief Build a writer, derive byte ordering and explicit-ness of VR
     * from transfer syntax.
     */
    Writer(
        std::ostream & stream,
        std::string const & transfer_syntax,
        ItemEncoding item_encoding=ItemEncoding::ExplicitLength,
        bool use_group_length=false);

    /// @brief Write a data set.
    void write_data_set(std::shared_ptr<DataSet const> data_set) const;

    /// @brief Write a tag.
    void write_tag(Tag const & tag) const;

    /// @brief Write an element (VR, VL and value).
    void write_element(Element const & element) const;

    /// @brief Write a file (meta-information and data set).
    static void write_file(
        std::shared_ptr<DataSet const> data_set, std::ostream & stream,
        std::shared_ptr<DataSet const> meta_information={},
        std::string const & transfer_syntax = registry::ExplicitVRLittleEndian,
        ItemEncoding item_encoding=ItemEncoding::ExplicitLength,
        bool use_group_length=false);

private:

    struct WriteVisitor
    {
        typedef void result_type;

        std::ostream & stream;
        VR vr;

        ByteOrdering byte_ordering;
        bool explicit_vr;
        ItemEncoding item_encoding;
        bool use_group_length;

        WriteVisitor(
            std::ostream & stream, VR vr,
            ByteOrdering byte_ordering, bool explicit_vr, ItemEncoding item_encoding,
            bool use_group_length);

        result_type operator()(Value::Integers const & value) const;
        result_type operator()(Value::Reals const & value) const;
        result_type operator()(Value::Strings const & value) const;
        result_type operator()(Value::DataSets const & value) const;
        result_type operator()(Value::Binary const & value) const;
        
        void write_strings(Value::Strings const & sequence, char padding) const;
        void write_strings(Value::Integers const & sequence, char padding) const;
    };
    
    class SizeVisitor
    {
    public:
        using result_type = std::size_t;
        
        VR vr;
        bool explicit_vr;
        ItemEncoding item_encoding;
        bool use_group_length;

        SizeVisitor(
            VR vr, bool explicit_vr, ItemEncoding item_encoding,
            bool use_group_length);
        
        result_type operator()(Value::Integers const & value) const;
        result_type operator()(Value::Reals const & value) const;
        result_type operator()(Value::Strings const & value) const;
        result_type operator()(Value::DataSets const & value) const;
        result_type operator()(Value::Binary const & value) const;
    };
};

}

#include "odil/Writer.txx"

#endif // _ca5c06d2_04f9_4009_9e98_5607e1060379
