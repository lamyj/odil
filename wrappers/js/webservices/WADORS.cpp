#include <emscripten.h>
#include <emscripten/bind.h>

#include <odil/webservices/WADORS.h>

void wrap_webservices_WADORS()
{
    using namespace emscripten;
    using namespace odil::webservices::WADORS;
    
    enum_<Type>("webservices_WADORS_Type")
        .value("None", Type::None)
        .value("DICOM", Type::DICOM)
        .value("BulkData", Type::BulkData)
        .value("PixelData", Type::PixelData)
    ;

    /// @brief Data representation for DICOM requests and responses.
    enum_<Representation>("webservices_WADORS_Representation")
        .value("DICOM", Representation::DICOM)
        .value("DICOM_XML", Representation::DICOM_XML)
        .value("DICOM_JSON", Representation::DICOM_JSON)
    ;

    EM_ASM(
        Module['webservices']['WADORS'] = {};
        
        Module['webservices']['WADORS']['Type'] = Module['webservices_WADORS_Type'];
        delete Module['webservices_WADORS_Type'];
        
        Module['webservices']['WADORS']['Representation'] = Module['webservices_WADORS_Representation'];
        delete Module['webservices_WADORS_Representation'];
    );
}
