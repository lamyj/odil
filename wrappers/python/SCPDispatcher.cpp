/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/EchoSCP.h"
#include "odil/NCreateSCP.h" 
#include "odil/NSetSCP.h"
#include "odil/SCP.h"
#include "odil/SCPDispatcher.h"
#include "odil/StoreSCP.h"

namespace
{

template<typename TSCP, odil::message::Message::Command Command>
void set_scp(odil::SCPDispatcher & dispatcher, TSCP scp)
{
    dispatcher.set_scp(Command, std::make_shared<TSCP>(scp));
}

}

void wrap_SCPDispatcher(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    class_<SCPDispatcher >(m, "SCPDispatcher")
        .def(init<Association&>())
        .def("set_scp", &SCPDispatcher::set_scp)
        .def("dispatch", &SCPDispatcher::dispatch)
        .def(
            "set_echo_scp",
            &set_scp<EchoSCP, message::Message::Command::C_ECHO_RQ>)
        .def(
            "set_store_scp",
            &set_scp<StoreSCP, message::Message::Command::C_STORE_RQ>)
        .def(
            "set_nset_scp",
            &set_scp<NSetSCP, message::Message::Command::N_SET_RQ>)
        .def(
            "set_ncreate_scp",
            &set_scp<NCreateSCP, message::Message::Command::N_CREATE_RQ>)
        .def("has_scp", &SCPDispatcher::has_scp)
    ;
}


