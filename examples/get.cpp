#include <iostream>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/FindSCU.h"
#include "dcmtkpp/GetSCU.h"
#include "dcmtkpp/registry.h"

void print_informations(dcmtkpp::DataSet const & response)
{
    auto const name = response.has("PatientName")?
        response.as_string("PatientName", 0):"(no name)";
    auto const study = response.has("StudyDescription")?
        response.as_string("StudyDescription", 0):"(no study description)";
    auto const series = response.has("SeriesDescription")?
        response.as_string("SeriesDescription", 0):"(no series description)";
    auto const instance = response.has("InstanceNumber")?
        response.as_int("InstanceNumber", 0):(-1);
    std::cout
        << name << ": " << study << " / " << series << ": " << instance << "\n";
}

int main()
{
    dcmtkpp::Association association;
    association.set_peer_host("184.73.255.26");
    association.set_peer_port(11112);
    association.update_parameters()
        .set_calling_ae_title("myself")
        .set_called_ae_title("AWSPIXELMEDPUB")
        .set_presentation_contexts({
            {
                1, dcmtkpp::registry::StudyRootQueryRetrieveInformationModelFIND,
                { dcmtkpp::registry::ImplicitVRLittleEndian }, true, false
            },
            {
                3, dcmtkpp::registry::StudyRootQueryRetrieveInformationModelGET,
                { dcmtkpp::registry::ImplicitVRLittleEndian }, true, false
            },
            {
                5, dcmtkpp::registry::MRImageStorage,
                { dcmtkpp::registry::ImplicitVRLittleEndian }, false, true
            },
            {
                7, dcmtkpp::registry::VerificationSOPClass,
                { dcmtkpp::registry::ImplicitVRLittleEndian }, true, false
            }
        });
    
    association.associate();

    dcmtkpp::FindSCU find_scu(association);
    find_scu.set_affected_sop_class(
        dcmtkpp::registry::StudyRootQueryRetrieveInformationModelFIND);

    dcmtkpp::DataSet query;
    query.add("QueryRetrieveLevel", { "STUDY" });
    query.add("StudyInstanceUID");

    auto const studies = find_scu.find(query);
    dcmtkpp::DataSet series;
    for(auto const & study: studies)
    {
        if(!study.has("StudyInstanceUID"))
        {
            continue;
        }

        query = dcmtkpp::DataSet();
        query.add("QueryRetrieveLevel", {"SERIES"});
        query.add("Modality", {"MR"});
        query.add("StudyInstanceUID", study.as_string("StudyInstanceUID"));
        query.add("SeriesInstanceUID");

        auto const study_series = find_scu.find(query);

        if(!study_series.empty())
        {
            series = study_series[0];
            break;
        }
    }

    dcmtkpp::GetSCU get_scu(association);
    get_scu.set_affected_sop_class(
        dcmtkpp::registry::StudyRootQueryRetrieveInformationModelGET);
    
    query = dcmtkpp::DataSet();
    query.add("QueryRetrieveLevel", { "SERIES" });
    query.add("StudyInstanceUID", series["StudyInstanceUID"]);
    query.add("SeriesInstanceUID", series["SeriesInstanceUID"]);

    std::cout << "--------\n";
    std::cout << "Callback\n";
    std::cout << "--------\n\n";
    
    get_scu.get(query, print_informations);
    
    std::cout << "\n";
    
    std::cout << "------\n";
    std::cout << "vector\n";
    std::cout << "------\n\n";
    
    auto const result = get_scu.get(query);
    for(auto const & dataset: result)
    {
        print_informations(dataset);
    }
    
    association.release();
}
