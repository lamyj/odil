#include "odil/Association.h"
#include "odil/DataSet.h"
#include "odil/EchoSCU.h"
#include "odil/Reader.h"
#include "odil/StoreSCU.h"

int main(int argc, char** argv)
{
    odil::Association association;
    association.set_peer_host("184.73.255.26");
    association.set_peer_port(11112);
    association.update_parameters()
        .set_calling_ae_title("myself")
        .set_called_ae_title("AWSPIXELMEDPUB")
        .set_presentation_contexts({
            {
                odil::registry::MRImageStorage,
                { odil::registry::ImplicitVRLittleEndian }, 
                odil::AssociationParameters::PresentationContext::Role::SCP
            },
            {
                odil::registry::VerificationSOPClass,
                { odil::registry::ImplicitVRLittleEndian }, 
                odil::AssociationParameters::PresentationContext::Role::SCU
            }
        });
    
    association.associate();

    odil::EchoSCU echo_scu(association);
    echo_scu.echo();
    
    odil::StoreSCU scu(association);
    
    for(int i=1; i<argc; ++i)
    {
        std::ifstream stream(argv[i], std::ios::binary);
        auto const header_and_data_set = odil::Reader::read_file(stream);
        
        scu.set_affected_sop_class(header_and_data_set.first);
        scu.store(header_and_data_set.first);
    }
    
    association.release();
}
