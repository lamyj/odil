/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <string>
#include <vector>

#include <pybind11/pybind11.h>

#include "odil/BasicDirectoryCreator.h"

#include "opaque_types.h"
#include "type_casters.h"

namespace
{

pybind11::list get_files(odil::BasicDirectoryCreator const & creator)
{
    pybind11::list result;
    for(auto const & file: creator.files)
    {
        result.append(file);
    }

    return result;
}

void set_files(
    odil::BasicDirectoryCreator & creator,
    pybind11::sequence const & files_python)
{
    std::vector<std::string> files_cpp(pybind11::len(files_python));
    std::transform(
        files_python.begin(), files_python.end(), files_cpp.begin(),
        [](pybind11::handle const & h) { return pybind11::cast<std::string>(h); });
    creator.files = files_cpp;
}

pybind11::dict
get_extra_record_keys(odil::BasicDirectoryCreator const & creator)
{
    pybind11::dict result;
    for(auto const & item: creator.extra_record_keys)
    {
        pybind11::list values;
        for(auto const & value_cpp: item.second)
        {
            pybind11::list value_python;
            value_python.append(value_cpp.first);
            value_python.append(value_cpp.second);
            values.append(value_python);
        }
        result[pybind11::cast(item.first)] = values;
    }
    return result;
}

void 
set_extra_record_keys(
    odil::BasicDirectoryCreator & creator, 
    pybind11::dict const & extra_record_keys_python)
{
    for(auto const item: extra_record_keys_python)
    {
        auto const level = pybind11::cast<std::string>(item.first);
        auto const extra_record_keys = item.second;

        std::vector<odil::BasicDirectoryCreator::RecordKey> value(
            pybind11::len(extra_record_keys));
        std::transform(
            extra_record_keys.begin(), extra_record_keys.end(), value.begin(),
            [](pybind11::handle const & h)
            {
                auto const tag_and_type = h.cast<pybind11::sequence>();
                auto const tag = pybind11::cast<odil::Tag>(tag_and_type[0]);
                auto const type = pybind11::cast<int>(tag_and_type[1]);
                return odil::BasicDirectoryCreator::RecordKey(tag, type);
            });

        creator.extra_record_keys[level] = value;
    }
}

}

void wrap_BasicDirectoryCreator(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    class_<BasicDirectoryCreator>(m, "BasicDirectoryCreator")
        .def(
            init(
                [](
                    std::string const & root, sequence const & files,
                    dict const & extra_record_keys)
                {
                    BasicDirectoryCreator creator(root);
                    set_files(creator, files);
                    set_extra_record_keys(creator, extra_record_keys);
                    return creator;
                }),
            "root"_a, "files"_a, "extra_record_keys"_a=dict())
        .def_readwrite("root", &BasicDirectoryCreator::root)
        .def_property("files", &get_files, &set_files)
        .def_property(
            "extra_record_keys", &get_extra_record_keys, &set_extra_record_keys)
        .def("__call__", &BasicDirectoryCreator::operator())
    ;
}
