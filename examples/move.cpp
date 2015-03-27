#include <iostream>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "dcmtkpp/MoveSCU.h"

void print_informations(DcmDataset const * response)
{
    std::cout
        << dcmtkpp::ElementAccessor<EVR_PN>::get(*response, DCM_PatientName)
        << ": "
        << dcmtkpp::ElementAccessor<EVR_LO>::get(*response, DCM_StudyDescription)
        << " / "
        << dcmtkpp::ElementAccessor<EVR_LO>::get(*response, DCM_SeriesDescription)
        << ": "
        << dcmtkpp::ElementAccessor<EVR_IS>::get(*response, DCM_InstanceNumber)
        << "\n";
}

int main()
{
    dcmtkpp::Network network;
    network.set_role(NET_ACCEPTORREQUESTOR);
    network.set_port(11112);
    network.initialize();
    
    dcmtkpp::Association association;
    association.set_own_ae_title("myself");
    
    association.set_peer_host_name("pacs.example.com");
    association.set_peer_port(11112);
    association.set_peer_ae_title("pacs");
    
    association.add_presentation_context(
        UID_MOVEStudyRootQueryRetrieveInformationModel,
        { UID_LittleEndianImplicitTransferSyntax });
    
    association.add_presentation_context(
        UID_MRImageStorage,
        { UID_LittleEndianImplicitTransferSyntax });
    
    association.add_presentation_context(
        UID_VerificationSOPClass,
        { UID_LittleEndianImplicitTransferSyntax });
    
    association.associate(network);
    
    dcmtkpp::MoveSCU scu;
    scu.set_network(&network);
    scu.set_association(&association);
    scu.set_move_destination(association.get_own_ae_title());
    
    scu.echo();
    
    DcmDataset * query = new DcmDataset();
    query->putAndInsertOFStringArray(DCM_PatientID, "1234");
    query->putAndInsertOFStringArray(DCM_QueryRetrieveLevel, "SERIES");
    query->putAndInsertOFStringArray(DCM_StudyInstanceUID, "1.2.3.4.5");
    query->putAndInsertOFStringArray(DCM_SeriesInstanceUID, "1.2.3.4.5.1");
    
    scu.set_affected_sop_class(UID_MOVEStudyRootQueryRetrieveInformationModel);
    
    std::cout << "--------\n";
    std::cout << "Callback\n";
    std::cout << "--------\n\n";
    
    scu.move(query, print_informations);
    
    std::cout << "\n";
    
    std::cout << "------\n";
    std::cout << "vector\n";
    std::cout << "------\n\n";
    
    std::vector<DcmDataset*> result = scu.move(query);
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
