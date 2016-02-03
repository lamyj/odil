/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include "odil/DataSet.h"

void wrap_DataSet()
{
    using namespace boost::python;
    using namespace odil;

    //BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(DataSet_overloads, add, 2, 3)
    class_<DataSet>("DataSet", init<>())
        //.def("add", &DataSet::add, DataSet_overloads())
        .def("remove", &DataSet::remove)
        .def("has", &DataSet::has)
        .def("get_vr", &DataSet::get_vr)
        .def("empty", static_cast<bool (DataSet::*)() const>(&DataSet::empty))
        .def(
            "size", 
            static_cast<std::size_t (DataSet::*)() const>(&DataSet::size))
        // operator[], cf. map
        // is_XXX, as_XXX
        // iteration
        .def(self == self)
        .def(self != self)
        //.def(map_indexing_suite<DataSet>())
    ;
}
