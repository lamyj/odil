#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "dcmtkpp/conversion.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/StoreSCU.h"

void progress_callback(void * data, unsigned long bytes_count)
{
    long file_size = *reinterpret_cast<long*>(data);
    std::cout << bytes_count << "/" << file_size << std::endl;
}

int main(int argc, char** argv)
{
    dcmtkpp::Network network;
    network.initialize();
    
    dcmtkpp::DcmtkAssociation association;
    
    association.set_own_ae_title("myself");
    
    association.set_peer_host_name("pacs.example.com");
    association.set_peer_port(11112);
    association.set_peer_ae_title("pacs");
    
    association.add_presentation_context(
        dcmtkpp::registry::MRImageStorage,
        { dcmtkpp::registry::ImplicitVRLittleEndian });
    
    association.add_presentation_context(
        dcmtkpp::registry::EnhancedMRImageStorage,
        { dcmtkpp::registry::ImplicitVRLittleEndian });
    
    association.add_presentation_context(
        dcmtkpp::registry::VerificationSOPClass,
        { dcmtkpp::registry::ImplicitVRLittleEndian });
    
    association.associate(network);
    
    dcmtkpp::StoreSCU scu;
    scu.set_network(&network);
    scu.set_association(&association);
    
    scu.echo();
    
    for(int i=1; i<argc; ++i)
    {
        std::cout << "Storing " << argv[i] << std::endl;
        
        long file_size = OFStandard::getFileSize(argv[i]);
        DcmFileFormat file;
        file.loadFile(argv[i]);

        dcmtkpp::DataSet const data_set = dcmtkpp::convert(file.getDataset());
        
        scu.set_affected_sop_class(data_set);
        scu.store(data_set, progress_callback, &file_size);
    }
    
    association.release();
    network.drop();
}
