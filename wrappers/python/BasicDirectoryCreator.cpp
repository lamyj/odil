/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <string>
#include <vector>

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "odil/BasicDirectoryCreator.h"

namespace
{

boost::python::list get_files(odil::BasicDirectoryCreator const & creator)
{
    boost::python::list result;
    for(auto const & file: creator.files)
    {
        result.append(file);
    }

    return result;
}

void set_files(
    odil::BasicDirectoryCreator & creator, 
    boost::python::list const & files_python)
{
    std::vector<std::string> files_cpp(boost::python::len(files_python));
    for(int i = 0; i<boost::python::len(files_python); ++i)
    {
        files_cpp[i] = boost::python::extract<std::string>(files_python[i]);
    }
    creator.files = files_cpp;
}

boost::python::dict 
get_extra_record_keys(odil::BasicDirectoryCreator const & creator)
{
    boost::python::dict result;
    for(auto const & item: creator.extra_record_keys)
    {
        boost::python::list values;
        for(auto const & value_cpp: item.second)
        {
            boost::python::list value_python;
            value_python.append(value_cpp.first);
            value_python.append(value_cpp.second);
            values.append(value_python);
        }
        result[item.first] = values;
    }
    return result;
}

void 
set_extra_record_keys(
    odil::BasicDirectoryCreator & creator, 
    boost::python::dict const & extra_record_keys_python)
{
    odil::BasicDirectoryCreator::RecordKeyMap extra_record_keys_cpp;
    
    auto items = extra_record_keys_python.items();
    for(int item_index=0; item_index<boost::python::len(items); ++item_index)
    {
        auto item = items[item_index];
        
        auto key_python = item[0];
        std::string const key_cpp = boost::python::extract<std::string>(key_python);
        
        auto value_python = item[1];
        std::vector<odil::BasicDirectoryCreator::RecordKey> value_cpp;
        for(int value_index=0; value_index<boost::python::len(value_python); ++value_index)
        {
            auto record_key_python = value_python[value_index];
            
            auto tag_python = record_key_python[0];
            odil::Tag const tag_cpp = boost::python::extract<odil::Tag>(tag_python);
            
            auto type_python = record_key_python[1];
            int const type_cpp = boost::python::extract<int>(type_python);
            
            value_cpp.push_back(
                odil::BasicDirectoryCreator::RecordKey(tag_cpp, type_cpp));
        }
        
        extra_record_keys_cpp[key_cpp] = value_cpp;
    }
    
    creator.extra_record_keys = extra_record_keys_cpp;
}
    
boost::shared_ptr<odil::BasicDirectoryCreator>
constructor(
    std::string const & root, boost::python::list const & files, 
    boost::python::dict const & extra_record_keys=boost::python::dict())
{
    // Old versions of Boost.Python (Debian 7, Ubuntu 12.04) do not like 
    // std::shared_ptr
    auto creator = new odil::BasicDirectoryCreator(root);
    set_files(*creator, files);
    set_extra_record_keys(*creator, extra_record_keys);
    return boost::shared_ptr<odil::BasicDirectoryCreator>(creator);    
}

}

void wrap_BasicDirectoryCreator()
{
    using namespace boost::python;
    using namespace odil;

    class_<BasicDirectoryCreator>("BasicDirectoryCreator", no_init)
        .def(
            "__init__", 
            make_constructor(constructor, default_call_policies(), 
            (arg("root"), arg("files"), arg("extra_record_keys")=dict())))
        .def_readwrite("root", &BasicDirectoryCreator::root)
        .add_property("files", &get_files, &set_files)
        .add_property(
            "extra_record_keys", &get_extra_record_keys, &set_extra_record_keys)
        .def("__call__", &BasicDirectoryCreator::operator())
    ;
}
