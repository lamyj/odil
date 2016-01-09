/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/BasicDirectoryCreator.h"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Reader.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Tag.h"
#include "dcmtkpp/uid.h"

namespace dcmtkpp
{

std::map<std::string, std::vector<BasicDirectoryCreator::RecordKey>> const
BasicDirectoryCreator
::default_record_keys = {
    { "PATIENT", {
        { registry::PatientName, 2},
        { registry::PatientID, 1 } } },
    { "STUDY", {
        { registry::StudyDate, 1 },
        { registry::StudyTime, 1 },
        { registry::StudyDescription, 2 },
        { registry::StudyInstanceUID, 1 }, // only if (0004,1511) is absent (see Note)
        { registry::StudyID, 1 },
        { registry::AccessionNumber, 2 } } },
    { "SERIES", {
        { registry::Modality, 1 },
        { registry::SeriesInstanceUID, 1 },
        { registry::SeriesNumber, 1 },
        //registry::IconImageSequence
        } },
    { "IMAGE", {
        { registry::InstanceNumber, 1 },
        //registry::IconImageSequence
        } },
};

BasicDirectoryCreator
::BasicDirectoryCreator(
    std::string const & root, std::vector<std::string> const & files,
    RecordKeyMap const & extra_record_keys, Writer::ItemEncoding item_encoding)
: root(root), files(files), extra_record_keys(extra_record_keys),
    item_encoding(item_encoding)
{
    // Nothing else.
}

void
BasicDirectoryCreator
::operator()() const
{
    auto const record_tree = this->_create_records();
    auto linearized_tree = this->_linearize_records(record_tree);
    auto const relative_offsets = this->_get_relative_offsets(
        linearized_tree.records);
    this->_write(linearized_tree, relative_offsets);
}

BasicDirectoryCreator::RecordMap
BasicDirectoryCreator
::_create_records() const
{
    RecordMap patients;

    for(auto const & file: files)
    {
        auto const absolute_path = boost::filesystem::path(this->root)/file;
        if(!boost::filesystem::is_regular_file(absolute_path))
        {
            throw Exception("No such file: "+absolute_path.string());
        }

        boost::filesystem::ifstream stream(
            absolute_path, std::ifstream::in | std::ifstream::binary);
        auto const meta_info_and_data_set = Reader::read_file(stream);
        auto const & data_set = meta_info_and_data_set.second;

        auto const & patient_id = data_set.as_string(
            registry::PatientID)[0];
        auto & patient = this->_find_record(patients, patient_id);
        if(patient.data_set.empty())
        {
            this->_fill_record(data_set, patient, "PATIENT");
        }

        auto const & study_instance_uid = data_set.as_string(
            registry::StudyInstanceUID)[0];
        auto & study = this->_find_record(patient.children, study_instance_uid);
        if(study.data_set.empty())
        {
            this->_fill_record(data_set, study, "STUDY");
        }

        auto const & series_instance_uid = data_set.as_string(
            registry::SeriesInstanceUID)[0];
        auto & series = this->_find_record(study.children, series_instance_uid);
        if(series.data_set.empty())
        {
            this->_fill_record(data_set, series, "SERIES");
        }

        auto const & sop_instance_uid = data_set.as_string(
            registry::SOPInstanceUID)[0];
        auto & image = this->_find_record(series.children, sop_instance_uid);
        if(image.data_set.empty())
        {
            this->_fill_record(data_set, image, "IMAGE");

            Value::Strings file_id;
            int begin = 0;
            while(begin != std::string::npos)
            {
                auto const end = file.find('/', begin);
                auto const size =
                    (end==std::string::npos)?std::string::npos:(end-begin);
                std::string const item = file.substr(begin, size);
                file_id.push_back(item);
                if(end == std::string::npos)
                {
                    begin = end;
                }
                else
                {
                    begin = end+1;
                }
            }

            // Required if the Directory Record references a SOP Instance (PS3.3 F.3.2.2)
            image.data_set.add(registry::ReferencedFileID, file_id);
            image.data_set.add(
                registry::ReferencedSOPClassUIDInFile,
                data_set[registry::SOPClassUID]);
            image.data_set.add(
                registry::ReferencedSOPInstanceUIDInFile,
                data_set[registry::SOPInstanceUID]);

            auto const & meta_info = meta_info_and_data_set.first;
            image.data_set.add(
                registry::ReferencedTransferSyntaxUIDInFile,
                meta_info[registry::TransferSyntaxUID]);
        }
    }

    return patients;
}

BasicDirectoryCreator::Record &
BasicDirectoryCreator
::_find_record(RecordMap & records, std::string const & key) const
{
    auto iterator = records.find(key);
    if(iterator == records.end())
    {
        iterator = records.insert({key, Record::Pointer(new Record())}).first;
    }
    return *(iterator->second);
}

void
BasicDirectoryCreator
::_fill_record(
    DataSet const & data_set, Record & record, std::string const & type) const
{
    record.data_set.add(registry::DirectoryRecordType, {type});
    record.data_set.add(registry::OffsetOfTheNextDirectoryRecord, {0});
    record.data_set.add(registry::RecordInUseFlag, {0xffff});
    record.data_set.add(
        registry::OffsetOfReferencedLowerLevelDirectoryEntity, {0});

    this->_update_record(data_set, record, this->default_record_keys.at(type));

    auto const extra_record_keys_it = this->extra_record_keys.find(type);
    if(extra_record_keys_it != this->extra_record_keys.end())
    {
        this->_update_record(data_set, record, extra_record_keys_it->second);
    }
}

void
BasicDirectoryCreator
::_update_record(
    DataSet const & data_set, Record & record,
    std::vector<RecordKey> const & keys) const
{
    for(auto const & key: keys)
    {
        auto const & tag = key.first;
        auto const & type = key.second;

        if(data_set.has(tag))
        {
            record.data_set.add(tag, data_set[tag]);
        }
        else
        {
            if(type == 1)
            {
                throw Exception("Type 1 tag missing from data set: "+std::string(tag));
            }
            else if(type == 2)
            {
                record.data_set.add(tag);
            }
            // Otherwise do nothing.
        }
    }

    // TODO: registry::RecordInUseFlag;
}

BasicDirectoryCreator::LinearizedTree
BasicDirectoryCreator
::_linearize_records(RecordMap const & record_tree) const
{
    LinearizedTree linearized_tree;

    // Prime the stack with all top-level records.
    std::stack<Record::Pointer> stack;
    for(auto const & record: record_tree)
    {
        stack.push(record.second);
    }

    // Create a depth-first list of records and a sibling map.
    std::map<Record const *, long> location_map;
    std::map<Record const *, Record const *> sibling_map;
    while(!stack.empty())
    {
        auto const & record = stack.top();
        stack.pop();

        linearized_tree.records.push_back(record);
        location_map[record.get()] = linearized_tree.records.size()-1;

        auto const & children = record->children;

        for(auto child_it=children.begin(); child_it!=children.end(); ++child_it)
        {
            auto const & child_record = child_it->second;
            auto const sibling_it = std::next(child_it);
            if(sibling_it != children.end())
            {
                auto const & sibling = sibling_it->second;
                sibling_map[child_record.get()] = sibling.get();
            }
        }

        // Use reverse iterators to keep the relative order of children during
        // the depth-first search.
        std::for_each(
            children.rbegin(), children.rend(),
            [&] (RecordMap::value_type const & child) { stack.push(child.second); });
    }

    // Update the topological information.

    linearized_tree.child.resize(location_map.size());
    std::fill(linearized_tree.child.begin(), linearized_tree.child.end(), -1);

    linearized_tree.sibling.resize(location_map.size());
    std::fill(linearized_tree.sibling.begin(), linearized_tree.sibling.end(), -1);

    for(auto const & location_it: location_map)
    {
        auto const & record = location_it.first;
        auto const & location = location_it.second;
        if(!record->children.empty())
        {
            linearized_tree.child[location] =
                location_map.at(record->children.begin()->second.get());
        }
        else
        {
            linearized_tree.child[location] = -1;
        }

        auto const sibling_it = sibling_map.find(record);
        if(sibling_it != sibling_map.end())
        {
            linearized_tree.sibling[location] =
                location_map.at(sibling_it->second);
        }
        else
        {
            linearized_tree.sibling[location] = -1;
        }
    }

    return linearized_tree;
}

std::vector<std::streampos>
BasicDirectoryCreator
::_get_relative_offsets(std::vector<Record::Pointer> const & records) const
{
    // Create an in-memory stream to compute the position of the start of the
    // records
    std::ostringstream stream;

    // PS3.10, 8.6: The DICOMDIR File shall use the Explicit VR Little Endian
    // Transfer Syntax
    Writer const writer(
        stream, registry::ExplicitVRLittleEndian, this->item_encoding);

    std::vector<std::streampos> relative_offsets;

    std::streampos offset = 0;

    for(auto const & record: records)
    {
        relative_offsets.push_back(stream.tellp()+offset);

        // Item tag: 4 bytes
        // Item length: 4 bytes
        offset += 8;

        writer.write_data_set(record->data_set);

        if(this->item_encoding == Writer::ItemEncoding::UndefinedLength)
        {
            // Item Delimitation Item tag: 4 bytes
            // Item Delimitation Item length: 4 bytes
            offset += 8;
        }
    }

    return relative_offsets;
}

void
BasicDirectoryCreator
::_write(
    LinearizedTree const & linearized_tree,
    std::vector<std::streampos> const & relative_offsets) const
{
    DataSet meta_information;
    meta_information.add(
        registry::FileMetaInformationVersion, Value::Binary({0x00, 0x01}));
    meta_information.add(
        registry::MediaStorageSOPClassUID,
        { registry::MediaStorageDirectoryStorage });
    meta_information.add(
        registry::MediaStorageSOPInstanceUID, { generate_uid() });
    meta_information.add(
        registry::TransferSyntaxUID, { registry::ExplicitVRLittleEndian });
    meta_information.add(
        registry::ImplementationClassUID, { implementation_class_uid });
    meta_information.add(
        registry::ImplementationVersionName, { implementation_version_name });

    DataSet basic_directory;

    // File-Set Identification Module (PS3.3 F.3.2.1)
    basic_directory.add(registry::FileSetID, { "" });
    // Don't include user comments yet.
    // registry::FileSetDescriptorFileID;
    // registry::SpecificCharacterSetOfFileSetDescriptorFile;
    // Directory Information Module (PS3.3 F.3.2.2)
    basic_directory.add(
        registry::OffsetOfTheFirstDirectoryRecordOfTheRootDirectoryEntity,
        { 0 });
    basic_directory.add(
        registry::OffsetOfTheLastDirectoryRecordOfTheRootDirectoryEntity,
        { 0 });
    basic_directory.add(registry::FileSetConsistencyFlag, { 0 });

    std::ostringstream buffer;
    Writer buffer_writer(
        buffer, meta_information.as_string(registry::TransferSyntaxUID)[0],
        this->item_encoding);
    buffer_writer.write_data_set(meta_information);
    buffer_writer.write_data_set(basic_directory);

    // Preamble + prefix + data + Directory Record Sequence (tag + VR + reserved + VL)
    auto const start_of_directory_records = 128+4+buffer.tellp()+4+2+2+4;
    std::vector<std::streampos> absolute_offsets(relative_offsets.size());
    std::transform(
        relative_offsets.begin(), relative_offsets.end(), absolute_offsets.begin(),
        [&](std::streampos offset) { return offset+start_of_directory_records; });

    basic_directory.as_int(
        registry::OffsetOfTheFirstDirectoryRecordOfTheRootDirectoryEntity)[0] =
            *(absolute_offsets.begin());

    int last_top_level = 0;
    while(linearized_tree.sibling[last_top_level] != -1)
    {
        last_top_level = linearized_tree.sibling[last_top_level];
    }
    basic_directory.as_int(
        registry::OffsetOfTheLastDirectoryRecordOfTheRootDirectoryEntity)[0] =
            absolute_offsets[last_top_level];

    Value::DataSets record_sequence;
    for(int record_index=0; record_index<linearized_tree.records.size(); ++record_index)
    {
        auto & record = linearized_tree.records[record_index];
        auto & item = record->data_set;

        auto const sibling = linearized_tree.sibling[record_index];
        if(sibling != -1)
        {
            item.as_int(
                registry::OffsetOfTheNextDirectoryRecord)[0] =
                    absolute_offsets[sibling];
        }

        auto const child = linearized_tree.child[record_index];
        if(child != -1)
        {
            item.as_int(
                registry::OffsetOfReferencedLowerLevelDirectoryEntity)[0] =
                    absolute_offsets[child];
        }

        record_sequence.push_back(item);
    }
    basic_directory.add(registry::DirectoryRecordSequence, record_sequence);

    boost::filesystem::ofstream file(
        boost::filesystem::path(root)/"DICOMDIR",
        std::ofstream::out | std::ofstream::binary);
    Writer file_writer(
        file, buffer_writer.byte_ordering, buffer_writer.explicit_vr,
        buffer_writer.item_encoding, buffer_writer.use_group_length);

    // File preamble
    for(unsigned int i=0; i<128; ++i)
    {
        file.put(0);
        if(!file)
        {
            throw Exception("Could not write to stream");
        }
    }

    // DICOM prefix
    std::string const prefix("DICM");
    file.write(&prefix[0], prefix.size());
    if(!file)
    {
        throw Exception("Could not write to stream");
    }

    file_writer.write_data_set(meta_information);
    file_writer.write_data_set(basic_directory);
}

}
