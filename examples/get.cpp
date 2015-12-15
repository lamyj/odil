#include <iostream>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/GetSCU.h"
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
    network.initialize();
    
    dcmtkpp::DcmtkAssociation association;
    
    association.set_own_ae_title("myself");
    
    association.set_peer_host_name("pacs.example.com");
    association.set_peer_port(11112);
    association.set_peer_ae_title("pacs");
    
    association.add_presentation_context(
        dcmtkpp::registry::StudyRootQueryRetrieveInformationModelGET,
        { dcmtkpp::registry::ImplicitVRLittleEndian });
    
    association.add_presentation_context(
        dcmtkpp::registry::MRImageStorage,
        { dcmtkpp::registry::ImplicitVRLittleEndian },
        ASC_SC_ROLE_SCP);
    
    association.add_presentation_context(
        dcmtkpp::registry::VerificationSOPClass,
        { dcmtkpp::registry::ImplicitVRLittleEndian });
    
    association.associate(network);
    
    dcmtkpp::GetSCU scu;
    scu.set_network(&network);
    scu.set_association(&association);
    
    scu.echo();
    
    dcmtkpp::DataSet query;
    query.add("PatientID",{ "1234" });
    query.add("QueryRetrieveLevel", { "SERIES" });
    query.add("StudyInstanceUID", { "1.2.3.4.5" });
    query.add("SeriesInstanceUID", { "1.2.3.4.5.1" });
    
    scu.set_affected_sop_class(dcmtkpp::registry::StudyRootQueryRetrieveInformationModelGET);
    
    std::cout << "--------\n";
    std::cout << "Callback\n";
    std::cout << "--------\n\n";
    
    scu.get(query, print_informations);
    
    std::cout << "\n";
    
    std::cout << "------\n";
    std::cout << "vector\n";
    std::cout << "------\n\n";
    
    std::vector<dcmtkpp::DataSet> result = scu.get(query);
    for(auto dataset: result)
    {
        print_informations(dataset);
    }
    
    association.release();
    network.drop();
}
