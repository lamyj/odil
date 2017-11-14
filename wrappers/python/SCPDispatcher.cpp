/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/EchoSCP.h"
#include "odil/NCreateSCP.h" 
#include "odil/NSetSCP.h"
#include "odil/SCP.h"
#include "odil/SCPDispatcher.h"
#include "odil/StoreSCP.h"

#include <boost/python.hpp>

namespace
{

void dispatch_in_python( odil::SCPDispatcher& dispatcher)
{
    dispatcher.dispatch();
}

template<typename TSCP, odil::message::Message::Command::Type Command>
void set_scp(odil::SCPDispatcher & dispatcher, TSCP scp)
{
    dispatcher.set_scp(Command, std::make_shared<TSCP>( scp ));
}

}

void wrap_SCPDispatcher()
{
    using namespace boost::python;
    using namespace odil;

    class_<SCPDispatcher >("SCPDispatcher", init<Association&>())
    .def("set_scp", &SCPDispatcher::set_scp )
    .def("dispatch", &dispatch_in_python )
    .def("set_echo_scp", &set_scp<EchoSCP, message::Message::Command::Type::C_ECHO_RQ>)
    .def("set_store_scp", &set_scp<StoreSCP, message::Message::Command::Type::C_STORE_RQ>)
    .def("set_nset_scp", &set_scp<NSetSCP, message::Message::Command::Type::N_SET_RQ>)
    .def("set_ncreate_scp", &set_scp<NCreateSCP, message::Message::Command::Type::N_CREATE_RQ>)
    ;
}


