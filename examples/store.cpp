#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

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
    
    dcmtkpp::Association association;
    
    association.set_own_ae_title("bretagne");
    
    association.set_peer_host_name("aude.u-strasbg.fr");
    association.set_peer_port(11112);
    association.set_peer_ae_title("PIIV-RECHERCHE");
    
    association.add_presentation_context(UID_MRImageStorage,
        { UID_LittleEndianImplicitTransferSyntax });
    
    association.add_presentation_context(UID_EnhancedMRImageStorage,
        { UID_LittleEndianImplicitTransferSyntax });
    
    association.add_presentation_context(UID_VerificationSOPClass,
        { UID_LittleEndianImplicitTransferSyntax });
    
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
        
        std::cout << scu.get_affected_sop_class() << "\n";
        
        scu.store(file.getDataset(), progress_callback, &file_size);
    }
    
    association.release();
    network.drop();
}
