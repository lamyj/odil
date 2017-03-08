/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _8836a563_24f6_4afb_89ba_377d49ce9f5d
#define _8836a563_24f6_4afb_89ba_377d49ce9f5d

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "odil/DataSet.h"
#include "odil/odil.h"
#include "odil/Tag.h"
#include "odil/Writer.h"

namespace odil
{

/// @brief Write a Basic Directory (i.e. DICOMDIR) object to the disk.
class ODIL_API BasicDirectoryCreator
{
public:
    /// @brief The tag and its associated type in the record.
    typedef std::pair<Tag, int> RecordKey;

    /// @brief Map from a record type to the extra keys.
    typedef std::map<std::string, std::vector<RecordKey>> RecordKeyMap;

    /// @brief Default record keys, classified by record type.
    static RecordKeyMap const default_record_keys;

    /**
     * @brief Root of the DICOM files and location of the output DICOMDIR file.
     *
     * The concatenation of root and each file, as well as of root and
     * "DICOMDIR" must be a valid path.
     */
    std::string root;

    /**
     * @brief Path to the DICOM files, relative to root.
     *
     * The concatenation of root and each file must be a valid path.
     */
    std::vector<std::string> files;

    /// @brief User-defined record keys, classified by record type.
    RecordKeyMap extra_record_keys;

    /// @brief Encoding of sequence items, defaults to Writer::ItemEncoding::ExplicitLength.
    Writer::ItemEncoding item_encoding;

    /// @brief Constructor.
    BasicDirectoryCreator(
        std::string const & root="",
        std::vector<std::string> const & files=std::vector<std::string>(),
        RecordKeyMap const & extra_record_keys=RecordKeyMap(),
        Writer::ItemEncoding item_encoding=Writer::ItemEncoding::ExplicitLength
        );

    /// @brief Create and write the Basic Directory.
    void operator()() const;

private:
    struct Record
    {
        typedef std::shared_ptr<Record> Pointer;
        DataSet data_set;
        std::map<std::string, Record::Pointer> children;
    };

    struct LinearizedTree
    {
        std::vector<Record::Pointer> records;
        std::vector<long> sibling;
        std::vector<long> child;
    };

    typedef std::map<std::string, Record::Pointer> RecordMap;

    /// @brief Create a hierarchy of records from the files.
    std::map<std::string, Record::Pointer> _create_records() const;

    /// @brief Find a given record or insert a new one and return it.
    Record & _find_record(RecordMap & records, std::string const & key) const;

    /// @brief Create a default record.
    void _fill_record(
        DataSet const & data_set, Record & record,
        std::string const & type) const;

    /// @brief Update the record content from a data set.
    void _update_record(
        DataSet const & data_set, Record & record,
        std::vector<RecordKey> const & keys) const;

    /// @brief Return a linearized version of the record hierarchy.
    LinearizedTree _linearize_records(RecordMap const & record_tree) const;

    /// @brief Compute the offsets of the records relative to the first record.
    std::vector<std::streampos> _get_relative_offsets(
        std::vector<Record::Pointer> const & records) const;

    /// @brief Write the DICOMDIR.
    void _write(
        LinearizedTree const & linearized_tree,
        std::vector<std::streampos> const & relative_offsets) const;
};

}

#endif // _8836a563_24f6_4afb_89ba_377d49ce9f5d
