#include <iostream>

#include "odil/Association.h"
#include "odil/DataSet.h"
#include "odil/FindSCU.h"
#include "odil/MoveSCU.h"
#include "odil/registry.h"

void print_informations(std::shared_ptr<odil::DataSet const> response)
{
    auto const name = response->has("PatientName")?
        response->as_string("PatientName", 0):"(no name)";
    auto const study = response->has("StudyDescription")?
        response->as_string("StudyDescription", 0):"(no study description)";
    auto const series = response->has("SeriesDescription")?
        response->as_string("SeriesDescription", 0):"(no series description)";
    auto const instance = response->has("InstanceNumber")?
        response->as_int("InstanceNumber", 0):(-1);
    std::cout
        << name << ": " << study << " / " << series << ": " << instance << "\n";
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
                odil::registry::StudyRootQueryRetrieveInformationModelFind,
                { odil::registry::ImplicitVRLittleEndian }, 
                odil::AssociationParameters::PresentationContext::Role::SCU
            },
            {
                odil::registry::StudyRootQueryRetrieveInformationModelMove,
                { odil::registry::ImplicitVRLittleEndian }, 
                odil::AssociationParameters::PresentationContext::Role::SCU
            },
            {
                odil::registry::MRImageStorage,
                { odil::registry::ImplicitVRLittleEndian }, 
                odil::AssociationParameters::PresentationContext::Role::SCP
            },
            {
                odil::registry::Verification,
                { odil::registry::ImplicitVRLittleEndian }, 
                odil::AssociationParameters::PresentationContext::Role::SCU
            }
        });

    association.associate();

    odil::FindSCU find_scu(association);
    find_scu.set_affected_sop_class(
        odil::registry::StudyRootQueryRetrieveInformationModelFind);

    auto query = std::make_shared<odil::DataSet>();
    query->add("QueryRetrieveLevel", { "STUDY" });
    query->add("StudyInstanceUID");
    query->add("NumberOfStudyRelatedSeries");

    auto const studies = find_scu.find(query);
    std::shared_ptr<odil::DataSet> series;
    for(auto const & study: studies)
    {
        if(!study->has("StudyInstanceUID"))
        {
            continue;
        }

        query->clear();
        query->add("QueryRetrieveLevel", {"SERIES"});
        query->add("Modality", {"MR"});
        query->add("StudyInstanceUID", study->as_string("StudyInstanceUID"));
        query->add("SeriesInstanceUID");

        auto const study_series = find_scu.find(query);

        if(!study_series.empty())
        {
            series = study_series[0];
            break;
        }
    }

    odil::MoveSCU move_scu(association);
    move_scu.set_affected_sop_class(
        odil::registry::StudyRootQueryRetrieveInformationModelMove);
    move_scu.set_move_destination(
        association.get_parameters().get_calling_ae_title());

    query->clear();
    query->add("QueryRetrieveLevel", { "SERIES" });
    query->add("StudyInstanceUID", (*series)["StudyInstanceUID"]);
    query->add("SeriesInstanceUID", (*series)["SeriesInstanceUID"]);

    std::cout << "--------\n";
    std::cout << "Callback\n";
    std::cout << "--------\n\n";

    move_scu.move(query, print_informations, odil::MoveSCU::MoveCallback());

    std::cout << "\n";

    std::cout << "------\n";
    std::cout << "vector\n";
    std::cout << "------\n\n";

    auto const result = move_scu.move(query);
    for(auto const & dataset: result)
    {
        print_informations(dataset);
    }

    association.release();
}
