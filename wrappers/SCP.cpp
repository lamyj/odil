/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/SCP.h"
/*
namespace
{

void 
set_callback(odil::SCP & scp, boost::python::object const & f)
{
    scp.set_callback(
        [f](odil::message::CEchoRequest const & message) 
        { 
            return boost::python::call<odil::Value::Integer>(f.ptr(), message);
        }
    );
}

}
*/

void wrap_SCP()
{
    using namespace boost::python;
    using namespace std;
    using namespace odil;

    class_<SCP, shared_ptr<SCP>, boost::noncopyable>("SCP", no_init )
            .def("receive_and_process", &SCP::receive_and_process )
            ;

}
