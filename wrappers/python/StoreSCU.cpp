/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/StoreSCU.h"

#include "opaque_types.h"
#include "type_casters.h"

void wrap_StoreSCU(pybind11::module & m)
{
    using namespace pybind11;
    using namespace pybind11::literals;
    using namespace odil;

    typedef
        void (StoreSCU::*StoreFunction)(
            std::shared_ptr<DataSet>, Value::String const &, Value::Integer) const;

    class_<StoreSCU>(m, "StoreSCU")
        .def(init<Association &>())
        .def(
            "get_affected_sop_class", &StoreSCU::get_affected_sop_class,
            return_value_policy::copy)
        .def(
            "set_affected_sop_class",
            static_cast<void(StoreSCU::*)(std::shared_ptr<DataSet const>)>(
                &StoreSCU::set_affected_sop_class)
        )
        .def(
            "store", &odil::StoreSCU::store,
            "dataset"_a, "move_originator_ae_title"_a="",
            "move_originator_message_id"_a=-1)
    ;
}
