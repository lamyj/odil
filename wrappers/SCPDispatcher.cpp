/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/SCPDispatcher.h"
#include "odil/SCP.h"
#include "odil/StoreSCP.h"

namespace
{

    void set_scp_in_python( odil::SCPDispatcher & scpDispatcher,  odil::Value::Integer command
                            , ::boost::python::object & scp_to_add )
    {
        try{
            /*
            auto scp = dynamic_cast< odil::SCP& >(scp_to_add);
            auto shared_scp = std::make_shared<odil::SCP>(scp);
            scpDispatcher.set_scp(command, shared_scp);
            */
        }
        catch(...){
            //Fuck it
        }
    }

    void dispatch_in_python(odil::SCPDispatcher const & dispatcher, ::boost::python::object const & f)
    {
    //    dispatcher.dispatch(
    //                [f](void){
    //                    boost::python::call<void>(f.ptr() );
    //            }
    //            )
    }

    void functionTest(odil::SCPDispatcher scpd)
    {
       std::cout << "Hello" << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl ;
    }


    void set_scp(odil::SCPDispatcher scpd, odil::StoreSCP scp)
    {
        auto shared_scp = std::make_shared< odil::StoreSCP>( scp );
        odil::Value::Integer command = ::odil::message::Message::Command::Type::C_STORE_RQ ;

        scpd.set_scp(command, shared_scp );

        std::cout<< "Ta mere le wrapping!" << std::endl << std::endl << std::endl << std::endl ;
    }

    std::shared_ptr< odil::SCPDispatcher> New( odil::Association &  a )
    {
        return std::shared_ptr< odil::SCPDispatcher>( new odil::SCPDispatcher(a) ) ;
    }
}

void wrap_SCPDispatcher()
{
    using namespace boost::python;
    using namespace odil;

    class_<SCPDispatcher, std::shared_ptr<SCPDispatcher> >("SCPDispatcher", init<Association &>())
            .def("set_scp", &SCPDispatcher::set_scp )
            .def("add_scp", &set_scp_in_python )
            .def("dispatch", &dispatch_in_python )
            .def("set_storeSCP", &set_scp);
            ;

    def("New_SCPDispatcher" , &New ) ;

}


