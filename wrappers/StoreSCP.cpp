/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/StoreSCP.h"

#include <boost/python.hpp>

#include <functional>

namespace
{
using namespace std;
void
set_callback(odil::StoreSCP& scp, boost::python::object const& f)
{
    scp.set_callback(
        [f](odil::message::CStoreRequest const& message)
        {
            return boost::python::call<odil::Value::Integer>(f.ptr(), message);
        }
        );
}

std::shared_ptr<odil::StoreSCP> New_StoreSCP2( odil::Association& a, ::boost::python::object const& f )
{
    odil::StoreSCP scp( a );
    set_callback( std::ref(scp), f );
    auto scp_sptr = std::make_shared<odil::StoreSCP>(scp);
    return scp_sptr;
}

std::shared_ptr<odil::StoreSCP> New_StoreSCP1( odil::Association& a )
{
    return std::shared_ptr<odil::StoreSCP>( new odil::StoreSCP(a) );
}

}

void wrap_StoreSCP()
{
    using namespace boost::python;
    using namespace std;
    using namespace odil;

//    class_<StoreSCP, bases<SCP>>("StoreSCP", init<Association &>())
    class_<StoreSCP>("StoreSCP", init<Association&>())
    .def(init<Association&, StoreSCP::Callback& >())
    .def("set_callback", &set_callback)
    .def("__call__", &StoreSCP::operator())
    ;

    def("New_StoreSCP1", &New_StoreSCP1);
    def("New_StoreSCP2", &New_StoreSCP2);

//    register_ptr_to_python< shared_ptr<StoreSCP> >();
}
