#include <iostream>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/MoveSCU.h"
#include "dcmtkpp/registry.h"

void print_informations(dcmtkpp::DataSet const & response)
{
    std::cout
        << response.as_string("PatientName", 0)
        << ": "
        << response.as_string("StudyDescription", 0)
        << " / "
        << response.as_string("SeriesDescription", 0)
        << ": "
        << response.as_string("InstanceNumber", 0)
        << "\n";
}

int main()
{
    dcmtkpp::Network network;
    network.set_role(NET_ACCEPTORREQUESTOR);
    network.set_port(11112);
    network.initialize();
    
    dcmtkpp::DcmtkAssociation association;
    association.set_own_ae_title("myself");
    
    association.set_peer_host_name("pacs.example.com");
    association.set_peer_port(11112);
    association.set_peer_ae_title("pacs");

    std::vector<dcmtkpp::DcmtkAssociation::PresentationContext>
            presentation_contexts;

    presentation_contexts.push_back(
                dcmtkpp::DcmtkAssociation::PresentationContext(
                    dcmtkpp::registry::StudyRootQueryRetrieveInformationModelMOVE,
                    { dcmtkpp::registry::ImplicitVRLittleEndian }));

    presentation_contexts.push_back(
                dcmtkpp::DcmtkAssociation::PresentationContext(
                    dcmtkpp::registry::MRImageStorage,
                    { dcmtkpp::registry::ImplicitVRLittleEndian },
                    ASC_SC_ROLE_SCP));

    presentation_contexts.push_back(
                dcmtkpp::DcmtkAssociation::PresentationContext(
                    dcmtkpp::registry::VerificationSOPClass,
                    { dcmtkpp::registry::ImplicitVRLittleEndian }));

    association.set_presentation_contexts(presentation_contexts);
    
    association.associate(network);
    
    dcmtkpp::MoveSCU scu;
    scu.set_network(&network);
    scu.set_association(&association);
    scu.set_move_destination(association.get_own_ae_title());
    
    scu.echo();
    
    dcmtkpp::DataSet query;
    query.add("PatientID",{ "1234" });
    query.add("QueryRetrieveLevel", { "SERIES" });
    query.add("StudyInstanceUID", { "1.2.3.4.5" });
    query.add("SeriesInstanceUID", { "1.2.3.4.5.1" });
    
    scu.set_affected_sop_class(dcmtkpp::registry::StudyRootQueryRetrieveInformationModelMOVE);
    
    std::cout << "--------\n";
    std::cout << "Callback\n";
    std::cout << "--------\n\n";
    
    scu.move(query, print_informations);
    
    std::cout << "\n";
    
    std::cout << "------\n";
    std::cout << "vector\n";
    std::cout << "------\n\n";
    
    std::vector<dcmtkpp::DataSet> result = scu.move(query);
    for(auto dataset: result)
    {
        print_informations(dataset);
    }
    
    association.release();
    network.drop();
}
