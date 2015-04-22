#include <iostream>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/GetSCU.h"

void print_informations(DcmDataset const * response)
{
    std::cout
        << dcmtkpp::ElementAccessor<std::string>::get(*response, DCM_PatientName)
        << ": "
        << dcmtkpp::ElementAccessor<std::string>::get(*response, DCM_StudyDescription)
        << " / "
        << dcmtkpp::ElementAccessor<std::string>::get(*response, DCM_SeriesDescription)
        << ": "
        << dcmtkpp::ElementAccessor<std::string>::get(*response, DCM_InstanceNumber)
        << "\n";
}

int main()
{
    dcmtkpp::Network network;
    network.initialize();
    
    dcmtkpp::Association association;
    
    association.set_own_ae_title("myself");
    
    association.set_peer_host_name("pacs.example.com");
    association.set_peer_port(11112);
    association.set_peer_ae_title("pacs");
    
    association.add_presentation_context(
        UID_GETStudyRootQueryRetrieveInformationModel,
        { UID_LittleEndianImplicitTransferSyntax });
    
    association.add_presentation_context(
        UID_MRImageStorage,
        { UID_LittleEndianImplicitTransferSyntax },
        ASC_SC_ROLE_SCP);
    
    association.add_presentation_context(
        UID_VerificationSOPClass,
        { UID_LittleEndianImplicitTransferSyntax });
    
    association.associate(network);
    
    dcmtkpp::GetSCU scu;
    scu.set_network(&network);
    scu.set_association(&association);
    
    scu.echo();
    
    DcmDataset * query = new DcmDataset();
    query->putAndInsertOFStringArray(DCM_PatientID, "1234");
    query->putAndInsertOFStringArray(DCM_QueryRetrieveLevel, "SERIES");
    query->putAndInsertOFStringArray(DCM_StudyInstanceUID, "1.2.3.4.5");
    query->putAndInsertOFStringArray(DCM_SeriesInstanceUID, "1.2.3.4.5.1");
    
    scu.set_affected_sop_class(UID_GETStudyRootQueryRetrieveInformationModel);
    
    std::cout << "--------\n";
    std::cout << "Callback\n";
    std::cout << "--------\n\n";
    
    scu.get(query, print_informations);
    
    std::cout << "\n";
    
    std::cout << "------\n";
    std::cout << "vector\n";
    std::cout << "------\n\n";
    
    std::vector<DcmDataset*> result = scu.get(query);
    for(auto dataset: result)
    {
        print_informations(dataset);
    }
    for(auto & dataset: result)
    {
        delete dataset;
        dataset = 0;
    }
    
    association.release();
    network.drop();
}
