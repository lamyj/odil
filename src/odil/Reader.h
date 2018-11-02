/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _aa2965aa_e891_4713_9c90_e8eacd2944ea
#define _aa2965aa_e891_4713_9c90_e8eacd2944ea

#include <functional>
#include <istream>
#include <string>
#include <utility>

#include "odil/DataSet.h"
#include "odil/Element.h"
#include "odil/endian.h"
#include "odil/odil.h"
#include "odil/Tag.h"
#include "odil/Value.h"
#include "odil/VR.h"

namespace odil
{

/// @brief Read DICOM objects from a stream.
class ODIL_API Reader
{
public:
    /// @brief Input stream.
    std::istream & stream;

    /// @brief Transfer syntax used to read the file.
    std::string transfer_syntax;

    /// @brief Endianness.
    ByteOrdering byte_ordering;

    /// @brief Explicit-ness of the Value Representations.
    bool explicit_vr;

    /// @brief Flag to keep or discard group length tags.
    bool keep_group_length;

    /**
     * @brief Read binary data from an stream encoded with the given endianness,
     * ensure stream is still good.
     */
    template<typename T>
    static T read_binary(std::istream & stream, ByteOrdering byte_ordering);

    /// @brief Read pixel data in encapsulated form.
    static Value::Binary read_encapsulated_pixel_data(
        std::istream & stream, ByteOrdering byte_ordering,
        std::string transfer_syntax, bool keep_group_length=false);

    /// @brief Ignore data from a stream, ensure stream is still good.
    static void ignore(std::istream & stream, std::streamsize size);

    /**
     * @brief Build a reader, derive byte ordering and explicit-ness of VR
     * from transfer syntax.
     */
    Reader(
        std::istream & stream, std::string const & transfer_syntax,
        bool keep_group_length=false);

    /// @brief Read a data set.
    std::shared_ptr<DataSet> read_data_set(
        std::function<bool(Tag const &)> halt_condition =
            [](Tag const &) { return false;}) const;

    /// @brief Read a tag.
    Tag read_tag() const;

    /// @brief Read the length of an element.
    uint32_t read_length(VR vr) const;

    /**
     * @brief Read an element (VR and value), try to guess the VR from the tag,
     * partially read data set, and transfer syntax for implicit VR transfer
     * syntaxes.
     */
    Element read_element(
        Tag const & tag=Tag(0xffff,0xffff),
        std::shared_ptr<DataSet const> data_set=std::make_shared<DataSet>()) const;

    /// @brief Return the meta-data header and data set stored in the stream.
    static std::pair<std::shared_ptr<DataSet>, std::shared_ptr<DataSet>>
    read_file(
        std::istream & stream,
        bool keep_group_length=false,
        std::function<bool(Tag const &)> halt_condition = [](Tag const &) { return false;});

private:
    struct Visitor
    {
        typedef void result_type;

        std::istream & stream;
        VR vr;
        uint32_t vl;

        std::string transfer_syntax;
        ByteOrdering byte_ordering;
        bool explicit_vr;
        bool keep_group_length;

        Visitor(
            std::istream & stream, VR vr, uint32_t vl,
            std::string const & transfer_syntax, ByteOrdering byte_ordering,
            bool explicit_vr, bool keep_group_length);

        result_type operator()(Value::Integers & value) const;
        result_type operator()(Value::Reals & value) const;
        result_type operator()(Value::Strings & value) const;
        result_type operator()(Value::DataSets & value) const;
        result_type operator()(Value::Binary & value) const;

        // uint32_t read_length() const;

        Value::Strings split_strings(std::string const & string) const;
        std::shared_ptr<DataSet>
        read_item(std::istream & specific_stream) const;
        Value::Binary read_encapsulated_pixel_data(
            std::istream & specific_stream) const;
    };
};

}

#include "odil/Reader.txx"

#endif // _aa2965aa_e891_4713_9c90_e8eacd2944ea
