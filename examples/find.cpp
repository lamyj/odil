#include <iostream>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "dcmtkpp/FindSCU.h"

void print_informations(DcmDataset * response)
{
    OFString patient_name;
    response->findAndGetOFString(DCM_PatientName, patient_name);
    
    OFString study_description;
    response->findAndGetOFString(DCM_StudyDescription, study_description);
    
    OFString study_date;
    response->findAndGetOFString(DCM_StudyDate, study_date);
    
    Sint32 number_of_study_related_series;
    response->findAndGetSint32(DCM_NumberOfStudyRelatedSeries, number_of_study_related_series);
    
    std::cout << patient_name << ": " << study_description
              << " on " << study_date << ", " 
              << number_of_study_related_series << " series\n";
}

void callback_full(void * callback_data, T_DIMSE_C_FindRQ * request,
    int response_index, T_DIMSE_C_FindRSP * response,
    DcmDataset * response_identifiers)
{
    std::cout << "Callback data: " << callback_data << ", " 
              << "Response index: " << response_index << std::endl;
    print_informations(response_identifiers);
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
        UID_FINDStudyRootQueryRetrieveInformationModel,
        { UID_LittleEndianImplicitTransferSyntax });
    
    association.add_presentation_context(
        UID_VerificationSOPClass,
        { UID_LittleEndianImplicitTransferSyntax });
    
    association.associate(network);
    
    dcmtkpp::FindSCU scu;
    scu.set_network(&network);
    scu.set_association(&association);
    
    scu.echo();
    
    DcmDataset * query = new DcmDataset();
    query->putAndInsertOFStringArray(DCM_PatientName, "DOE^John");
    query->putAndInsertOFStringArray(DCM_QueryRetrieveLevel, "STUDY");
    query->putAndInsertOFStringArray(DCM_StudyDescription, "Brain");
    query->insertEmptyElement(DCM_NumberOfStudyRelatedSeries);
    query->insertEmptyElement(DCM_StudyDate);
    
    scu.set_affected_sop_class(UID_FINDStudyRootQueryRetrieveInformationModel);
    
    std::cout << "-------------\n";
    std::cout << "Full callback\n";
    std::cout << "-------------\n\n";
    
    scu.find(query, callback_full, (void*)0xdeadbeef);
    
    std::cout << "\n";
    
    std::cout << "---------------\n";
    std::cout << "Simple callback\n";
    std::cout << "---------------\n\n";
    
    scu.find(query, print_informations);
    
    std::cout << "\n";
        
    std::cout << "------\n";
    std::cout << "vector\n";
    std::cout << "------\n\n";
    
    std::vector<DcmDataset*> result = scu.find(query);
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
