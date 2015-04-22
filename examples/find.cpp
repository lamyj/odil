#include <iostream>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "dcmtkpp/FindSCU.h"

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

    std::string const patient_name =
        dcmtkpp::ElementAccessor<std::string>::get(*response, DCM_PatientName);

    std::string const study_description =
        dcmtkpp::ElementAccessor<std::string>::get(*response, DCM_StudyDescription);

    std::string const study_date =
        dcmtkpp::ElementAccessor<std::string>::get(*response, DCM_StudyDate);

    Sint32 const number_of_study_related_series =
        dcmtkpp::ElementAccessor<Sint32>::get(*response, DCM_NumberOfStudyRelatedSeries);
    
    std::cout << patient_name << ": " << study_description
              << " on " << study_date << ", " 
              << number_of_study_related_series << " series\n";
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
    
    DcmDataset query;
    dcmtkpp::ElementAccessor<std::string>::set(query, DCM_PatientName, "DOE^John");
    dcmtkpp::ElementAccessor<std::string>::set(query, DCM_QueryRetrieveLevel, "STUDY");
    query.insertEmptyElement(DCM_StudyDescription);
    query.insertEmptyElement(DCM_NumberOfStudyRelatedSeries);
    query.insertEmptyElement(DCM_StudyDate);
    
    scu.set_affected_sop_class(UID_FINDStudyRootQueryRetrieveInformationModel);
    
    std::cout << "--------\n";
    std::cout << "Callback\n";
    std::cout << "--------\n\n";
    
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
