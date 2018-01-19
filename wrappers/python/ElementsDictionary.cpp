/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include <odil/ElementsDictionary.h>

namespace
{

bool contains(odil::ElementsDictionary const & container, odil::Tag const & key)
{
    return container.find(key) != container.end();
}

bool contains(odil::ElementsDictionary const & container, std::string const & key)
{
    return container.find(key) != container.end();
}

odil::ElementsDictionaryEntry &
get_item(odil::ElementsDictionary & container, odil::Tag const & key)
{
    odil::ElementsDictionary::iterator iterator = container.find(key);
    if(iterator == container.end())
    {
        PyErr_SetString(PyExc_KeyError, "Invalid key");
        boost::python::throw_error_already_set();
    }
    return iterator->second;
}

odil::ElementsDictionaryEntry &
get_item(odil::ElementsDictionary & container, std::string const & key)
{
    odil::ElementsDictionary::iterator iterator = container.find(key);
    if(iterator == container.end())
    {
        PyErr_SetString(PyExc_KeyError, "Invalid key");
        boost::python::throw_error_already_set();
    }
    return iterator->second;
}


}

void wrap_ElementsDictionary()
{
    using namespace boost::python;
    using namespace odil;

    class_<ElementsDictionaryKey>("ElementsDictionaryKey", init<>())
        .def(init<Tag>())
        .def(init<std::string>())
    ;

    class_<ElementsDictionaryEntry>(
        "ElementsDictionaryEntry",
        init<std::string, std::string, std::string, std::string>()
    )
        .def_readwrite("name", &ElementsDictionaryEntry::name)
        .def_readwrite("keyword", &ElementsDictionaryEntry::keyword)
        .def_readwrite("vr", &ElementsDictionaryEntry::vr)
        .def_readwrite("vm", &ElementsDictionaryEntry::vm)
    ;

    class_<ElementsDictionary>("ElementsDictionary")
        .def(map_indexing_suite<ElementsDictionary>())
        .def(
            "__contains__",
            static_cast<bool(*)(ElementsDictionary const &, Tag const &)>(contains)
        )
        .def(
            "__contains__",
            static_cast<bool(*)(ElementsDictionary const &, std::string const &)>(contains)
        )
        .def(
            "__getitem__",
            static_cast<ElementsDictionaryEntry & (*)(ElementsDictionary &, Tag const &)>(get_item),
            return_value_policy<reference_existing_object>()
        )
        .def(
            "__getitem__",
            static_cast<ElementsDictionaryEntry & (*)(ElementsDictionary &, std::string const &)>(get_item),
            return_value_policy<reference_existing_object>()
        )
        ;
    ;
}
