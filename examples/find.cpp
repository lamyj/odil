#include <iostream>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/FindSCU.h"
#include "dcmtkpp/registry.h"

void print_informations(dcmtkpp::DataSet const & response)
{
    std::cout << response.as_string("PatientName", 0) << ": "
              << response.as_string("StudyDescription", 0)
              << " on " << response.as_string("StudyDate", 0) << ", "
              << response.as_int(dcmtkpp::registry::NumberOfStudyRelatedSeries, 0) << " series\n";
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
        dcmtkpp::registry::StudyRootQueryRetrieveInformationModelFIND,
        { dcmtkpp::registry::ImplicitVRLittleEndian });
    
    association.add_presentation_context(
        dcmtkpp::registry::VerificationSOPClass,
        { dcmtkpp::registry::ImplicitVRLittleEndian });
    
    association.associate(network);
    
    dcmtkpp::FindSCU scu;
    scu.set_network(&network);
    scu.set_association(&association);
    
    scu.echo();
    
    dcmtkpp::DataSet query;
    query.add("PatientName", { "DOE^John" });
    query.add("QueryRetrieveLevel", { "STUDY" });
    query.add("StudyDescription");
    query.add(dcmtkpp::registry::NumberOfStudyRelatedSeries);
    query.add("StudyDate");
    
    scu.set_affected_sop_class(dcmtkpp::registry::StudyRootQueryRetrieveInformationModelFIND);
    
    std::cout << "--------\n";
    std::cout << "Callback\n";
    std::cout << "--------\n\n";
    
    scu.find(query, print_informations);
    
    std::cout << "\n";
        
    std::cout << "------\n";
    std::cout << "vector\n";
    std::cout << "------\n\n";
    
    std::vector<dcmtkpp::DataSet> result = scu.find(query);
    for(auto dataset: result)
    {
        print_informations(dataset);
    }
    
    association.release();
    network.drop();
}
