#include <iostream>

#include "odil/Association.h"
#include "odil/DataSet.h"
#include "odil/FindSCU.h"
#include "odil/registry.h"

void print_informations(odil::DataSet const & response)
{
    auto const name = response.has("PatientName")?
        response.as_string("PatientName", 0):"(no name)";
    auto const study = response.has("StudyDescription")?
        response.as_string("StudyDescription", 0):"(no description)";
    auto const date = response.has("StudyDate")?
        response.as_string("StudyDate", 0):"(no date)";
    std::cout
        << "\"" << name << "\": \"" << study << "\" on " << date << "\n";
}

int main()
{
    odil::Association association;
    association.set_peer_host("184.73.255.26");
    association.set_peer_port(11112);
    association.update_parameters()
        .set_calling_ae_title("myself")
        .set_called_ae_title("AWSPIXELMEDPUB")
        .set_presentation_contexts({
            {
                1, odil::registry::StudyRootQueryRetrieveInformationModelFIND,
                { odil::registry::ExplicitVRLittleEndian }, true, false
            },
            {
                3, odil::registry::VerificationSOPClass,
                { odil::registry::ExplicitVRLittleEndian }, true, false
            }
        });
    
    association.associate();
    
    odil::FindSCU scu(association);

    scu.echo();

    odil::DataSet query;
    query.add("PatientName", { "*" });
    query.add("QueryRetrieveLevel", { "STUDY" });
    query.add("StudyDescription");
    query.add("StudyDate");
    
    scu.set_affected_sop_class(odil::registry::StudyRootQueryRetrieveInformationModelFIND);
    
    std::cout << "--------\n";
    std::cout << "Callback\n";
    std::cout << "--------\n\n";
    
    scu.find(query, print_informations);

    std::cout << "\n";
        
    std::cout << "------\n";
    std::cout << "vector\n";
    std::cout << "------\n\n";
    
    auto const result = scu.find(query);
    for(auto const & dataset: result)
    {
        print_informations(dataset);
    }
    
    association.release();
}
