#include <iostream>

#include "odil/Association.h"
#include "odil/DataSet.h"
#include "odil/FindSCU.h"
#include "odil/MoveSCU.h"
#include "odil/registry.h"

void print_informations(odil::DataSet const & response)
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
    odil::Association association;
    association.set_peer_host("184.73.255.26");
    association.set_peer_port(11112);
    association.update_parameters()
        .set_calling_ae_title("myself")
        .set_called_ae_title("AWSPIXELMEDPUB")
        .set_presentation_contexts({
            {
                odil::registry::StudyRootQueryRetrieveInformationModelFIND,
                { odil::registry::ImplicitVRLittleEndian }, true, false
            },
            {
                odil::registry::StudyRootQueryRetrieveInformationModelMOVE,
                { odil::registry::ImplicitVRLittleEndian }, true, false
            },
            {
                odil::registry::MRImageStorage,
                { odil::registry::ImplicitVRLittleEndian }, false, true
            },
            {
                odil::registry::VerificationSOPClass,
                { odil::registry::ImplicitVRLittleEndian }, true, false
            }
        });

    association.associate();

    odil::FindSCU find_scu(association);
    find_scu.set_affected_sop_class(
        odil::registry::StudyRootQueryRetrieveInformationModelFIND);

    odil::DataSet query;
    query.add("QueryRetrieveLevel", { "STUDY" });
    query.add("StudyInstanceUID");
    query.add("NumberOfStudyRelatedSeries");

    auto const studies = find_scu.find(query);
    odil::DataSet series;
    for(auto const & study: studies)
    {
        if(!study.has("StudyInstanceUID"))
        {
            continue;
        }

        query = odil::DataSet();
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

    odil::MoveSCU move_scu(association);
    move_scu.set_affected_sop_class(
        odil::registry::StudyRootQueryRetrieveInformationModelMOVE);
    move_scu.set_move_destination(
        association.get_parameters().get_calling_ae_title());

    query = odil::DataSet();
    query.add("QueryRetrieveLevel", { "SERIES" });
    query.add("StudyInstanceUID", series["StudyInstanceUID"]);
    query.add("SeriesInstanceUID", series["SeriesInstanceUID"]);

    std::cout << "--------\n";
    std::cout << "Callback\n";
    std::cout << "--------\n\n";

    move_scu.move(query, print_informations, odil::MoveSCU::MoveCallback());

    std::cout << "\n";

    std::cout << "------\n";
    std::cout << "vector\n";
    std::cout << "------\n\n";

    std::vector<odil::DataSet> result = move_scu.move(query);
    for(auto dataset: result)
    {
        print_informations(dataset);
    }

    association.release();
}
